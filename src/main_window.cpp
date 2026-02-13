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
    QString curr_note = curr_item->get_textView()->toPlainText();

    noteView *note = new noteView(nullptr);
    note->show();
    note->get_editView()->setPlainText(curr_note);

    connect(note, &noteView::finish_edit, this, &MainWindow::push_edit);
}

void MainWindow::push_edit(QString note)
{
    curr_item->get_textView()->setPlainText(note);

    QFile local_note(QDir::homePath() + "/.local/share/Simpato/notes/note_" + QString::number(local_notes[curr_item]) + ".txt");
    local_note.open(QIODevice::WriteOnly);
    QTextStream out(&local_note);
    out << note;      // 写入内容，覆盖原有数据
    local_note.close();
}

void MainWindow::on_addBtn_clicked()
{
    create_item();

    QFile local_note(QDir::homePath() + "/.local/share/Simpato/notes/note_" + QString::number(QDateTime::currentSecsSinceEpoch()) + ".txt");
    local_notes[curr_item] = QDateTime::currentSecsSinceEpoch();
    local_note.open(QIODevice::NewOnly);
    local_note.close();

}

void MainWindow::on_rmBtn_clicked()
{
    if (curr_item)
    {
        if (curr_item->property("is_itemView").toBool())
        {
            curr_item->deleteLater();
            rm_note();
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

void MainWindow::create_item()
{
    itemView *item = new itemView(this);
    item->show();

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollView->layout());
    layout->insertWidget(layout->count() - 1, item);

    connect(item, &itemView::itemClicked, this, &MainWindow::select_item);
    connect(item, &itemView::noteEdit, this, &MainWindow::note_edit);
    connect(item, &itemView::noteRmed, this, &MainWindow::rm_note);

    curr_item = qobject_cast<itemView*>(item);
    std::cout << curr_item << std::endl;
}

void MainWindow::release_curr_ptr()
{
    curr_item = NULL;
}

void MainWindow::rm_note()
{
    QFile::remove(QDir::homePath() + "/.local/share/Simpato/notes/note_" + QString::number(local_notes[curr_item]) + ".txt");
    release_curr_ptr();
}

void MainWindow::process_notes(const QString folder_path)
{
    QDir dir(folder_path);

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QFileInfoList fileList = dir.entryInfoList();

    QMap<int, QString> fileMap;  // 自动按数字排序

    // re
    QRegularExpression re("(\\d+)");  // 匹配连续数字

    for (const QFileInfo& fileInfo : fileList) {
        QString note_name = fileInfo.fileName();  // 获取文件名（不含路径）
        qDebug() << "Processing:" << note_name;

        QRegularExpressionMatch match = re.match(note_name);
        if (match.hasMatch()) {
            bool ok;
            int number = match.captured(1).toInt(&ok);  // 提取第一个匹配的数字

            if (ok) {
                create_item();

                local_notes[curr_item] = number;

                std::cout << local_notes[curr_item] << std::endl;
                std::cout << number << std::endl;

                QFile local_note(fileInfo.absoluteFilePath());
                local_note.open(QIODevice::ReadOnly);
                QTextStream stream(&local_note);
                stream.setEncoding(QStringConverter::Utf8);
                QString note = stream.readAll();
                local_note.close();

                push_edit(note);
                // fileMap[number] = fileInfo.absoluteFilePath();  // 存储到map
                // qDebug() << "  Extracted number:" << number;
            } else {
                qDebug() << "  Failed to convert to int";
            }
        } else {
            qDebug() << "  No number found in filename";
        }
    }

    qDebug() << "/.local/share/Simpato/notes/note_" + QString::number(local_notes[curr_item]) + ".txt";

}
