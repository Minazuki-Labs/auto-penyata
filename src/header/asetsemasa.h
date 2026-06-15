#ifndef ASETSEMASA_H
#define ASETSEMASA_H 

#include "pagemanager.h"

class AsetSemasa : public PageManager
{
    Q_OBJECT
    
public:
    explicit AsetSemasa(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Aset Semasa page is open
    void handlePageActivation() override;
};
#endif // ASETSEMASA_H