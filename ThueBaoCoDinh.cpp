#include "ThueBaoCoDinh.h"
#include <iostream>
#include <sstream> 

using namespace std;

ThueBaoCoDinh::ThueBaoCoDinh() {}

ThueBaoCoDinh::ThueBaoCoDinh(string ten, string dc, string sd) 
    : tenDonVi(ten), diaChi(dc), soDuoi(sd) {}

ThueBaoCoDinh::~ThueBaoCoDinh() {}

void ThueBaoCoDinh::xuat(string maVung) const {  
    cout << "Ten: " << tenDonVi << " | Dia chi: " << diaChi << " | SDT: ";
    if (!maVung.empty()) {
        cout << "(" << maVung << ") ";
    }
    cout << soDuoi;
}

string ThueBaoCoDinh::getSoDuoi() const { 
    return soDuoi; 
}

// ===== THUE BAO CA NHAN =====
ThueBaoCaNhan::ThueBaoCaNhan(string ten, string cc, string dc, string sd) 
    : ThueBaoCoDinh(ten, dc, sd), cccd(cc) {}

void ThueBaoCaNhan::xuat(string maVung) const 
{
    cout << "[Ca Nhan] ";
    ThueBaoCoDinh::xuat(maVung);
    cout << " | CCCD: " << cccd << endl;
}

string ThueBaoCaNhan::taochuoi() const { 
    return "1|" + tenDonVi + "|" + cccd + "|" + diaChi + "|" + soDuoi; 
}

// ===== THUE BAO DOANH NGHIEP =====
ThueBaoDoanhNghiep::ThueBaoDoanhNghiep(string ten, string mst, string dc, string sd) 
    : ThueBaoCoDinh(ten, dc, sd), maSoThue(mst) {}

void ThueBaoDoanhNghiep::xuat(string maVung) const 
{
    cout << "[Doanh Nghiep] ";
    ThueBaoCoDinh::xuat(maVung);
    cout << " | MST: " << maSoThue << endl;
}

string ThueBaoDoanhNghiep::taochuoi() const { 
    return "2|" + tenDonVi + "|" + maSoThue + "|" + diaChi + "|" + soDuoi; 
}

// ===== PHAN TICH DU LIEU TU FILE =====
ThueBaoCoDinh* ThueBaoCoDinh::chinhsuadata(string line) 
{
    stringstream ss(line);
    string flag, ten, thongTinRieng, diaChi, soDuoi;

    getline(ss, flag, '|');           
    getline(ss, ten, '|');            
    getline(ss, thongTinRieng, '|');  
    getline(ss, diaChi, '|');         
    getline(ss, soDuoi, '|');            

    if (flag == "1") return new ThueBaoCaNhan(ten, thongTinRieng, diaChi, soDuoi);
    else if (flag == "2") return new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, soDuoi);

    return nullptr; 
}