#include "model.h"
#include "treeitem.h"

#include <QColor>
#include <QUrl>

#include <QDebug>
#include <QFile>

#include "persist.h"

const int number = 100;

const QList<QColor> colors = {
    QColor(Qt::blue),
    QColor(Qt::darkYellow),
    QColor(Qt::darkGreen),
    QColor(Qt::red),
    QColor(Qt::darkRed),
    QColor(Qt::gray),
    QColor(Qt::darkMagenta),
    QColor(Qt::darkBlue),
};

//! нормально сделать каритинки для набора состояний
const QList<QUrl> folderClosedImages = {
    QUrl("qrc:/img/folder-blue.png"),
    QUrl("qrc:/img/folder-yellow.png"),
    QUrl("qrc:/img/folder-green.png"),
    QUrl("qrc:/img/folder-red.png"),
    QUrl("qrc:/img/folder-orange.png"),
    QUrl("qrc:/img/folder-grey.png"),
    QUrl("qrc:/img/folder-violet.png"),
    QUrl("qrc:/img/folder-cyan.png"),
};

const QList<QUrl> folderOpenImages = {
    QUrl("qrc:/img/folder-blue_open.png"),
    QUrl("qrc:/img/folder-yellow_open.png"),
    QUrl("qrc:/img/folder-green_open.png"),
    QUrl("qrc:/img/folder-red_open.png"),
    QUrl("qrc:/img/folder-orange_open.png"),
    QUrl("qrc:/img/folder-grey_open.png"),
    QUrl("qrc:/img/folder-violet_open.png"),
    QUrl("qrc:/img/folder-cyan_open.png"),
};

static TreeItem *createTreeItem(Model* model, const QString &title = "(no title)", TreeItem *parent = 0, bool isOpen = true)
{

    int level = parent ? parent->level() + 1 : 0;

    auto res = new TreeItem(parent, title, colors.at(level), folderClosedImages.at(level), folderOpenImages.at(level), isOpen);
    if (model) { QObject::connect(res, SIGNAL(selectedItemChanged(TreeItem*)), model, SLOT(onSelectedItemChanged(TreeItem*))); }

    return res;
}

TreeItem * Model::s_rootItem = 0;//createTreeItem(0, "[Empty]");

void Model::onSelectedItemChanged(TreeItem *item)
{
    //qDebug() << "Model::onSelectedItemChanged" << item;
    m_selectedItem = item;
    emit selectedItemChanged(item);
}

TreeItem* Model::insertChild(TreeItem *parent)
{
    //qDebug() << "Model::insertChild" << parent;
    auto i = createTreeItem(this, "Новый элемент", parent, false);
    emit treeChanged();

    return i;
}

void Model::deleteChild(TreeItem *item)
{
    QList<TreeItem*>& pcl = const_cast<QList<TreeItem*>&>(item->parentItem()->childItems());
    if (pcl.contains(item)) {
        qDebug() << "Model::deleteChild" << item;

        auto i = pcl.at(pcl.indexOf(item));
        if (i->parentItem()) i->parentItem()->setSelected(true);
        item->parentItem()->removeChild(i);
        //delete i;

        emit treeChanged();
    }

}

void Model::save(const QString &filename)
{
    QFile f(filename);

    f.open(QIODevice::WriteOnly);
    QTextStream fs(&f);

    Persist p(s_rootItem);
    fs << p;

    f.close();
}

void Model::open(const QString &filename)
{
    QFile f(filename);

    f.open(QIODevice::ReadOnly);
    QByteArray xml;

    QTextStream fs(&f);
    xml = f.readAll();

    //qDebug(xml);
    //delete s_rootItem;
    clearModel();

    TreeItem *opened = Persist::deserialize(xml);

    qDebug() << Persist(opened);

    delete s_rootItem;
    s_rootItem = opened;
    m_tree = opened->childItems();
    emit treeChanged();

}

