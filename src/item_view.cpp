#include "item_view.h"
#include "ui_item_view.h"
#include <QMouseEvent>

itemView::itemView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::itemView)
{
    ui->setupUi(this);

    this->setProperty("is_itemView", true);
}

itemView::~itemView()
{
    delete ui;
}

void itemView::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        emit itemClicked();
    }

    if (event->button() == Qt::RightButton)
    {
        emit noteEdit();
    }

}

void itemView::on_itemCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    this->deleteLater();
}

QTextEdit *itemView::get_textView()
{
    return ui->textView;
}
