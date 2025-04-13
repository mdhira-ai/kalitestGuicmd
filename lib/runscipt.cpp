#include "runscript.h"

void RunmyScript::nmapscript(
    QProcess *process,
    QLineEdit *programpath,
    QPushButton *runbutton,
    QPushButton *stopbutton,
    QTextEdit *output,
    QWidget *parent)
{

    auto scriptpath = programpath->text();
    if (scriptpath.isEmpty())
    {
        QMessageBox::warning(parent, "error", "Please specify a script to run");
        return;
    }

    output->clear();

    try
    {
        process->start("ping", QStringList() << "google.com");
        // process->start("/usr/bin/nmap",);
        output->append("process started...");
    }
    catch (const std::exception &e)
    {
        output->append(QString(e.what()));
    }

    runbutton->setEnabled(false);
    stopbutton->setEnabled(true);
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