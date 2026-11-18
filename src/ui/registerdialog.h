#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QtWidgets>
#include "NguoiDung.h"

class RegisterDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *txtUser;
    QLineEdit *txtPass;
    QLineEdit *txtConfirmPass;
    QPushButton *btnXacNhan;
    QPushButton *btnHuy;

private slots:
    void onDangKy();

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
};

#endif