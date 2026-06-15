#include "header/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Initializes the Qt system
    MainWindow w;               // Creates the MainWindow object
    w.show();                   // Displays the window
    return a.exec();            // Starts the event loop
}