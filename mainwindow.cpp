#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "runscript.h"
#include <QFileDialog>
#include <cmd.h>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QClipboard>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->attackbtn->setEnabled(true);
    ui->pushButton_5_nmapstop->setEnabled(false);

    nmapoutput = ui->textEdit_2_nmapoutput;


    // getting local ip
    QHostAddress localIP;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for(const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            localIP = address;
            break;
        }
    }
    ui->label_ip->setText(localIP.toString());


    // getting router ip
    QString routerIP;
    QProcess routerProcess;
    #ifdef Q_OS_WIN
        routerProcess.start("ipconfig");
    #else
        routerProcess.start("ip", QStringList() << "route" << "show" << "default");
    #endif
    routerProcess.waitForFinished();
    QString output = routerProcess.readAllStandardOutput();
    QStringList lines = output.split('\n');
    for (const QString& line : lines) {
        if (line.contains("default")) {
            QStringList parts = line.simplified().split(' ');
            if (parts.size() > 2) {
                routerIP = parts[2];
                break;
            }
        }
    }
    ui->label_router->setText(routerIP);

    connect(ui->label_router, &QLabel::linkActivated,this,[this](){
        QClipboard *clipbp = QGuiApplication::clipboard();
        clipbp->setText(ui->label_router->text());
    });
    ui->label_router->setTextInteractionFlags(Qt::TextSelectableByMouse);


    // copy local ip to clipboard
    connect(ui->label_ip, &QLabel::linkActivated, this, [this]() {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(ui->label_ip->text());
    });
    ui->label_ip->setTextInteractionFlags(Qt::TextSelectableByMouse);



    intesecmd = ui->comboBox_4_intense;
    intesecmd->addItems({"Default",
                         "-T0 (Paranoid)",
                         "-T1 (Sneaky)",
                         "-T2 (Polite)",
                         "-T3 (Normal)",
                         "-T4 (Aggressive)",
                         "-T5 (Insane)"});

    subselectcommand = ui->comboBox_3_command;

    selectcommand = ui->comboBox_2;
    selectcommand->addItems({
        "Basic Scanning Commands",
        "Advanced Scanning Techniques",
        "Script Scanning",
        "Firewall/IDS Evasion",
        "Service and Vulnerability Detection",
        "Network Mapping",

    });

    targetipbox = ui->targetip;

    process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, [=]()
            { nmapoutput->append(process->readAllStandardOutput()); });

    connect(process, &QProcess::readyReadStandardError, [=]()
            { nmapoutput->append(process->readAllStandardError()); });

    connect(process, &QProcess::finished, [=](int exitcode, QProcess::ExitStatus exitstatus)
            {
                ui->attackbtn->setEnabled(true);
                ui->pushButton_5_nmapstop->setEnabled(false);
                nmapoutput->append("Processed finished " + QString::number(exitcode));
                nmapoutput->append("exit status: " + QString(exitstatus == QProcess::NormalExit ? "Normal exit" : "crash exit")); });

}

MainWindow::~MainWindow()
{
    delete ui;
}


// Nmap tab
void MainWindow::on_attackbtn_clicked()
{
    RunmyScript::nmapscript(this,process,ui->attackbtn,ui->pushButton_5_nmapstop,nmapoutput,selectcommand,subselectcommand,targetipbox,intesecmd,ui->lineEdit_4_filepath);

}

void MainWindow::on_pushButton_4_savebtn_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select Folder", QDir::homePath());
    if (!folderPath.isEmpty())
    {
        ui->lineEdit_4_filepath->setText(folderPath);
    }
}

void MainWindow::on_pushButton_5_nmapstop_clicked()
{
    RunmyScript::nmapstop(process, this, ui->attackbtn, ui->pushButton_5_nmapstop, nmapoutput);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    cmdcheck::cmdchange(arg1,selectcommand,subselectcommand);
  
}
