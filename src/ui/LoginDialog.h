#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtWidgets>
#include "NguoiDung.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *txtUser;
    QLineEdit *txtPass;
    QPushButton *btnDangNhap;
    QPushButton *btnMoDangKy;

    NguoiDung* nguoiDung;

private slots:
    void onDangNhap();
    void onMoDangKy();

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    NguoiDung* takeNguoiDung();
};

#endif
