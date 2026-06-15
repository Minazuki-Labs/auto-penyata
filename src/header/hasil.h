#ifndef HASIL_H
#define HASIL_H 

#include "pagemanager.h"

class Hasil : public PageManager
{
    Q_OBJECT
    
public:
    explicit Hasil(Ui::MainWindow *m_ui, QObject *parent = nullptr,  StatusBar* statusBar = nullptr);

    // When Hasil page is open
    void handlePageActivation() override;
};
#endif // HASIL_H