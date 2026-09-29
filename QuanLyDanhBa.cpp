#include "QuanLyDanhBa.h"
#include "ThanhPho.h"
#include <iostream>
#include <fstream>

using namespace std;

QuanLyDanhBa::QuanLyDanhBa()
{
    ifstream file("data/0_DanhSachTinh.dat");
    if (!file) return;
    
    dsTinh.clear();
    string tenTinh;

    while (getline(file, tenTinh))
        if (!tenTinh.empty()) dsTinh.push_back(tenTinh);
    file.close();
}

QuanLyDanhBa::~QuanLyDanhBa(){}


void QuanLyDanhBa::themTinh(string tinh) {
    for (string x : dsTinh) 
        if (x == tinh)  return;

    dsTinh.push_back(tinh);

    ofstream fileMucLuc("data/.0_DanhSachTinh.dat", ios::app);
    if (fileMucLuc){
        fileMucLuc << tinh << endl;
        fileMucLuc.close();
    }
}

void QuanLyDanhBa::themThueBao() 
{
    string tinh;
    cout << "Nhap tinh thanh (khong dung khoang trang): ";
    cin >> tinh;

    themTinh(tinh);

    ThanhPho tp(tinh);
    tp.themThueBao();
}

void QuanLyDanhBa::lietKeTheoTinh() 
{
    string tinh;
    cout << "Nhap tinh can xem: ";
    cin >> tinh;

    ThanhPho tp(tinh);
    tp.lietKeDanhBa();
}

void QuanLyDanhBa::thongKeTheoTinh() 
{
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

void QuanLyDanhBa::hienThiTinh() 
{
    cout << "\n===== CAC TINH DANG QUAN LY =====\n";

    if (dsTinh.empty()) {
        cout << "Danh sach rong!\n";
        return;
    }

    for (string tinh : dsTinh) {
        cout << tinh << endl;
    }
}

void QuanLyDanhBa::kiemTraXoaTrung() 
{
    string tinh;
    cout << "Nhap tinh can kiem tra: ";
    cin >> tinh;

    ThanhPho tp(tinh);
    tp.xoaSoTrung();
}
