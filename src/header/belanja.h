#ifndef BELANJA_H
#define BELANJA_H 

#include "pagemanager.h"

class Belanja : public PageManager
{
    Q_OBJECT
    
public:
    explicit Belanja(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Belanja page is open
    void handlePageActivation() override;
};
#endif // BELANJA_H