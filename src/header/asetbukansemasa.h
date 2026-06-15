#ifndef ASETBUKANSEMASA_H
#define ASETBUKANSEMASA_H 

#include "pagemanager.h"

class AsetBukanSemasa : public PageManager
{
    Q_OBJECT
    
public:
    explicit AsetBukanSemasa(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Aset Bukan Semasa page is open
    void handlePageActivation() override;
    void handlePageDeactivation() override;

private slots:
    void handleAddButtonClick() override;
};
#endif // ASETBUKANSEMASA_H