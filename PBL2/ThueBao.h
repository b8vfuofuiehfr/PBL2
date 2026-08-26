#ifndef THUEBAOCODINH_H
#define THUEBAOCODINH_H

#include <string>

using namespace std;

class ThueBaoCoDinh {

private:
    string soDienThoai;
    string tenDonVi;
    string diaChi;

public:
    ThueBaoCoDinh();
    ThueBaoCoDinh(string ten, string dc, string sdt);

    void nhap();
    void xuat();

    string getSoDienThoai();
    string toString();
    static ThueBaoCoDinh fromString(string line);
};

#endif
