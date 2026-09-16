#include "QuanLyDanhBa.h"
#include "ThanhPho.h"
#include <iostream>
#include <fstream>

using namespace std;

QuanLyDanhBa::~QuanLyDanhBa(){}

QuanLyDanhBa::QuanLyDanhBa()
{
    ifstream file("DanhSachTinh.dat");

    if (!file){
        cout << "Khong mo duoc file DanhSachTinh.dat!\n";
        return;
    }

    dsTinh.clear();

    string tenTinh;

    while (getline(file, tenTinh)){
        if (!tenTinh.empty()) 
            dsTinh.push_back(tenTinh);
    }

    file.close();
}

void QuanLyDanhBa::themTinh(string tinh) 
{
    for (string x : dsTinh) 
        if (x == tinh){
            cout << tinh << "da ton tai trong danh sach!\n" << endl;
            return;
        }
    

    dsTinh.push_back(tinh);

    ofstream fileMucLuc("DanhSachTinh.dat", ios::app); 
    if (fileMucLuc) {
        fileMucLuc << tinh << endl;
        fileMucLuc.close();
    }
}

void QuanLyDanhBa::themThueBao(string tinh) 
{
    themTinh(tinh);
    ThanhPho tp(tinh);
    tp.themThueBao();
}

void QuanLyDanhBa::lietKeTheoTinh(string tinh) 
{
    ThanhPho tp(tinh);
    tp.lietKeDanhBa();
}

void QuanLyDanhBa::thongKeTheoTinh() 
{
    cout << "\n===== THONG KE =====\n";

    if (dsTinh.empty()){
        cout << "Chua co du lieu!\n";
        return;
    }

    for (string tinh : dsTinh){
        ThanhPho tp(tinh);
        cout << tinh << " : " << tp.demSoLuongThueBao() << " thue bao" << endl;
    }
}

void QuanLyDanhBa::hienThiTinh() 
{
    cout << "\n===== CAC TINH DANG QUAN LY =====\n";

    if (dsTinh.empty()){
        cout << "Danh sach rong!\n";
        return;
    }

    for (string tinh : dsTinh) cout << tinh << endl;
    
}

void QuanLyDanhBa::kiemTraXoaTrung(string tinh) 
{
    ThanhPho tp(tinh);
    tp.xoaSoTrung();
}

