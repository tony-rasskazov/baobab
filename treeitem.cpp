#include "treeitem.h"

#include <QDebug>
QPointer<TreeItem> TreeItem::s_selected = 0;
QPointer<TreeItem> TreeItem::s_highlighted = 0;


TreeItem::TreeItem(TreeItem *parent, const QString &content, const QColor &color, const QUrl &imageUrl, const QUrl &imageOpenUrl, bool isOpen) :
    QObject(parent),
    m_parentItem(parent),
    m_content(content),
    m_color(color),
    m_selected(false),
    m_highlighted(false),
    m_level(-1),
    m_childItems(QList<TreeItem*>()),
    m_isOpen(isOpen),
    m_var("vds://factory1.plant1.0.0/value.toString"),
    m_imageUrl(imageUrl),
    m_imageOpenUrl(imageOpenUrl),
    m_subSelected(false)
{
    if (parent) {
        parent->addChildItem(this);
        setLevel(parent->level() + 1);
    }
}

const QString &TreeItem::content() const {
    return m_content;
}

void TreeItem::setContent(const QString &content) {
    //qDebug() << "TreeItem::setContent" << content;
    if (content != m_content) {
        m_content = content;
        emit contentChanged();
    }
}

QColor TreeItem::color()
{
    return m_color;
}

void TreeItem::setColor(QColor color)
{
    if (color != m_color){
        m_color = color;
        emit colorChanged();
    }
}

QUrl TreeItem::imageOpenUrl() const
{
    return m_imageOpenUrl;
}

QUrl TreeItem::imageUrl() const
{
    return m_imageUrl;
}

bool TreeItem::selected() const
{
    return m_selected;
}

void TreeItem::setSelected(bool selected)
{
    if (selected != m_selected) {
        if (s_selected && (s_selected != this) && selected)
            s_selected->setSelected(false);

        m_selected = selected;
        s_selected = this;

        setSelectedItem(this);
        emit selectedChanged();

        if (m_parentItem)
            m_parentItem->setSubSelected(selected);
    }
}

bool TreeItem::highlighted() const
{
    return m_highlighted;
}

void TreeItem::setHighlighted(bool highlighted)
{
    if (highlighted != m_highlighted) {
        if (s_highlighted && (s_highlighted != this) && highlighted)
            s_highlighted->setHighlighted(false);

        m_highlighted = highlighted;
        s_highlighted = this;

        emit highlightedChanged();

    }
}

TreeItem *TreeItem::selectedItem() const
{
    return s_selected;
}

void TreeItem::setSelectedItem(TreeItem *selectedItem)
{
    //qDebug() << "TreeItem::setSelectedItem" << selectedItem << s_selected;
    s_selected = selectedItem;
    emit selectedItemChanged(s_selected);
}

TreeItem *TreeItem::parentItem() const
{
    return m_parentItem;
}

int TreeItem::level() const
{
    return m_level;
}

void TreeItem::setLevel(int level)
{
    if(level != m_level){
        m_level = level;
        emit levelChanged();
    }

}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::isLeaf() const
{
    return childCount() > 0;
}

//! индекс в parent->m_childItems
int TreeItem::index() const
{
    if (!m_parentItem)
        return -1;
    else {
        TreeItem *p = m_parentItem;

        int inx = p->m_childItems.indexOf(const_cast<TreeItem*>(this));

        return inx;
    }
}

const QList<TreeItem *> &TreeItem::childItems() const {
    return m_childItems;
}

const QList<QObject *> TreeItem::childItemsAsQObject() const{
    QList<QObject *> res;
    res.reserve(m_childItems.count());
    for(auto i : m_childItems)
        res.append(i);
    return res;
}

void TreeItem::addChildItem(TreeItem *childItem, bool silent){
    m_childItems.append(childItem);
    setIsOpen(true);
    if (!silent) {
        emit childItemsChanged();
        emit hasChildChanged();
    }
}

bool TreeItem::isOpen() const{
    return m_isOpen;
    //return m_childItems.count() == 0 ? true : m_isOpen;
}

void TreeItem::setIsOpen(bool isOpen){
    if(isOpen != m_isOpen){
        m_isOpen = isOpen;
        emit isOpenChanged();
    }
}

bool TreeItem::hasChild() const{
    return !m_childItems.isEmpty();
}

QString TreeItem::variable() const
{
    return m_var;
}

void TreeItem::setVariable(QString variable)
{
    if (variable != m_var) {
        m_var = variable;
        emit variableChanged();
    }
}

bool TreeItem::subSelected() const
{
    return m_subSelected;
}

void TreeItem::setSubSelected(bool subSelected)
{
    if (subSelected != m_subSelected) {
        m_subSelected = subSelected;
        if (m_parentItem) {
            m_parentItem->setSubSelected(m_subSelected);
        }
        emit subSelectedChanged();
    }
}

void TreeItem::silentClear()
{
    foreach (TreeItem* ti, childItems()) {
        //delete ti;
    }
    m_childItems.clear();

}

void TreeItem::removeChild(TreeItem *child)
{
    m_childItems.removeAll(child);
    delete child;
    emit childCountChanged();
    emit childItemsChanged();
}
