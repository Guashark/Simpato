#ifndef ITEM_VIEW_H
#define ITEM_VIEW_H

#include <QWidget>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class itemView;
}
QT_END_NAMESPACE

class itemView : public QWidget
{
    Q_OBJECT

public:
    itemView(QWidget *parent);
    ~itemView();
    QTextEdit *get_textView();

signals:
    void noteRmed();

private:
    Ui::itemView *ui;

signals:
    void itemClicked();
    void noteEdit();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_itemCheckBox_checkStateChanged(const Qt::CheckState &arg1);
};

#endif // ITEM_VIEW_H
