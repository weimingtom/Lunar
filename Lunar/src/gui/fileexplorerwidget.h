#ifndef FILEEXPLORERWIDGET_H
#define FILEEXPLORERWIDGET_H

#include <string>
#include <QList>
#include <QTreeWidget>

class QTreeWidgetItem;
class QContextMenuEvent;

namespace gui
{

class FileExplorerWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit FileExplorerWidget(QWidget *parent = 0);
    virtual ~FileExplorerWidget();
    QString getCurrentSelectedDir();
signals:
    void openFile(const QString&);
public slots:
    void onFileSaved(const QString& file);
    void onAllFilesSaved();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *e);
private:
    void init();
    void initConnections();
    //load both folders and files
    bool loadNode(QTreeWidgetItem* item);
    //load only files
    bool loadNodeFiles(QTreeWidgetItem* item);
    QString getNodeAbsolutePath(QTreeWidgetItem* item);
    QString getNodeRelativePath(QTreeWidgetItem* item);
private Q_SLOTS:
    void loadRoot();
    void newFolder();
    void newFolderOk(const QString& folder_name);
    void deleteCurrentItem();
    void renameCurrentItem();
    void renameCurrentItemOk(const QString& new_name);
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);
    void onItemReturn(QTreeWidgetItem *item, int column);
    void onDeleteItems(QTreeWidgetItem* item, int column);
    QTreeWidgetItem* findDirNodeItemWithFile(const QString& file);
private:
};

}


#endif // FILEEXPLORERWIDGET_H
