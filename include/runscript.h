#if !defined(RUNSCRIPT_H)
#define RUNSCRIPT_H

#include <QDebug>
#include <QProcess>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QMessageBox>

class RunmyScript
{
public:
    static void nmapscript(
        QProcess *process,
        QLineEdit *programpath,
        QPushButton *runbutton,
        QPushButton *stopbutton,
        QTextEdit *output,
        QWidget *parent);

    static void nmapstop(
        QProcess *process,
        QWidget *parant,
        QPushButton *runbutton,
        QPushButton *stopbutton,
        QTextEdit *output


    );
};

#endif // run_H
