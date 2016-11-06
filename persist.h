#ifndef YO_H
#define YO_H

#include <iostream>

#include <QObject>
#include <QByteArray>
#include <QPointer>

#include <QDataStream>
#include <QTextStream>

#include <QDomDocument>
#include <QDomElement>

#include <QDebug>

#include "treeitem.h"

class Persist
{
public:

    enum Serializer {
        xml,
        txt,
        none,
        raw
    };


    Persist(TreeItem *object, Serializer serializer = xml) : m_pObject(object), m_serializer(serializer) { /* nothing */ }

    friend std::ostream& operator<<(std::ostream&, const Persist&);
    friend QDataStream& operator<<(QDataStream&, const Persist&);
    friend QTextStream& operator<<(QTextStream&, const Persist&);
    friend QByteArray& operator<<(QByteArray&, const Persist&);

    //todo: исключить из релиза
    friend QDebug operator<<(QDebug debug, const Persist&);

    static QByteArray _serialize_to_xml(TreeItem* object);


    static TreeItem* deserialize(QByteArray xml);


private:
    TreeItem* m_pObject;
    Serializer m_serializer;

    static void _serialize_to_xml_recursive(TreeItem* object, QDomDocument &xmlDoc, QDomElement &xmlElement);
    static bool deserialize_from_xml(QByteArray xml, TreeItem* object);
    static bool deserialize_from_element(QDomElement xml, TreeItem* object);

};



#endif // YO_H
