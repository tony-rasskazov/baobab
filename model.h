#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class TreeItem;

class Model : public QObject
{
    Q_OBJECT
public:
    QList<TreeItem *> s_allItems;

    explicit Model(QObject *parent = 0);

    Q_PROPERTY(QList<QObject*> tree READ treeAsQObjects NOTIFY treeChanged)
    const QList<TreeItem*> &tree() const;
    const QList<QObject*> treeAsQObjects() const;

    Q_PROPERTY(int count READ count)
    int count() const;

    Q_PROPERTY(TreeItem* selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)
    TreeItem *selectedItem() const;
    void setSelectedItem(TreeItem* selectedItem);


    void clearModel();

signals:
    void treeChanged();
    void selectedItemChanged(TreeItem *item);

public slots:
    void onSelectedItemChanged(TreeItem *item);
    TreeItem *insertChild(TreeItem *parent);
    void deleteChild(TreeItem *item);

    void save(const QString& filename);
    void open(const QString& filename);

private:
    static TreeItem* s_rootItem;

    QList<TreeItem*> m_tree;
    TreeItem *m_selectedItem;
};

#endif // MODEL_H
