#include "QuanLyDanhBa.h"
#include "ThanhPho.h"
#include <iostream>

using namespace std;

void QuanLyDanhBa::themTinh(string tinh) {
    for (string x : dsTinh) {
        if (x == tinh) {
            cout << tinh << "da ton tai trong danh sach!\n" << endl;
            return;
        }
    }

    dsTinh.push_back(tinh);
}

void QuanLyDanhBa::themThueBao() {
    string tinh;
    cout << "Nhap tinh thanh (khong dung khoang trang): ";
    cin >> tinh;

    themTinh(tinh);

    ThanhPho tp(tinh);
    tp.themThueBao();
}

void QuanLyDanhBa::lietKeTheoTinh() {
    string tinh;
    cout << "Nhap tinh can xem: ";
    cin >> tinh;

    ThanhPho tp(tinh);
    tp.lietKeDanhBa();
}

void QuanLyDanhBa::thongKeTheoTinh() {
    cout << "\n===== THONG KE =====\n";

    if (dsTinh.empty()) {
        cout << "Chua co du lieu!\n";
        return;
    }

    for (string tinh : dsTinh) {
        ThanhPho tp(tinh);
        cout << tinh << " : "
             << tp.demSoLuongThueBao()
             << " thue bao" << endl;
    }
}

void QuanLyDanhBa::hienThiTinh() {
    cout << "\n===== CAC TINH DANG QUAN LY =====\n";

    if (dsTinh.empty()) {
        cout << "Danh sach rong!\n";
        return;
    }

    for (string tinh : dsTinh) {
        cout << tinh << endl;
    }
}

void QuanLyDanhBa::kiemTraXoaTrung() {
    string tinh;
    cout << "Nhap tinh can kiem tra: ";
    cin >> tinh;

    ThanhPho tp(tinh);
    tp.xoaSoTrung();
}
