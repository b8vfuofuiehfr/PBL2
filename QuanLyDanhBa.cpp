#include "QuanLyDanhBa.h"
#include "ThanhPho.h"
#include <iostream>
#include <fstream>
#include <cstdio> // Dung ham remove() de xoa file

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

void QuanLyDanhBa::capNhatFileDanhSachTinh()
{
    ofstream file("data/0_DanhSachTinh.dat");
    if (!file) return;
    for (size_t i = 0; i < dsTinh.size(); i++) {
        file << dsTinh[i] << endl;
    }
    file.close();
}

void QuanLyDanhBa::themTinh(string tinh) 
{
    for (string x : dsTinh) 
        if (x == tinh) return;

    dsTinh.push_back(tinh);

    ofstream fileMucLuc("data/0_DanhSachTinh.dat", ios::app);
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
        cout << tinh << " (Ma vung: " << tp.getMaVung() << ") : "
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
        ThanhPho tp(tinh);
        cout << "- " << tinh << " [Ma vung: " << tp.getMaVung() << "]\n";
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

// ===== MỚI: KIỂM TRA TỒN TẠI SỐ ĐIỆN THOẠI =====
void QuanLyDanhBa::kiemTraTonTaiSDT() 
{
    string tinh, soDuoi;
    cout << "Nhap tinh can tra cuu: ";
    cin >> tinh;

    bool tonTaiTinh = false;
    for (string x : dsTinh) {
        if (x == tinh) { tonTaiTinh = true; break; }
    }

    if (!tonTaiTinh) {
        cout << "[-] Tinh " << tinh << " hien khong co trong he thong!\n";
        return;
    }

    ThanhPho tp(tinh);
    cout << "Nhap so duoi can tim (Ma vung cua " << tinh << " la " << tp.getMaVung() << "): ";
    cin >> soDuoi;

    tp.kiemTraTonTai(soDuoi);
}

// ===== MỚI: XÓA SỐ ĐIỆN THOẠI =====
void QuanLyDanhBa::xoaThueBao() 
{
    string tinh, soDuoi;
    cout << "Nhap tinh chua thue bao can xoa: ";
    cin >> tinh;

    bool tonTaiTinh = false;
    for (string x : dsTinh) {
        if (x == tinh) { tonTaiTinh = true; break; }
    }

    if (!tonTaiTinh) {
        cout << "[-] Tinh " << tinh << " khong ton tai!\n";
        return;
    }

    ThanhPho tp(tinh);
    cout << "Nhap so duoi can xoa: ";
    cin >> soDuoi;

    tp.xoaThueBao(soDuoi);
}

// ===== MỚI: XÓA TỈNH =====
void QuanLyDanhBa::xoaTinh() 
{
    string tinh;
    cout << "Nhap ten tinh/thanh pho muon xoa: ";
    cin >> tinh;

    int viTri = -1;
    for (size_t i = 0; i < dsTinh.size(); i++) {
        if (dsTinh[i] == tinh) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        cout << "[-] Tinh " << tinh << " khong co trong danh sach quan ly!\n";
        return;
    }

    cout << "[CANDIDATE] Ban co chac muon xoa tinh " << tinh << " va toan bo du lieu lien quan? (y/n): ";
    char xacNhan;
    cin >> xacNhan;

    if (xacNhan != 'y' && xacNhan != 'Y') {
        cout << "Da huy thao tac xoa tinh!\n";
        return;
    }

    // 1. Xoa khoi vector dsTinh
    dsTinh.erase(dsTinh.begin() + viTri);

    // 2. Cap nhat lai file 0_DanhSachTinh.dat
    capNhatFileDanhSachTinh();

    // 3. Xoa file vat ly data/<tinh>.dat
    string duongDan = "data/" + tinh + ".dat";
    remove(duongDan.c_str());

    cout << "=> Da xoa tinh " << tinh << " thanh cong!\n";
}