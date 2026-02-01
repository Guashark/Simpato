#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "item_view.h"

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

private slots:
    void select_item();

    void note_edit();

    void push_edit(QString note);

    void on_addBtn_clicked();

    void on_rmBtn_clicked();

    void on_upBtn_clicked();

    void on_downBtn_clicked();

private:
    Ui::MainWindow *ui;  
};
#endif // MAIN_WINDOW_H
