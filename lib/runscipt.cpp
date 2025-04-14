#include "runscript.h"

void RunmyScript::nmapscript(
    QWidget *parent,
    QProcess *process,
    QPushButton *attackbtn,
    QPushButton *pushButton_5_nmapstop,
    QTextEdit *nmapoutput,
    QComboBox *selectcommand,
    QComboBox *subselectcommand,
    QLineEdit *targetipbox,
    QComboBox *intesecmd,
    QLineEdit *lineEdit_4_filepath

)
{

    nmapoutput->clear(); //this is for output 


    attackbtn->setEnabled(false);
    pushButton_5_nmapstop->setEnabled(true);

    auto intence = intesecmd->currentText();
    auto cmdargs = subselectcommand->currentText();
    auto fp = lineEdit_4_filepath->text();

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
        QMessageBox::warning(parent, "Error", "Target IP is missing. Please enter a valid target IP address.");
    }
}

void RunmyScript::nmapstop(
    QProcess *process,
    QWidget *parent,
    QPushButton *runbutton,
    QPushButton *stopbutton,
    QTextEdit *output

)
{
    if (process && process->state() == QProcess::Running)
    {
        process->terminate();
        if (!process->waitForFinished(3000))
        {
            process->kill();
        }
        QMessageBox::information(parent, "script Runner", "Process Terminated");
    }

    runbutton->setEnabled(true);
    stopbutton->setEnabled(false);
}