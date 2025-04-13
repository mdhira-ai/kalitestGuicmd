#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_attackbtn_clicked();
    void on_pushButton_5_nmapstop_clicked();
    void on_pushButton_4_savebtn_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QTextEdit *mytextoutput;
    QTextEdit *nmapoutput;
    QProcess *process;
    QLineEdit *scriptpath;
    QLineEdit *targetipbox;

    QComboBox *intesecmd;
    QComboBox *selectcommand;
    QComboBox *subselectcommand;

};
#endif // MAINWINDOW_H
