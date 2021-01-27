#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextBlock>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum CONVERTDIR {
        TEXT1TOTEXT2,
        TEXT2TOTEXT1
    };
    void convert(int from, int to, CONVERTDIR flag);      //进制转换from->to

    void convertAsciitoHex(CONVERTDIR flag); //ascii字符串转换成十六进制字符串

    void convertHextoAscii(CONVERTDIR flag); //十六进制字符串转换成ascii字符串

private slots:
    void on_pushButton_clicked();

    void on_pBtn_Clear_clicked();

    void on_pBtn_Clear2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
