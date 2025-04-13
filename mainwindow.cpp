#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "runscript.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->attackbtn->setEnabled(true);
    ui->pushButton_5_nmapstop->setEnabled(false);

    nmapoutput = ui->textEdit_2_nmapoutput;
    mytextoutput = ui->textEdit;
    mytextoutput->setReadOnly(true);
    scriptpath = ui->lineEdit_2;

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
    RunmyScript::nmapscript(process, scriptpath, ui->pushButton_3, ui->pushButton_2, mytextoutput, this);
}

void MainWindow::on_pushButton_2_clicked()
{
    // process stop button
    RunmyScript::nmapstop(process, this, ui->pushButton_3, ui->pushButton_2, mytextoutput);
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

void MainWindow::on_attackbtn_clicked()
{
    nmapoutput->clear();
    ui->attackbtn->setEnabled(false);
    ui->pushButton_5_nmapstop->setEnabled(true);

    auto intence = intesecmd->currentText();
    auto cmdargs = subselectcommand->currentText();
    qDebug() << intence.split(" ").first() << cmdargs.split(" ").first();
    auto fp = ui->lineEdit_4_filepath->text();

    if (!targetipbox->text().isEmpty())
    {

        QStringList arguments;

        //TODO: need to make save ext .xml .txt

        // Check if the intensity command is set to "Default"
        if (intence.split(" ").first() == "Default")
        {
            // If a file path is provided, add output file arguments
            if (!fp.isEmpty())
            {
            arguments << "-oX" << fp + "/outnmap.xml";
            }
            // Otherwise, add the target IP and selected command arguments
            arguments << targetipbox->text()
                  << cmdargs.split(" ").first();
        }
        else
        {
            // If a file path is provided, add output file arguments
            if (!fp.isEmpty())
            {
            arguments << "-oX" << fp + "/outnmap.xml";
            }
            // Otherwise, add the target IP, intensity, and selected command arguments
            arguments << targetipbox->text()
                  << intence.split(" ").first()
                  << cmdargs.split(" ").first();
        }

        // Start the process with the constructed arguments
        if (process)
        {
            process->start("/usr/bin/nmap", arguments);
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Target IP is missing. Please enter a valid target IP address.");
    }

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
    RunmyScript::nmapstop(process, this, ui->pushButton_3, ui->pushButton_2, mytextoutput);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Basic Scanning Commands")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"-sS (TCP SYN scan)",
                                    "-sT (TCP connect scan)",
                                    "-sU (UDP scan)",
                                    "-sP (Ping scan)",
                                    "-sL (List scan)"});
    }
    else if (arg1 == "Advanced Scanning Techniques")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-sA (ACK scan)",
            "-sW (Window scan)",
            "-sM (TCP Maimon scan)",
            "-sN (TCP Null scan)",
            "-sF (TCP FIN scan)"
            "-p- (Scan all ports)",
            "--top-ports (Scan top ports: 20)" // TODO: add port lineedit
        });
    }
    else if (arg1 == "Script Scanning")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"--script=default",
                                    "--script=vuln",
                                    "--script=discovery",
                                    "--script=safe"});
    }
    else if (arg1 == "Firewall/IDS Evasion")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-f (Fragment packets)",
            "--mtu (Set custom MTU)",
            "-D (Decoy scan)",
            "-S (Spoof source address)",
            "--data-length (Append random data)",
            "-PA (Use TCP ACK packets for discovery)",
            "-PS (Use TCP SYN packets for discovery)",
            "--source-port (Randomize source port)" // TODO:need to add port lineedit
        });
    }
    else if (arg1 == "Service and Vulnerability Detection")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-sV (Service version detection)",
            "--version-intensity",
            "--version-light",
            "--version-all",
            "--script=vuln",
            "-O (OS detection)",
            "-p (Scan for specific services)" // TODO: need to add nmap -p 22,53,110,143 192.168.1.1

        });
    }
    else if (arg1 == "Network Mapping")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"-sn (Ping scan)",
                                    "-PE (ICMP echo request)",
                                    "-PP (ICMP timestamp request)",
                                    "-PM (ICMP address mask request)",
                                    "-PO (Protocol ping)",
                                    "-sL (List targets without scanning)",
                                    "--iflist (Show interfaces and routes) "

        });
    }

    else
    {
        subselectcommand->clear();
    }
}
