#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/calculate.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convert(int from, int to, CONVERTDIR flag)             //文本进制转换from -> to
{
    QString convertstring = "";
    QString orgstring, tostring;
    QStringList orglist;
    QTextBlock textline;
    QTextDocument *doc = ui->plainTextEdit->document();

    if (flag == TEXT1TOTEXT2) {
        ui->plainTextEdit_2->clear();
    } else if (flag == TEXT2TOTEXT1) {
        doc = ui->plainTextEdit_2->document();
        ui->plainTextEdit->clear();
    }

    long n;
    int cnt = doc->blockCount();
    for (int j = 0; j < cnt; j++) {
        textline = doc->findBlockByLineNumber(j);
        orgstring = textline.text();
        orgstring = orgstring.trimmed();
        qDebug() << "orgstring:" << orgstring << endl;
        orglist = orgstring.split(" ",QString::SkipEmptyParts);
        convertstring = "";
        for (int i = 0; i < orglist.count(); i++) {
            tostring = orglist.at(i);
            n = tostring.toLong(nullptr, from);
            tostring = tostring.setNum(n, to);
            convertstring = convertstring + tostring + " ";
        }
        if (flag == TEXT1TOTEXT2) {
            ui->plainTextEdit_2->appendPlainText(convertstring);
        } else if (flag == TEXT2TOTEXT1) {
            ui->plainTextEdit->appendPlainText(convertstring);
        }
    }
}

void MainWindow::convertAsciitoHex(CONVERTDIR flag)
{
    QTextBlock textline;
    QTextDocument *doc = ui->plainTextEdit->document();
    if (flag == TEXT1TOTEXT2) {
        ui->plainTextEdit_2->clear();
    } else if (flag == TEXT2TOTEXT1) {
        doc = ui->plainTextEdit_2->document();
        ui->plainTextEdit->clear();
    }
    int cnt = doc->blockCount();
    for (int i = 0; i < cnt; i++) {
        textline = doc->findBlockByLineNumber(i);
        QString orgstring = textline.text();
        orgstring = orgstring.trimmed();
        qDebug() << "orgstring:" << orgstring << endl;
        QByteArray orgarray = orgstring.toLatin1();
        QByteArray convertarray = orgarray.toHex(' ');

        if (flag == TEXT1TOTEXT2) {
            ui->plainTextEdit_2->appendPlainText(convertarray);
        } else if (flag == TEXT2TOTEXT1) {
            ui->plainTextEdit->appendPlainText(convertarray);
        }
    }
}

void MainWindow::convertHextoAscii(CONVERTDIR flag)
{
    QTextBlock textline;
    QTextDocument *doc = ui->plainTextEdit->document();
    if (flag == TEXT1TOTEXT2) {
        ui->plainTextEdit_2->clear();
    } else if (flag == TEXT2TOTEXT1) {
        doc = ui->plainTextEdit_2->document();
        ui->plainTextEdit->clear();
    }
    int cnt = doc->blockCount();
    for (int i = 0; i < cnt; i++) {
        textline = doc->findBlockByLineNumber(i);
        QString orgstring = textline.text();
        orgstring = orgstring.trimmed();
        qDebug() << "orgstring:" << orgstring << endl;
        QByteArray orgarray = orgstring.toLatin1();
        QByteArray convertarray = orgarray.fromHex(orgarray);
        if (flag == TEXT1TOTEXT2) {
            ui->plainTextEdit_2->appendPlainText(convertarray);
        } else if (flag == TEXT2TOTEXT1) {
            ui->plainTextEdit->appendPlainText(convertarray);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString mode = ui->comboBox->itemText(ui->comboBox->currentIndex());
    if (mode == QString("十六进制转换成十进制")) {
        convert(16, 10, TEXT1TOTEXT2);
    } else if (mode == QString("十进制转换成十六进制")) {
        convert(10, 16, TEXT1TOTEXT2);
    } else if (mode == QString("十六进制转换成二进制")) {
        convert(16, 2, TEXT1TOTEXT2);
    } else if (mode == QString("二进制转换成十六进制")) {
        convert(2, 16, TEXT1TOTEXT2);
    } else if (mode == QString("ASCII转换成十六进制")) {
        convertAsciitoHex(TEXT1TOTEXT2);
    } else if (mode == QString("十六进制转换成ASCII")) {
        convertHextoAscii(TEXT1TOTEXT2);
    }
}

void MainWindow::on_pBtn_Clear_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pBtn_Clear2_clicked()
{
    ui->plainTextEdit_2->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString mode = ui->comboBox_2->itemText(ui->comboBox_2->currentIndex());
    if (mode == QString("十六进制转换成十进制")) {
        convert(16, 10, TEXT2TOTEXT1);
    } else if (mode == QString("十进制转换成十六进制")) {
        convert(10, 16, TEXT2TOTEXT1);
    } else if (mode == QString("十六进制转换成二进制")) {
        convert(16, 2, TEXT2TOTEXT1);
    } else if (mode == QString("二进制转换成十六进制")) {
        convert(2, 16, TEXT2TOTEXT1);
    } else if (mode == QString("ASCII转换成十六进制")) {
        convertAsciitoHex(TEXT2TOTEXT1);
    } else if (mode == QString("十六进制转换成ASCII")) {
        convertHextoAscii(TEXT2TOTEXT1);
    }
}
