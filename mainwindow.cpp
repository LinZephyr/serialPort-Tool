#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    layoutInit();
    scanSerialPort();
    baudRateItemInit();
    dataBitsItemInit();
    parityItemInit();
    stopBitsItemInit();
}

MainWindow::~MainWindow()
{
}

void MainWindow::layoutInit()
{
    this->resize(800, 480);

    serialPort = new QSerialPort(this);
    //textBrowser = new QTextBrowser();
    //textEdit = new QTextEdit();
    vboxLayout = new QVBoxLayout();
    funcWidget = new QWidget();
    mainWidget = new QWidget();
    gridLayout = new QGridLayout();

    QList <QString> list1;
    list1<<"串口号:"<<"波特率:"<<"数据位:"<<"校验位:"<<"停止位:";

    for(int i=0; i<5; i++) {
        label[i] = new QLabel(list1[i]);
        label[i]->setMinimumSize(80, 30);
        label[i]->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
            );
        gridLayout->addWidget(label[i], 0, i);
    }

    for(int i=0; i<5; i++) {
        comboBox[i] = new QComboBox();
        comboBox[i]->setMinimumSize(80, 30);
        comboBox[i]->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
            );
        gridLayout->addWidget(comboBox[i], 1, i);
    }

    QList <QString> list2;
    list2 << "开始测试" << "打开串口";

    for(int i=0; i<2; i++) {
        pushButton[i] = new QPushButton(list2[i]);
        pushButton[i]->setMaximumSize(80, 30);
        gridLayout->addWidget(pushButton[i], i, 5);
    }
    pushButton[0]->setEnabled(false);

    QList <QString> list3;
    list3<<"重启"<<"容触版本号"<<"获取容触diff值"<<"容触diff值"<<"启动容触中断检测"<<"容触中断检测结果";
    for(int i=0; i<6; i++) {
        label1[i] = new QLabel(list3[i]);
        label1[i]->setMinimumSize(800, 10);
        label1[i]->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
            );
        label1[i]->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
        vboxLayout->addWidget(label1[i]);
    }



    //vboxLayout->addWidget(textBrowser);
    //vboxLayout->addWidget(textEdit);
    funcWidget->setLayout(gridLayout);
    vboxLayout->addWidget(funcWidget);

    mainWidget->setLayout(vboxLayout);
    this->setCentralWidget(mainWidget);


    connect(pushButton[0], SIGNAL(clicked()),
            this, SLOT(sendPushButtonClicked()));

    connect(pushButton[1], SIGNAL(clicked()),
            this, SLOT(openSerialPortPushButtonClicked()));
    /*
    connect(serialPort, SIGNAL(readyRead()),
            this, SLOT(serialPortReadyRead()));
    */
}

void MainWindow::scanSerialPort()
{
    foreach(const QSerialPortInfo &info,
             QSerialPortInfo::availablePorts()) {
        comboBox[0]->addItem(info.portName());
    }
}

void MainWindow::baudRateItemInit()
{
    QList <QString> list;
    list << "1200" << "2400" << "4800" << "9600"
        << "19200" << "38400" << "57600"
        << "115200" << "230400" << "460800"
        << "921600";
    for(int i=0; i<11; i++) {
        comboBox[1]->addItem(list[i]);
    }
    comboBox[1]->setCurrentIndex(7);
}

void MainWindow::dataBitsItemInit()
{
    QList <QString> list;
    list << "5" << "6" << "7" << "8";
    for(int i=0; i<4; i++) {
        comboBox[2]->addItem(list[i]);
    }
    comboBox[2]->setCurrentIndex(3);
}
void MainWindow::parityItemInit()
{
    QList <QString> list;
    list << "None" << "Even" << "Odd" << "Space" << "Mark";
    for(int i=0; i<5; i++) {
        comboBox[3]->addItem(list[i]);
    }
    comboBox[3]->setCurrentIndex(0);
}
void MainWindow::stopBitsItemInit()
{
    QList <QString> list;
    list << "1" << "2";
    for(int i=0; i<2; i++) {
        comboBox[4]->addItem(list[i]);
    }
    comboBox[4]->setCurrentIndex(0);
}


void MainWindow::sendPushButtonClicked()
{
    //QByteArray data = textEdit->toPlainText().toUtf8();
    //serialPort->write(data);

    label1[0]->setStyleSheet("QLabel{background-color:rgb(34,139,34);}");
    QThread::sleep(2);
    label1[1]->setStyleSheet("QLabel{background-color:rgb(34,139,34);}");
    QThread::sleep(2);
}


void MainWindow::openSerialPortPushButtonClicked()
{
    if (pushButton[1]->text() == "打开串口") {
        /* 设置串口名 */
        serialPort->setPortName(comboBox[0]->currentText());
        /* 设置波特率 */
        serialPort->setBaudRate(comboBox[1]->currentText().toInt());
        /* 设置数据位数 */
        switch (comboBox[2]->currentText().toInt()) {
        case 5:
            serialPort->setDataBits(QSerialPort::Data5);
            break;
        case 6:
            serialPort->setDataBits(QSerialPort::Data6);
            break;
        case 7:
            serialPort->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            serialPort->setDataBits(QSerialPort::Data8);
            break;
        default: break;
        }
        /* 设置奇偶校验 */
        switch (comboBox[3]->currentIndex()) {
        case 0:
            serialPort->setParity(QSerialPort::NoParity);
            break;
        case 1:
            serialPort->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            serialPort->setParity(QSerialPort::OddParity);
            break;
        case 3:
            serialPort->setParity(QSerialPort::SpaceParity);
            break;
        case 4:
            serialPort->setParity(QSerialPort::MarkParity);
            break;
        default: break;
        }
        /* 设置停止位 */
        switch (comboBox[4]->currentText().toInt()) {
        case 1:
            serialPort->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serialPort->setStopBits(QSerialPort::TwoStop);
            break;
        default: break;
        }
        /* 设置流控制 */
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        if (!serialPort->open(QIODevice::ReadWrite))
            QMessageBox::about(NULL, "错误",
                               "串口无法打开！可能串口已经被占用！");
        else {
            for (int i = 0; i < 5; i++)
                comboBox[i]->setEnabled(false);
            pushButton[1]->setText("关闭串口");
            pushButton[0]->setEnabled(true);
        }
    } else {
        serialPort->close();
        for (int i = 0; i < 5; i++)
            comboBox[i]->setEnabled(true);
        pushButton[1]->setText("打开串口");
        pushButton[0]->setEnabled(false);

        for(int i=0; i<6; i++) {
            label1[i]->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
        }
    }
}
/*
void MainWindow::serialPortReadyRead()
{
    QByteArray buf = serialPort->readAll();
    textBrowser->insertPlainText(QString(buf));
}
*/
