#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("DANG KY TAI KHOAN USER");
    resize(360, 200);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *lblTitle = new QLabel("TAO TAI KHOAN NGUOI DUNG MOI");
    lblTitle->setAlignment(Qt::AlignCenter);
    QFont f = lblTitle->font();
    f.setBold(true);
    lblTitle->setFont(f);
    mainLayout->addWidget(lblTitle);

    QFormLayout *form = new QFormLayout();
    txtUser = new QLineEdit();
    txtUser->setPlaceholderText("Nhap ten dang nhap");

    txtPass = new QLineEdit();
    txtPass->setPlaceholderText("Nhap mat khau");
    txtPass->setEchoMode(QLineEdit::Password);

    txtConfirmPass = new QLineEdit();
    txtConfirmPass->setPlaceholderText("Nhap lai mat khau");
    txtConfirmPass->setEchoMode(QLineEdit::Password);

    form->addRow("Tai khoan:", txtUser);
    form->addRow("Mat khau:", txtPass);
    form->addRow("Xac nhan:", txtConfirmPass);
    mainLayout->addLayout(form);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnXacNhan = new QPushButton("Dang Ky");
    btnHuy     = new QPushButton("Huy");
    btnLayout->addWidget(btnXacNhan);
    btnLayout->addWidget(btnHuy);
    mainLayout->addLayout(btnLayout);

    connect(btnXacNhan, &QPushButton::clicked, this, &RegisterDialog::onDangKy);
    connect(btnHuy, &QPushButton::clicked, this, &QDialog::reject);
    connect(txtConfirmPass, &QLineEdit::returnPressed, this, &RegisterDialog::onDangKy);
}

void RegisterDialog::onDangKy()
{
    QString u = txtUser->text().trimmed();
    QString p = txtPass->text();
    QString cp = txtConfirmPass->text();

    if (u.isEmpty() || p.isEmpty() || cp.isEmpty()) {
        QMessageBox::warning(this, "Thieu thong tin", "Vui long nhap day du cac truong!");
        return;
    }
    if (u.contains("|") || p.contains("|")) {
        QMessageBox::warning(this, "Khong hop le", "Khong duoc chua ky tu '|'.");
        return;
    }
    if (p != cp) {
        QMessageBox::warning(this, "Loi", "Mat khau xac nhan khong khop!");
        return;
    }

    if (QuanLyTaiKhoan::getInstance().dangKyUser(u.toStdString(), p.toStdString())) {
        QMessageBox::information(this, "Thanh cong", "Dang ky tai khoan User thanh cong!");
        accept();
    } else {
        QMessageBox::critical(this, "That bai", "Ten dang nhap da ton tai!");
    }
}