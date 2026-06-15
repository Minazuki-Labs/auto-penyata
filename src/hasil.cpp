#include "header/hasil.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

Hasil::Hasil(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar)
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "hasil.json";
    addButton = ui->button_hasil_addAccount;
    scrollArea = ui->scrollable_hasil;
    contentWidget = ui->hasil_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Button
    connect(addButton, &QPushButton::clicked, this, &Hasil::handleAddButtonClick); // Add button
}

// When Hasil page is open
void Hasil::handlePageActivation()
{
    qDebug() << "Switched to page: Hasil";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}