#include "header/asetsemasa.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

AsetSemasa::AsetSemasa(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar) 
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "aset_semasa.json";
    addButton = ui->button_as_addAccount;
    scrollArea = ui->scrollable_as;
    contentWidget = ui->as_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Desired display order of keys
    desiredOrder = {
        "Tunai",
        "Bank",
        "Akaun Belum Terima",
        "Peruntukan Hutang Ragu"
    };

    // Button
    connect(addButton, &QPushButton::clicked, this, &AsetSemasa::handleAddButtonClick); // Add button
}

// When Aset Semasa page is open
void AsetSemasa::handlePageActivation()
{
    qDebug() << "Switched to page: Aset Semasa";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}