#include "main_window.h"
#include "ui_main_window.h"
#include "item_view.h"
#include "note_view.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Simpato !");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::select_item()
{
    curr_item = qobject_cast<itemView*>(sender());
    std::cout << curr_item << std::endl;
}

void MainWindow::note_edit()
{
    noteView *note = new noteView(nullptr);
    note->show();
    connect(note, &noteView::finish_edit, this, &MainWindow::push_edit);
}

void MainWindow::push_edit(QString note)
{
    curr_item->get_textView()->setPlainText(note);
}
void MainWindow::on_addBtn_clicked()
{
    itemView *item = new itemView(this);
    item->show();

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollView->layout());
    layout->insertWidget(layout->count() - 1, item);
    connect(item, &itemView::itemClicked, this, &MainWindow::select_item);
    connect(item, &itemView::noteEdit, this, &MainWindow::note_edit);
    curr_item = qobject_cast<itemView*>(item);
    std::cout << curr_item << std::endl;
}
void MainWindow::on_rmBtn_clicked()
{
    if (curr_item)
    {
        if (curr_item->property("is_itemView").toBool())
        {
            curr_item->deleteLater();
            curr_item = nullptr;
        }
        else std::cout << "Mission incorrect, address is " << curr_item << std::endl;
    }
}

void MainWindow::on_upBtn_clicked()
{
    if (!curr_item) return;

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollView->layout());
    int curr_item_idx = layout->indexOf(curr_item);
    if (curr_item_idx > 0) layout->insertWidget(curr_item_idx - 1, curr_item);
}


void MainWindow::on_downBtn_clicked()
{
    if (!curr_item) return;

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollView->layout());
    int curr_item_idx = layout->indexOf(curr_item);
    if (curr_item_idx < (layout->count() - 1) - 1) layout->insertWidget(curr_item_idx + 1, curr_item);
}

