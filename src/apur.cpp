#include "header/apur.h"
#include "header/blockmanager.h"
#include "header/jsonmanager.h"

Apur::Apur(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar) 
    : PageManager(m_ui, parent, std::make_unique<BlockManager>(nullptr))
{
    // Page initailsation
    fileName = "apur.json";
    scrollArea = ui->scrollable_apur;
    contentWidget = ui->apur_scrollAreaWidgetContents;
    m_statusBar = statusBar;

    // Desired display order of keys
    desiredOrder = {
        "Jualan",
        "Pulangan Jualan",
        "Inventori Awal",
        "Belian",
        "Pulangan Belian",
        "Angkutan Masuk",
        "Upah Atas Belian",
        "Duti Import",
        "Insurans Atas Belian",
        "Inventori Akhir"
    };

    handlePageActivation();
}

// When Apur page is open
void Apur::handlePageActivation()
{
    qDebug() << "Switched to page: APUR";

    // Create accounts block
    jsonData = JsonManager::readJson(fileName);
    m_blockManager->createAccountBlocks(jsonData, desiredOrder, ui, scrollArea, contentWidget);
}