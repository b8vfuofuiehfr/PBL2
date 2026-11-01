#include "ThueBaoCoDinh.h"
#include <iostream>
#include <sstream> 

using namespace std;

ThueBaoCoDinh::ThueBaoCoDinh() {}

ThueBaoCoDinh::ThueBaoCoDinh(const string& ten, const string& dc, const string& sd) 
    : tenDonVi(ten), diaChi(dc), soDuoi(sd) {}

ThueBaoCoDinh::~ThueBaoCoDinh() {}

void ThueBaoCoDinh::xuat(const string& maVung) const {  
    cout << "Ten: " << tenDonVi << " | Dia chi: " << diaChi << " | SDT: ";
    if (!maVung.empty()) {
        cout << "(" << maVung << ") ";
    }
    cout << soDuoi;
}

const string& ThueBaoCoDinh::getSoDuoi() const{ return soDuoi; }

const string& ThueBaoCoDinh::getTenDonVi() const{ return tenDonVi; }

ThueBaoCaNhan::ThueBaoCaNhan(const string& ten, const string& cc, const string& dc, const string& sd) 
    : ThueBaoCoDinh(ten, dc, sd), cccd(cc) {}

void ThueBaoCaNhan::xuat(const string& maVung) const 
{
    cout << "[Ca Nhan] ";
    ThueBaoCoDinh::xuat(maVung);
    cout << " | CCCD: " << cccd << "\n";
}

string ThueBaoCaNhan::taochuoi() const{ return "1|" + tenDonVi + "|" + cccd + "|" + diaChi + "|" + soDuoi; }
int ThueBaoCaNhan::getLoai() const { return 1; }

string ThueBaoDoanhNghiep::taochuoi() const{ return "2|" + tenDonVi + "|" + maSoThue + "|" + diaChi + "|" + soDuoi; }
int ThueBaoDoanhNghiep::getLoai() const { return 2; }

ThueBaoDoanhNghiep::ThueBaoDoanhNghiep(const string& ten, const string& mst, const string& dc, const string& sd) 
    : ThueBaoCoDinh(ten, dc, sd), maSoThue(mst) {}

void ThueBaoDoanhNghiep::xuat(const string& maVung) const 
{
    cout << "[Doanh Nghiep] ";
    ThueBaoCoDinh::xuat(maVung);
    cout << " | MST: " << maSoThue << "\n";
}



ThueBaoCoDinh* ThueBaoCoDinh::chinhsuadata(const string& line) 
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