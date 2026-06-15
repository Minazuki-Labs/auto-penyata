#include "header/asetbukansemasa.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

AsetBukanSemasa::AsetBukanSemasa(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar)
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "aset_bukan_semasa.json";
    addButton = ui->button_abs_addAccount;
    scrollArea = ui->scrollable_abs;
    contentWidget = ui->abs_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Button
    connect(addButton, &QPushButton::clicked, this, &AsetBukanSemasa::handleAddButtonClick); // Add button
}

// When Aset Bukan Semasa page is open
void AsetBukanSemasa::handlePageActivation()
{
    qDebug() << "Switched to page: Aset Bukan Semasa";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAbsAccountBlocks(jsonData, ui, scrollArea, contentWidget);
}

// When page is closed
void AsetBukanSemasa::handlePageDeactivation()
{   
    // Get all data
    QVariantMap newData = m_blockManager->getAbsValueMap();
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

// When add button is click
void AsetBukanSemasa::handleAddButtonClick()
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

    // Create a new map
    QVariantMap newEntry;
    newEntry.insert("value", 0.0);
    newEntry.insert("deprecatedValue", 0.0);

    // Add the new data to the map
    jsonData.insert(uniqueKey, newEntry);
    
    // Create accounts block
    m_blockManager->createAbsAccountBlocks(jsonData, ui, scrollArea, contentWidget);
}