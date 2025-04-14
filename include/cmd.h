#if !defined(CMD_H)
#define CMD_H

#include <QComboBox>
#include <QString>

class cmdcheck {
    public:
        static void cmdchange(
            const QString &arg1,
            QComboBox *selectcommand,
            QComboBox *subselectcommand
        );
};

#endif // CMD_H
