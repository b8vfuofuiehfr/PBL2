#ifndef THUEBAO_H
#define THUEBAO_H

#include <string>

using namespace std;

class ThueBaoCoDinh{

private:
    string soDienThoai;
    string tenDonVi;
    string diaChi;

public:
    ThueBaoCoDinh();
    ~ThueBaoCoDinh();
    ThueBaoCoDinh(string ten, string dc, string sdt);

    void nhap();
    void xuat();

    string getSoDienThoai() const;
    string taochuoi() const;
    static ThueBaoCoDinh chinhsuadata(string line);
};

#endif
