#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "runscript.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mytextoutput = ui->textEdit;
    mytextoutput->setReadOnly(true);

    scriptpath = ui->lineEdit_2;

    process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, [=]()
            { mytextoutput->append(process->readAllStandardOutput()); });

    connect(process, &QProcess::readyReadStandardError, [=]()
            { mytextoutput->append(process->readAllStandardError()); });

    connect(process, &QProcess::finished, [=](int exitcode, QProcess::ExitStatus exitstatus)
            {
                mytextoutput->append("Processed finished " + QString::number(exitcode));
                mytextoutput->append("exit status: " + QString(exitstatus == QProcess::NormalExit ? "Normal exit" : "crash exit")); });

    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    // run button
    RunmyScript::nmapscript(process,scriptpath, ui->pushButton_3, ui->pushButton_2, mytextoutput, this);
}

void MainWindow::on_pushButton_2_clicked()
{
    // process stop button
    RunmyScript::nmapstop(process,this,ui->pushButton_3,ui->pushButton_2,mytextoutput);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Nmap (Network Scanner)")
    {
        ui->lineEdit->setText("/usr/bin/nmap");
        ui->lineEdit_2->setText("-sV -p 1-1000 localhost");
    }
    else
    {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }
}
