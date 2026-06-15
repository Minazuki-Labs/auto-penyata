#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "./ui_mainwindow.h"

class StatusBar : public QObject
{
    Q_OBJECT

public:
    StatusBar(Ui::MainWindow *ui, QObject *parent);

    // Update status bar
    void updateStatusBar(QString page, QVariantMap newData, QVariantMap oldData);
    void createStatusBar();

    // Check if account is balance
    bool checkBalance();

private:
    Ui::MainWindow *ui;

    // Amount
    double debitAmount;
    double creditAmount;

    // Status bar initailsation
    QWidget* statusBar; // Status bar
    QLabel* amountLabel; // Label showing amount

    // Index of each page
    QHash<QString, int> m_pageIndexMap;

    // Update data in each page
    void updateApurValue(const QVariantMap apurData, bool reverse = false);
    void updateAbsValue(const QVariantMap absData, bool reverse = false);
    void updateAsValue(const QVariantMap asData, bool reverse = false);
    void updateCustomValue(const QVariantMap data, double& amount, bool reverse = false);
    void updateEpValue(const QVariantMap epData, bool reverse = false);

    // Update status label
    void updateStatusLabel();
};
#endif // STATUSBAR_H