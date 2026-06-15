#ifndef APUR_H
#define APUR_H 

#include "pagemanager.h"

class Apur : public PageManager
{
    Q_OBJECT
    
public:
    explicit Apur(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr);

    // When Apur page is open
    void handlePageActivation() override;
};
#endif // APUR_H