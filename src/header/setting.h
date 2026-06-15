#ifndef SETTING_H
#define SETTING_H 

#include "pagemanager.h"

class Setting : public PageManager
{
    Q_OBJECT
    
public:
    explicit Setting(Ui::MainWindow *m_ui, QObject *parent = nullptr, StatusBar* statusBar = nullptr); 

    // When setting page is open
    void handlePageActivation();

    // When setting page is closed
    void handlePageDeactivation();

private slots:
    // Button
    void handleResetButtonClick(); // Called when Reset button pressed
    void handleSetTodayButtonClick(); // Called when setToday button pressed

private:
    // VARIABLE
    QString initialCompanyName;
    QDate initialDate;

    // Read from Json
    void loadJson();

};
#endif // SETTING_H