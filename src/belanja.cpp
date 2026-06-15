#include "header/belanja.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

Belanja::Belanja(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar)
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "belanja.json";
    addButton = ui->button_belanja_addAccount;
    scrollArea = ui->scrollable_belanja;
    contentWidget = ui->belanja_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Button
    connect(addButton, &QPushButton::clicked, this, &Belanja::handleAddButtonClick); // Add button
}

// When Belanja page is open
void Belanja::handlePageActivation()
{
    qDebug() << "Switched to page: Belanja";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}