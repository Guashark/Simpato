#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "item_view.h"

#include <QDir>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <vector>
#include <QMap>

#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    itemView *curr_item = nullptr;

    void process_notes(const QString folder_path);

private slots:
    void select_item();

    void note_edit();

    void push_edit(QString note);

    void on_addBtn_clicked();

    void on_rmBtn_clicked();

    void on_upBtn_clicked();

    void on_downBtn_clicked();

    void rm_note();

private:
    Ui::MainWindow *ui;

    QMap<itemView *, int64_t> local_notes;
    void create_item();
    void release_curr_ptr();

};
#endif // MAIN_WINDOW_H
