#include "header/liabilitibukansemasa.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

LiabilitiBukanSemasa::LiabilitiBukanSemasa(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar)
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "liabiliti_bukan_semasa.json";
    addButton = ui->button_lbs_addAccount;
    scrollArea = ui->scrollable_lbs;
    contentWidget = ui->lbs_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Button
    connect(addButton, &QPushButton::clicked, this, &LiabilitiBukanSemasa::handleAddButtonClick); // Add button
}

// When Liabilti Bukan Semasa page is open
void LiabilitiBukanSemasa::handlePageActivation()
{
    qDebug() << "Switched to page: Liabiliti Bukan Semasa";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}