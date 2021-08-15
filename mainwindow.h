#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLabel *label1[6];

private:
    QSerialPort *serialPort;
    //QTextBrowser *textBrowser;
    //QTextEdit *textEdit;
    QLabel *label[5];
    QPushButton *pushButton[2];
    QComboBox *comboBox[5];

    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    
    QWidget *mainWidget;
    QWidget *funcWidget;

    void layoutInit();
    void scanSerialPort();
    void baudRateItemInit();
    void dataBitsItemInit();
    void parityItemInit();
    void stopBitsItemInit();

private slots:
    void sendPushButtonClicked();
    void openSerialPortPushButtonClicked();
    //void serialPortReadyRead();
};


#endif // MAINWINDOW_H
