#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H 

#include "./ui_mainwindow.h"
#include "statusbar.h"

#include <memory>

class BlockManager;

class PageManager : public QObject
{
    Q_OBJECT
    
public:
    explicit PageManager(Ui::MainWindow *ui, QObject *parent, std::unique_ptr<BlockManager> blockManager);
    PageManager(Ui::MainWindow *ui, QObject *parent);
    virtual ~PageManager();

    // When page is open
    virtual void handlePageActivation() = 0;

    // When page is closed
    virtual void handlePageDeactivation();

protected:
    Ui::MainWindow *ui; 
    std::unique_ptr<BlockManager> m_blockManager; 

    // Page initailsation
    QString fileName; // Json file name
    QVariantMap jsonData; // Data from Json
    QPushButton* addButton; // Add account buttons
    QScrollArea* scrollArea; // Scrollable area
    QWidget *contentWidget; // Area to put all account block

    // Status bar
    StatusBar* m_statusBar;

    // Desired order of blocks
    QStringList desiredOrder;

protected slots:
    virtual void handleAddButtonClick();
};
#endif // PAGEMANAGER_H