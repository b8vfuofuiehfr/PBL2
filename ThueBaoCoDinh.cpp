#include "ThueBaoCoDinh.h"
#include <iostream>
#include <sstream>

using namespace std;

ThueBaoCoDinh::~ThueBaoCoDinh(){}

ThueBaoCoDinh::ThueBaoCoDinh(){}

ThueBaoCoDinh::ThueBaoCoDinh(string ten, string dc, string sdt)
{
    tenDonVi = ten;
    diaChi = dc;
    soDienThoai = sdt;
}

void ThueBaoCoDinh::nhap()
{
    cout << "Ten don vi/chu thue bao: ";
    getline(cin, tenDonVi);

    cout << "Dia chi: ";
    getline(cin, diaChi);

    cout << "So dien thoai: ";
    getline(cin, soDienThoai);
}

void ThueBaoCoDinh::xuat() 
{
    cout << "Ten don vi : " << tenDonVi << endl;
    cout << "Dia chi    : " << diaChi << endl;
    cout << "So DT      : " << soDienThoai << endl;
    cout << "-----------------------------\n";
}

string ThueBaoCoDinh::getSoDienThoai() const 
{
    return soDienThoai;
}

string ThueBaoCoDinh::taochuoi() const 
{
    return tenDonVi + "|" + diaChi + "|" + soDienThoai;
}

ThueBaoCoDinh ThueBaoCoDinh::chinhsuadata(string line) 
{
    string ten, dc, sdt;
    stringstream ss(line);

    getline(ss, ten, '|');
    getline(ss, dc, '|');
    getline(ss, sdt, '|');

    return ThueBaoCoDinh(ten, dc, sdt);
}
