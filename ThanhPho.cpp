#include "ThanhPho.h"
#include "ThueBaoCoDinh.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

ThanhPho::ThanhPho(string ten) 
{
    tenTinh = ten;
    docFile();   
}

ThanhPho::~ThanhPho()
{
    for (size_t i = 0; i < dsThueBao.size(); i++)  delete dsThueBao[i];
    dsThueBao.clear();
}

string ThanhPho::getTenTinh() const{ return tenTinh; }

string ThanhPho::getFileName() const{  return "data/" + tenTinh + ".dat"; }

void ThanhPho::docFile()
{
    ifstream in("data/" + tenTinh + ".dat");
    if (!in) return;

    string line;
    while (getline(in, line)){
        ThueBaoCoDinh* tb = ThueBaoCoDinh::chinhsuadata(line);
        if (tb != nullptr) dsThueBao.push_back(tb);
    }
    in.close();
    
}

void ThanhPho::ghiFile()
{
    ofstream out("data/" + tenTinh + ".dat");
    if (!out) return;
    for (size_t i = 0; i < dsThueBao.size(); i++) out << dsThueBao[i]->taochuoi() << endl;
    out.close();
}

bool ThanhPho::kiemTraTrungSDT(string sdt) 
{
    bool flag = false;
    for (size_t i = 0; i < dsThueBao.size(); i++)
        if (dsThueBao[i]->getSoDienThoai() == sdt){
            flag = true;
            break;
        }
    if (flag) cout << "So dien thoai da ton tai trong danh ba!\n";
    return flag;
}

void ThanhPho::themThueBao() 
{
    int loai;
    cout << "\n+--- CHON LOAI THUE BAO CAN THEM ---+" << endl;
    cout << "| 1. Thue bao Ca nhan               |" << endl;
    cout << "| 2. Thue bao Doanh nghiep          |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << " >> Nhap lua chon (1 hoac 2): ";
    if(!(cin >> loai)){
        cout << "Loi Nhap du lieu, huy thao tac!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    
    cin.ignore(10000, '\n');

    string ten, diaChi, sdt, thongTinRieng;

    cout << "- Nhap ten (Nguoi/Doanh Nghiep):";
    getline(cin, ten);
    if (loai == 1){
        cout << "- Nhap CCCD: ";
        getline(cin, thongTinRieng);
    }
    else if (loai == 2){
        cout <<"-Nhap Ma so thue:";
        getline(cin, thongTinRieng);
    }
    else {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    cout <<"-Nhap dia chi:";
    getline(cin, diaChi);
    
    cout <<"-Nhap so dien thoai:";
    getline(cin, sdt);

    ThueBaoCoDinh* tb = nullptr;
    if (loai == 1) tb = new ThueBaoCaNhan(ten, thongTinRieng, diaChi, sdt);
    else tb = new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, sdt);
    dsThueBao.push_back(tb);
    ghiFile();

    cout << "Them thue bao thanh cong!\n";
}

void ThanhPho::lietKeDanhBa() 
{
    cout << "\n--- Danh sach thue bao tai " << tenTinh << " ---\n";
    for (size_t i = 0; i < dsThueBao.size(); i++) dsThueBao[i]->xuat(); 
}

int ThanhPho::demSoLuongThueBao(){  return dsThueBao.size();   }

void ThanhPho::xoaSoTrung() {
    for (size_t i = 0; i < dsThueBao.size(); i++) 
        for (size_t j = i + 1; j < dsThueBao.size(); ){ 
            
            if (dsThueBao[i]->getSoDienThoai() == dsThueBao[j]->getSoDienThoai()){
                delete dsThueBao[j];
                dsThueBao.erase(dsThueBao.begin() + j);
            }
            else j++; 
        }
    ghiFile(); 
}