#include "note_view.h"
#include "ui_note_view.h"
#include <iostream>
#include <string>

noteView::noteView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::noteView)
{
    ui->setupUi(this);

    this->setWindowTitle("Change note here :D");
}

noteView::~noteView()
{
    delete ui;
}

void noteView::on_dialBtns_rejected()
{
    this->deleteLater();
}

void noteView::on_dialBtns_accepted()
{
    edited_note = ui->editView->toPlainText();
    this->deleteLater();
    emit finish_edit(edited_note);

    //测试
    QByteArray byteArr = edited_note.toLocal8Bit();
    std::string str = std::string(byteArr);
    std::cout << str << std::endl;
}

QTextEdit *noteView::get_editView()
{
    return ui->editView;
}
