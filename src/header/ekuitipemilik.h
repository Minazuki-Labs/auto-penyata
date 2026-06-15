#ifndef EKUITIPEMILIK_H
#define EKUITIPEMILIK_H 

#include "pagemanager.h"

class EkuitiPemilik : public PageManager
{
    Q_OBJECT
    
public:
    explicit EkuitiPemilik(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Ekuiti Pemilik page is open
    void handlePageActivation() override;
};
#endif // EKUITIPEMILIK_H