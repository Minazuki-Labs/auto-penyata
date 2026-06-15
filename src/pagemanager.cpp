#include "header/pagemanager.h"
#include "header/jsonmanager.h"
#include "header/blockmanager.h"

PageManager::PageManager(Ui::MainWindow *ui, QObject *parent, std::unique_ptr<BlockManager> blockManager)
    : QObject(parent),
      ui(ui),
      m_blockManager(std::move(blockManager))
{
}

PageManager::PageManager(Ui::MainWindow *ui, QObject *parent)
    : QObject(parent),
      ui(ui)
{
}

PageManager::~PageManager() = default; 

// When page is closed
void PageManager::handlePageDeactivation()
{   
    // Get all data
    QVariantMap newData = m_blockManager->getAllValueMap();
    newData.insert("_placeholder", true);

    // Save to Json
    bool success = JsonManager::writeJson(fileName, newData);

    if (success) {
        qDebug() << "Data saved successfully to" << fileName;
        
        // Update status bar
        m_statusBar->updateStatusBar(fileName, newData, jsonData);
    } else {
        qDebug() << "Failed to save data to" << fileName;
    }
}

void PageManager::handleAddButtonClick()
{
    // Save into Json
    handlePageDeactivation();
    jsonData = JsonManager::readJson(fileName);

    const QString newKey = "New account";
    
    // Find a unique key to prevent duplicate
    QString uniqueKey = newKey;
    int counter = 1;
    while (jsonData.contains(uniqueKey)) {
        uniqueKey = QString("%1 %2").arg(newKey).arg(counter++);
    }

    // Add the new data to the map
    jsonData.insert(uniqueKey, 0.0); 

    // Create accounts block
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}