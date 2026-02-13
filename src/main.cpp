#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.process_notes(QDir::homePath() + "/.local/share/Simpato/notes/");
    w.show();
    return a.exec();
}