Model::Model(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>()),
    m_selectedItem(s_rootItem)
{
    qRegisterMetaType<TreeItem*>();

    if (!s_rootItem) {
        s_rootItem = createTreeItem(this, "(root)");
    }

    auto factory1 = createTreeItem(this, "Завод", s_rootItem);

    auto plant1 = createTreeItem(this, "Цех №1", factory1);
    auto c11 = createTreeItem(this, "Компрессор", plant1);

    auto p1 = createTreeItem(this, "Подшипник №1", c11, false);
    createTreeItem(this, "Вибрация X", p1);
    createTreeItem(this, "Вибрация Y", p1);
    createTreeItem(this, "Вибрация Z", p1);

    p1 = createTreeItem(this, "Подшипник №2", c11);
    createTreeItem(this, "Вибрация X", p1);
    createTreeItem(this, "Вибрация Y", p1);
    createTreeItem(this, "Вибрация Z", p1);

    auto t11 = createTreeItem(this, "Турбина", plant1, false);
    createTreeItem(this, "обороты", t11);
    createTreeItem(this, "t", t11);
    auto n11 = createTreeItem(this, "Нагнетатель", plant1, false);
    createTreeItem(this, "Вкл", n11);
    createTreeItem(this, "Авария", n11);
    auto d11 = createTreeItem(this, "Диагностика", plant1, false);
    auto d12 = createTreeItem(this, "Вычисляемое значение 1", d11);
    auto d13 = createTreeItem(this, "Вычисляемое значение 2", d12);
    auto d14 = createTreeItem(this, "Вычисляемое значение 3", d13);
    auto d15 = createTreeItem(this, "Вычисляемое значение 4", d14);
    auto d16 = createTreeItem(this, "Вычисляемое значение 5", d15);
    //! todo: защиту от listIndexOutOfBounds
    //! auto d17 = createTreeItem(this, "Вычисляемое значение 5", d16);

    plant1 = createTreeItem(this, "Цех №2", factory1, false);
    c11 = createTreeItem(this, "Компрессор", plant1, false);

    p1 = createTreeItem(this, "Подшипник №1", c11, false);
    createTreeItem(this, "x", p1);
    createTreeItem(this, "y", p1);
    createTreeItem(this, "z", p1);

    t11 = createTreeItem(this, "Турбина", plant1, false);
    createTreeItem(this, "обороты", t11);
    createTreeItem(this, "t", t11);
    n11 = createTreeItem(this, "Нагнетатель", plant1, false);
    createTreeItem(this, "Вкл", n11);
    createTreeItem(this, "Авария", n11);
    d11 = createTreeItem(this, "Диагностика", plant1, false);
    createTreeItem(this, "Вычисляемое значение 1", d11);
    createTreeItem(this, "Вычисляемое значение 2", d11);
    createTreeItem(this, "Вычисляемое значение 3", d11);
    createTreeItem(this, "Вычисляемое значение 4", d11);
    createTreeItem(this, "Вычисляемое значение 5", d11);


    auto factory2 = createTreeItem(this, "Завод 2", s_rootItem);

    plant1 = createTreeItem(this, "Цех №A", factory2);
    c11 = createTreeItem(this, "Компрессор №A", plant1);

    p1 = createTreeItem(this, "Подшипник №A", c11);
    createTreeItem(this, "x", p1);
    createTreeItem(this, "y", p1);
    createTreeItem(this, "z", p1);

    t11 = createTreeItem(this, "Турбина", plant1);
    createTreeItem(this, "обороты", t11);
    createTreeItem(this, "t", t11);
    n11 = createTreeItem(this, "Нагнетатель", plant1);
    createTreeItem(this, "Вкл", n11);
    createTreeItem(this, "Авария", n11);
    d11 = createTreeItem(this, "Диагностика over9000", plant1, false);

    /*
    for (int i = 0; i < 1000; ++i) {
        createTreeItem(this, QString("Что-то %1").arg(i), d11);
    }
    */

    m_tree.append(factory1);
    m_tree.append(factory2);
}

const QList<TreeItem *> &Model::tree() const{
    QList<TreeItem *> res;
    res.reserve(m_tree.count());
    for(auto i : m_tree)
        res.append(i);
    return res;
}

const QList<QObject *> Model::treeAsQObjects() const{
    QList<QObject *> res;
    res.reserve(m_tree.count());
    for(auto i : m_tree)
        res.append(i);
    return res;
}

int Model::count() const
{
    return m_tree.count();
}

TreeItem *Model::selectedItem() const
{
    return m_selectedItem;
}

void Model::setSelectedItem(TreeItem *selectedItem)
{
    //qDebug() << "Model::setSelectedItem" << selectedItem;
    if (selectedItem != m_selectedItem) {
        m_selectedItem = selectedItem;
        emit selectedItemChanged(m_selectedItem);
    }
}

void Model::clearModel()
{
    s_rootItem->silentClear();
}
