#if !defined(RUNSCRIPT_H)
#define RUNSCRIPT_H

#include <QDebug>
#include <QProcess>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <QComboBox>


class RunmyScript
{
public:
    static void nmapscript(
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
    
    );

    static void nmapstop(
        QProcess *process,
        QWidget *parant,
        QPushButton *runbutton,
        QPushButton *stopbutton,
        QTextEdit *output


    );
};

#endif // run_H
