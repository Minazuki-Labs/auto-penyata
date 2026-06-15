#include "header/setting.h"
#include "header/jsonmanager.h"
#include "header/statusbar.h"

Setting::Setting(Ui::MainWindow *m_ui, QObject *parent, StatusBar* statusBar)
    : PageManager(m_ui, parent)
{
    m_statusBar = statusBar;

    // Button
    connect(ui->button_reset, &QPushButton::clicked, this, &Setting::handleResetButtonClick); // Reset button
    connect(ui->button_setToday, &QPushButton::clicked, this, &Setting::handleSetTodayButtonClick); // setToday button
}

// When setting page is open
void Setting::handlePageActivation()
{
    qDebug() << "Switched to page: Setting";
    loadJson();
    
    ui->label_reset_status->setVisible(false); // Hide reset label
}

// When setting page is closed
void Setting::handlePageDeactivation()
{   
    // Get data
    QVariantMap settingsMap {
        {"CompanyName", ui->input_company_name->text()},
        {"Date", ui->input_date->date().toString("yyyy/MM/dd")}
    };

    // Check if changes were made
    if (settingsMap["CompanyName"] == initialCompanyName && settingsMap["Date"] == initialDate){
        return;
    }

    // Save to Json
    bool success = JsonManager::writeJson("setting.json", settingsMap);

    if (success) {
        qDebug() << "Data saved successfully to setting.json";
    } else {
        qDebug() << "Failed to save data to setting.json";
    }
}

// Load from JSON
void Setting::loadJson()
{
    jsonData= JsonManager::readJson("setting.json");

    if (jsonData.isEmpty()) {
        qWarning() << "setting.json is empty. Cannot load value";
        return;
    }

    // Find "CompanyName"
    if (jsonData.contains("CompanyName")) {
        initialCompanyName = jsonData["CompanyName"].toString();
    } else {
        qWarning() << "Key 'CompanyName' not found in setting.json.";
        initialCompanyName = ""; 
    }

    // Find "Date"
    if (jsonData.contains("Date")) {
        QString dateString = jsonData["Date"].toString();
        QDate date = QDate::fromString(dateString, "yyyy/MM/dd");

        // Check if the conversion was successful
        if (date.isValid()) {
            initialDate = date;
        } else {
            qWarning() << "Date string '" << dateString << "' is not in the expected format (YYYY/MM/DD).";
            initialDate = QDate::currentDate();
        }
    } else {
        qWarning() << "Key 'Date' not found in settings.";
        initialDate = QDate::currentDate();
    }

    // Update the form
    ui->input_company_name->setText(initialCompanyName);
    ui->input_date->setDate(initialDate);
}

// When user press Reset button
void Setting::handleResetButtonClick()
{
    // Reset JSON
    if (JsonManager::resetJSON())
    {
        ui->label_reset_status->setText("Reset Successful!");
        ui->label_reset_status->setStyleSheet("QLabel { color : #37ba1e }");
    }
    else
    {
        ui->label_reset_status->setText("Reset Failed!");
        ui->label_reset_status->setStyleSheet("QLabel { color : #e21717 }");
    }

    ui->label_reset_status->setVisible(true);
    loadJson();

    m_statusBar->createStatusBar();
}

// When user press setToday button
void Setting::handleSetTodayButtonClick()
{
    qDebug() << "Change date to today:" << QDate::currentDate();
    ui->input_date->setDate(QDate::currentDate());
}