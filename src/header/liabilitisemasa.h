#ifndef LIABILITISEMASA_H
#define LIABILITISEMASA_H 

#include "pagemanager.h"

class LiabilitiSemasa : public PageManager
{
    Q_OBJECT
    
public:
    explicit LiabilitiSemasa(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Liabiliti Semasa page is open
    void handlePageActivation() override;
};
#endif // LIABILITISEMASA_H