#include "ThueBaoCoDinh.h"
#include <iostream>
#include <sstream> 

using namespace std;

ThueBaoCoDinh::ThueBaoCoDinh() {}

ThueBaoCoDinh::ThueBaoCoDinh(string ten, string dc, string sdt) 
    : tenDonVi(ten), diaChi(dc), soDienThoai(sdt) {}

ThueBaoCoDinh::~ThueBaoCoDinh() {}

void ThueBaoCoDinh::xuat() const {  cout << "Ten: " << tenDonVi << " | Dia chi: " << diaChi << " | SDT: " << soDienThoai; }

string ThueBaoCoDinh::getSoDienThoai() const { return soDienThoai; }

ThueBaoCaNhan::ThueBaoCaNhan(string ten, string cc, string dc, string sdt) 
    : ThueBaoCoDinh(ten, dc, sdt), cccd(cc) {}

void ThueBaoCaNhan::xuat() const 
{
    cout << "[Ca Nhan] ";
    ThueBaoCoDinh::xuat();
    cout << " | CCCD: " << cccd << endl;
}

string ThueBaoCaNhan::taochuoi() const { return "1|" + tenDonVi + "|" + cccd + "|" + diaChi + "|" + soDienThoai; }

ThueBaoDoanhNghiep::ThueBaoDoanhNghiep(string ten, string mst, string dc, string sdt) 
    : ThueBaoCoDinh(ten, dc, sdt), maSoThue(mst) {}

void ThueBaoDoanhNghiep::xuat() const 
{
    cout << "[Doanh Nghiep] ";
    ThueBaoCoDinh::xuat();
    cout << " | MST: " << maSoThue << endl;
}

string ThueBaoDoanhNghiep::taochuoi() const { return "2|" + tenDonVi + "|" + maSoThue + "|" + diaChi + "|" + soDienThoai; }

ThueBaoCoDinh* ThueBaoCoDinh::chinhsuadata(string line) 
{
    stringstream ss(line);
    string flag, ten, thongTinRieng, diaChi, sdt;

    getline(ss, flag, '|');           
    getline(ss, ten, '|');            
    getline(ss, thongTinRieng, '|');  
    getline(ss, diaChi, '|');         
    getline(ss, sdt, '|');            

    if (flag == "1") return new ThueBaoCaNhan(ten, thongTinRieng, diaChi, sdt);
    else if (flag == "2") return new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, sdt);

    return nullptr; 
}