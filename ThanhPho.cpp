#include "ThanhPho.h"
#include "ThueBaoCoDinh.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

ThanhPho::ThanhPho(string ten) 
{
    tenTinh = ten;
    maVung = "";
    docFile();   
}

ThanhPho::~ThanhPho()
{
    for (size_t i = 0; i < dsThueBao.size(); i++) delete dsThueBao[i];
    dsThueBao.clear();
}

string ThanhPho::getTenTinh() const { return tenTinh; }
string ThanhPho::getMaVung() const { return maVung; }
void ThanhPho::setMaVung(string ma) { maVung = ma; }
string ThanhPho::getFileName() const { return "data/" + tenTinh + ".dat"; }

void ThanhPho::docFile()
{
    ifstream in(getFileName());
    if (!in) return;

    getline(in, maVung);

    string line;
    while (getline(in, line)){
        if (line.empty()) continue;
        ThueBaoCoDinh* tb = ThueBaoCoDinh::chinhsuadata(line);
        if (tb != nullptr) dsThueBao.push_back(tb);
    }
    in.close();
}

void ThanhPho::ghiFile()
{
    ofstream out(getFileName());
    if (!out) return;

    out << maVung << endl;

    for (size_t i = 0; i < dsThueBao.size(); i++) 
        out << dsThueBao[i]->taochuoi() << endl;
    out.close();
}

bool ThanhPho::kiemTraTrungSDT(string soDuoi) 
{
    for (size_t i = 0; i < dsThueBao.size(); i++) {
        if (dsThueBao[i]->getSoDuoi() == soDuoi) {
            cout << " [!] So dien thoai " << soDuoi << " da ton tai trong tinh/thanh pho nay!\n";
            return true;
        }
    }
    return false;
}

// ===== MỚI: KIỂM TRA TỒN TẠI VÀ XUẤT THÔNG TIN =====
bool ThanhPho::kiemTraTonTai(string soDuoi) 
{
    for (size_t i = 0; i < dsThueBao.size(); i++) {
        if (dsThueBao[i]->getSoDuoi() == soDuoi) {
            cout << "\n[+] TIM THAY THUE BAO:\n";
            dsThueBao[i]->xuat(maVung);
            return true;
        }
    }
    cout << "\n[-] Khong tim thay so dien thoai " << soDuoi << " tai " << tenTinh << "!\n";
    return false;
}

// ===== MỚI: XÓA 1 SỐ ĐIỆN THOẠI =====
bool ThanhPho::xoaThueBao(string soDuoi) 
{
    for (size_t i = 0; i < dsThueBao.size(); i++) {
        if (dsThueBao[i]->getSoDuoi() == soDuoi) {
            delete dsThueBao[i];
            dsThueBao.erase(dsThueBao.begin() + i);
            ghiFile(); // Ghi lai file sau khi xoa
            cout << "=> Da xoa thanh cong thue bao co so: " << soDuoi << "!\n";
            return true;
        }
    }
    cout << "[-] Khong tim thay thue bao co so " << soDuoi << " de xoa!\n";
    return false;
}

void ThanhPho::themThueBao() 
{
    if (maVung.empty()) {
        cout << "- Nhap ma vung dien thoai cho " << tenTinh << " (VD: 024, 028, 0236...): ";
        cin >> maVung;
    }

    int loai;
    cout << "\n+--- CHON LOAI THUE BAO CAN THEM ---+" << endl;
    cout << "| 1. Thue bao Ca nhan               |" << endl;
    cout << "| 2. Thue bao Doanh nghiep          |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << " >> Nhap lua chon (1 hoac 2): ";
    if (!(cin >> loai)){
        cout << "Loi nhap du lieu, huy thao tac!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    
    cin.ignore(10000, '\n');

    string ten, diaChi, soDuoi, thongTinRieng;

    cout << "- Nhap ten (Nguoi/Doanh Nghiep): ";
    getline(cin, ten);
    if (loai == 1){
        cout << "- Nhap CCCD: ";
        getline(cin, thongTinRieng);
    }
    else if (loai == 2){
        cout << "- Nhap Ma so thue: ";
        getline(cin, thongTinRieng);
    }
    else {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    cout << "- Nhap dia chi: ";
    getline(cin, diaChi);
    
    cout << "- Nhap so duoi dien thoai (khong nhap ma vung " << maVung << "): ";
    getline(cin, soDuoi);

    if (kiemTraTrungSDT(soDuoi)) {
        cout << "Them that bai do so dien thoai da ton tai!\n";
        return;
    }

    ThueBaoCoDinh* tb = nullptr;
    if (loai == 1) tb = new ThueBaoCaNhan(ten, thongTinRieng, diaChi, soDuoi);
    else tb = new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, soDuoi);

    dsThueBao.push_back(tb);
    ghiFile();

    cout << "Them thue bao thanh cong! SDT hoan chinh: (" << maVung << ") " << soDuoi << endl;
}

void ThanhPho::lietKeDanhBa() 
{
    cout << "\n--- Danh sach thue bao tai " << tenTinh << " (Ma vung: " << maVung << ") ---\n";
    if (dsThueBao.empty()) {
        cout << "(Chua co thue bao nao)\n";
        return;
    }
    for (size_t i = 0; i < dsThueBao.size(); i++) 
        dsThueBao[i]->xuat(maVung); 
}

int ThanhPho::demSoLuongThueBao() { 
    return dsThueBao.size(); 
}

void ThanhPho::xoaSoTrung() 
{
    int count = 0;
    for (size_t i = 0; i < dsThueBao.size(); i++) {
        for (size_t j = i + 1; j < dsThueBao.size(); ) { 
            if (dsThueBao[i]->getSoDuoi() == dsThueBao[j]->getSoDuoi()){
                delete dsThueBao[j];
                dsThueBao.erase(dsThueBao.begin() + j);
                count++;
            }
            else j++; 
        }
    }
    ghiFile(); 
    cout << "Da kiem tra va xoa " << count << " so bi trung trong tinh " << tenTinh << "!\n";
}