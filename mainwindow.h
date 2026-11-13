#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets> // <-- GOM TOÀN BỘ CÁC THÀNH PHẦN GIAO DIỆN VÀO 1 DÒNG NÀY!
#include "QuanLyDanhBa.h"
#include "ThanhPho.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QComboBox *cbTinh;
    QPushButton *btnThemTinh;
    QPushButton *btnXoaTinh;

    QTableWidget *tableDanhBa;

    QLineEdit *txtTimKiem;
    QPushButton *btnTimKiem;
    QPushButton *btnThemThueBao;
    QPushButton *btnSuaThueBao;
    QPushButton *btnXoaThueBao;
    QPushButton *btnSapXep;
    QPushButton *btnXoaTrung;

    void taiDanhSachTinh();
    void hienThiLenBang(const string& tenTinh);

private slots:
    void onChonTinh(int index);
    void onThemTinh();
    void onXoaTinh();
    void onThemThueBao();
    void onSuaThueBao();
    void onXoaThueBao();
    void onTimKiem();
    void onSapXep();
    void onXoaTrung();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif