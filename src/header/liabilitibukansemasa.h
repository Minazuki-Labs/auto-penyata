#ifndef LIABILITIBUKANSEMASA_H
#define LIABILITIBUKANSEMASA_H 

#include "pagemanager.h"

class LiabilitiBukanSemasa : public PageManager
{
    Q_OBJECT
    
public:
    explicit LiabilitiBukanSemasa(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr); 

    // When Liabiliti Bukan Semasa page is open
    void handlePageActivation() override;
};
#endif // LIABILITIBUKANSEMASA_H