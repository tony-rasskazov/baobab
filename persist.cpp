#include "persist.h"

#include <QDebug>

#include <QString>
#include <QTextStream>

#include <QVariant>
#include <QMetaProperty>

#include <QDomDocument>
#include <QDomElement>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "model.h"

std::ostream& operator<<(std::ostream &s, const Persist &yo)
{
    s << Persist::_serialize_to_xml(yo.m_pObject).toStdString();
    return s;
}

QDataStream& operator<<(QDataStream &s, const Persist& yo)
{
    s << Persist::_serialize_to_xml(yo.m_pObject);
    return s;
}

QTextStream& operator<<(QTextStream &s, const Persist& yo)
{
    s << Persist::_serialize_to_xml(yo.m_pObject);
    return s;
}

QDebug operator<<(QDebug debug, const Persist& yo)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << Persist::_serialize_to_xml(yo.m_pObject);

    return debug;
}

QByteArray& operator<<(QByteArray& ba, const Persist& yo)
{
    ba = Persist::_serialize_to_xml(yo.m_pObject);
    return ba;
}

QByteArray Persist::_serialize_to_xml(TreeItem* object)
{
    if (!object)
        return QByteArray("<NIL />");

    QDomDocument doc;
    //QDomElement root = doc.createElement(object->metaObject()->className());
    QDomElement root = doc.createElement("Instance");

    doc.appendChild(root);

    _serialize_to_xml_recursive(object, doc, root);

    return doc.toByteArray();
}

void Persist::_serialize_to_xml_recursive(TreeItem* object, QDomDocument &doc, QDomElement &xmlElement)
{
    xmlElement.setAttribute("Type", object->metaObject()->className());
    xmlElement.setAttribute("objectName", object->objectName());

    for (int i = 0; i < object->metaObject()->propertyCount(); i++) {

        QMetaProperty prop = object->metaObject()->property(i);
        QString propName = prop.name();
        QString typeName = prop.typeName();
        QVariant value = object->property(propName.toStdString().data());

        QDomElement el = doc.createElement("Property");
        el.setAttribute("Type", typeName);
        el.setAttribute("Name", propName);

        if (typeName != "QVariant") {
            QDomText txt = doc.createTextNode( value.toString() );
            el.appendChild(txt);
        } else {
            el.setAttribute("VariantType", value.typeName());

            TreeItem *o = qvariant_cast<TreeItem*>(value);

            if (o) {
                QDomText txt = doc.createTextNode( o->objectName() );
                el.appendChild(txt);
            }
        }

        xmlElement.appendChild(el);

    }

    if (object->children().count() > 0) {
        foreach (QObject* ochild, object->children()) {
            TreeItem* child = dynamic_cast<TreeItem*>(ochild);
//            QDomElement el = doc.createElement(child->metaObject()->className());

            if (child) {
                QDomElement el = doc.createElement("Instance");
                xmlElement.appendChild(el);

                _serialize_to_xml_recursive(child, doc, el);
            }
        }
    }

}


/*
template<class T>
T* YO::deserialize<T*>(QByteArray xml) {
    return NULL;
}
*/

TreeItem* Persist::deserialize(QByteArray xml)
{
    TreeItem* object = new TreeItem();
    Model *m;

    QQmlApplicationEngine engine;
    m = qvariant_cast<Model*>(engine.rootContext()->contextProperty("programmModel"));

    if (m) { QObject::connect(object, SIGNAL(selectedItemChanged(TreeItem*)), m, SLOT(onSelectedItemChanged(TreeItem*))); }

    if (deserialize_from_xml(xml, object))
        return object;
    delete object;
    return NULL;
}

/*
template<>
YObject* YO::deserialize<YObject>(QByteArray xml)
{
    YObject* object = new YObject();
    if (deserialize_from_xml(xml, object))
        return object;
    delete object;
    return NULL;
}
*/

bool Persist::deserialize_from_element(QDomElement xml, TreeItem *object)
{
    QDomElement propElement = xml.firstChildElement("Property");
    for (; !propElement.isNull(); propElement = propElement.nextSiblingElement("Property")) {
        QString propName = propElement.attribute("Name");
        QString propValue = propElement.text();
        //qDebug() << "setProperty" << propName << propValue;
        if ((propName != "selectedItem") &&
                (propName != "subSelected") &&
                (propName != "highlighted") &&
                (propName != "selected") &&
                (propName != "isOpen")

                ) {
                object->setProperty(propName.toStdString().c_str(), QVariant(propValue));
        }
    }

    QDomElement instanceElement = xml.firstChildElement("Instance");
    for (; !instanceElement.isNull(); instanceElement = instanceElement.nextSiblingElement("Instance")) {
        TreeItem *y = new TreeItem(object);
        deserialize_from_element(instanceElement, y);
    }
    return true;
}

bool Persist::deserialize_from_xml(QByteArray xml, TreeItem* object)
{
    QDomDocument doc;
    if (!doc.setContent(xml))
        return false;
    QDomElement root = doc.documentElement();

    object->setObjectName(root.attribute("objectName"));

    deserialize_from_element(root, object);

    return true;
}


