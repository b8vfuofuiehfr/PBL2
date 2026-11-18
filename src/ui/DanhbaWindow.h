#ifndef DANHBAWINDOW_H
#define DANHBAWINDOW_H

#include <QtWidgets>
#include "QuanLyDanhBa.h"
#include "ThanhPho.h"
#include "NguoiDung.h"

// ================= LOP TRU TUONG (ABSTRACT CLASS) =================
class DanhBaWindow : public QMainWindow
{
    Q_OBJECT

protected:
    NguoiDung* currentUser;
    bool isLoggingOut;

    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;

    QLabel *lblVaiTro;
    QLabel *lblThongKe;
    QPushButton *btnDangXuat;

    QComboBox *cbTinh;
    QLineEdit *txtTimKiem;
    QPushButton *btnTimKiem;
    QPushButton *btnSapXep;
    QPushButton *btnThongKe;

    QTableWidget *tableDanhBa;

    void khoiTao();
    void thietLapGiaoDienChung();
    virtual void thietLapChucNangRieng() = 0; // Ham thuan ao -> Abstract Class

    void taiDanhSachTinh();
    void hienThiLenBang(const string& tenTinh);
    void closeEvent(QCloseEvent *event) override;

signals:
    void dangXuat();

protected slots:
    void onDangXuat();
    void onChonTinh(int index);
    void onTimKiem();
    void onSapXep();
    void onThongKe();

public:
    DanhBaWindow(NguoiDung* user, QWidget *parent = nullptr);
    virtual ~DanhBaWindow();
};

// ================= GIAO DIEN ADMIN =================
class AdminWindow : public DanhBaWindow
{
    Q_OBJECT

private:
    QPushButton *btnThemTinh;
    QPushButton *btnXoaTinh;
    QPushButton *btnThemThueBao;
    QPushButton *btnSuaThueBao;
    QPushButton *btnXoaThueBao;
    QPushButton *btnXoaTrung;

protected:
    void thietLapChucNangRieng() override;

private slots:
    void onThemTinh();
    void onXoaTinh();
    void onThemThueBao();
    void onSuaThueBao();
    void onXoaThueBao();
    void onXoaTrung();

public:
    AdminWindow(NguoiDung* user, QWidget *parent = nullptr);
};

// ================= GIAO DIEN USER =================
class UserWindow : public DanhBaWindow
{
    Q_OBJECT

protected:
    void thietLapChucNangRieng() override;

public:
    UserWindow(NguoiDung* user, QWidget *parent = nullptr);
};

#endif
