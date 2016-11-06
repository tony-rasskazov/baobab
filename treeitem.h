#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <QColor>
#include <QUrl>
#include <QPointer>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TreeItem(TreeItem *parent = 0, const QString &content="(no content)", const QColor &color=Qt::black, const QUrl &imageUrl=QString("qrc:/img/folder-blue.png"), const QUrl &imageOpenUrl=QString("qrc:/img/folder-blue_open.png"), bool isOpen = true);

    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    const QString & content() const;

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    QColor color();
    void setColor(QColor color);

    Q_PROPERTY(QUrl imageUrl READ imageUrl NOTIFY imageUrlChanged)
    QUrl imageUrl() const;

    Q_PROPERTY(QUrl imageOpenUrl READ imageOpenUrl NOTIFY imageOpenUrlChanged)
    QUrl imageOpenUrl() const;

    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    bool selected() const;
    void setSelected(bool selected);

    Q_PROPERTY(bool highlighted READ highlighted WRITE setHighlighted NOTIFY highlightedChanged)
    bool highlighted() const;
    void setHighlighted(bool highlighted);

    Q_PROPERTY(TreeItem* selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)
    TreeItem * selectedItem() const;
    void setSelectedItem(TreeItem* selectedItem);

    Q_PROPERTY(TreeItem* parentItem READ parentItem NOTIFY parentItemChanged)
    TreeItem * parentItem() const;

    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    int level() const;
    void setLevel(int level);

    Q_PROPERTY(int childCount READ childCount NOTIFY childCountChanged)
    int childCount() const;

    Q_PROPERTY(int isLeaf READ isLeaf NOTIFY isLeafChanged)
    int isLeaf() const;

    Q_PROPERTY(int index READ index)
    int index() const;

    Q_PROPERTY(QList<QObject *> childItems READ childItemsAsQObject NOTIFY childItemsChanged)
    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    void addChildItem(TreeItem * childItem, bool silent = false);

    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    bool isOpen() const;
    void setIsOpen(bool isOpen);

    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    bool hasChild() const;

    Q_PROPERTY(QString variable READ variable WRITE setVariable NOTIFY variableChanged)
    QString variable() const;
    void setVariable(QString variable);

    Q_PROPERTY(bool subSelected READ subSelected WRITE setSubSelected NOTIFY subSelectedChanged)
    bool subSelected() const;
    void setSubSelected(bool subSelected);

    void silentClear();

signals:
    void imageUrlChanged();
    void imageOpenUrlChanged();
    void parentItemChanged();
    void variableChanged();
    void contentChanged();
    void childCountChanged();
    void colorChanged();
    void selectedChanged();
    void highlightedChanged();
    void levelChanged();
    void childItemsChanged();
    void isOpenChanged();
    void isLeafChanged();
    void hasChildChanged();
    void selectedItemChanged(TreeItem *item);
    void subSelectedChanged();

public slots:
    void setContent(const QString & content);

    void removeChild(TreeItem *child);

private:
    static QPointer<TreeItem> s_selected;
    static QPointer<TreeItem> s_highlighted;

    TreeItem *m_parentItem;
    QString m_content;
    QColor m_color;
    bool m_selected;
    bool m_highlighted;
    int m_level;
    QColor m_levelColor;
    QList<TreeItem *> m_childItems;
    bool m_isOpen;
    QString m_var;
    QUrl m_imageUrl;
    QUrl m_imageOpenUrl;
    bool m_subSelected;
};

Q_DECLARE_METATYPE(TreeItem*)

#endif // TREEITEM_H
