#ifndef NOTE_VIEW_H
#define NOTE_VIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class noteView;
}
QT_END_NAMESPACE

class noteView : public QWidget
{
    Q_OBJECT

public:
    noteView(QWidget *parent);
    ~noteView();
    QString edited_note = NULL;

private slots:
    void on_dialBtns_rejected();

    void on_dialBtns_accepted();

private:
    Ui::noteView *ui;

signals:
    void finish_edit(QString note);
};

#endif // NOTE_VIEW_H
