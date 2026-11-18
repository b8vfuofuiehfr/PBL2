#include "LoginDialog.h"
#include "RegisterDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), nguoiDung(nullptr)
{
    setWindowTitle("DANG NHAP HE THONG DANH BA (PBL2)");
    resize(380, 180);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *lblTitle = new QLabel("HE THONG QUAN LY DANH BA DIEN THOAI");
    lblTitle->setAlignment(Qt::AlignCenter);
    QFont f = lblTitle->font();
    f.setBold(true);
    f.setPointSize(11);
    lblTitle->setFont(f);
    mainLayout->addWidget(lblTitle);

    QFormLayout *form = new QFormLayout();
    txtUser = new QLineEdit();
    txtUser->setPlaceholderText("Tai khoan");
    txtPass = new QLineEdit();
    txtPass->setPlaceholderText("Mat khau");
    txtPass->setEchoMode(QLineEdit::Password);

    form->addRow("Tai khoan:", txtUser);
    form->addRow("Mat khau:", txtPass);
    mainLayout->addLayout(form);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnDangNhap = new QPushButton("Dang Nhap");
    btnMoDangKy = new QPushButton("Dang Ky Tai Khoan");
    btnLayout->addWidget(btnDangNhap);
    btnLayout->addWidget(btnMoDangKy);
    mainLayout->addLayout(btnLayout);

    connect(btnDangNhap, &QPushButton::clicked, this, &LoginDialog::onDangNhap);
    connect(btnMoDangKy, &QPushButton::clicked, this, &LoginDialog::onMoDangKy);
    connect(txtPass, &QLineEdit::returnPressed, this, &LoginDialog::onDangNhap);
}

LoginDialog::~LoginDialog()
{
    delete nguoiDung;
}

NguoiDung* LoginDialog::takeNguoiDung()
{
    NguoiDung* temp = nguoiDung;
    nguoiDung = nullptr;
    return temp;
}

void LoginDialog::onDangNhap()
{
    QString u = txtUser->text().trimmed();
    QString p = txtPass->text();

    if (u.isEmpty() || p.isEmpty()) {
        QMessageBox::warning(this, "Thieu thong tin", "Vui long nhap day du tai khoan va mat khau!");
        return;
    }

    NguoiDung* nd = QuanLyTaiKhoan::getInstance().dangNhap(u.toStdString(), p.toStdString());
    if (nd == nullptr) {
        QMessageBox::critical(this, "Loi", "Sai ten dang nhap hoac mat khau!");
        return;
    }

    delete nguoiDung;
    nguoiDung = nd;
    accept();
}

void LoginDialog::onMoDangKy()
{
    RegisterDialog dlg(this);
    dlg.exec();
}