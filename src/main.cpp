#include <QApplication>
#include <QTimer>
#include "LoginDialog.h"
#include "DanhBaWindow.h"

class AppController : public QObject
{
public:
    void moDangNhap()
    {
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            QApplication::quit();
            return;
        }

        NguoiDung* nd = login.takeNguoiDung();
        DanhBaWindow *w = nullptr;

        if (nd != nullptr && nd->coQuyenChinhSua()) {
            w = new AdminWindow(nd);
        } else {
            w = new UserWindow(nd);
        }

        w->setAttribute(Qt::WA_DeleteOnClose);
        connect(w, &DanhBaWindow::dangXuat, this, &AppController::moDangNhap, Qt::QueuedConnection);
        w->show();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    AppController controller;
    QTimer::singleShot(0, &controller, &AppController::moDangNhap);

    return a.exec();
}