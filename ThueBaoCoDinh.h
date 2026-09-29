#ifndef THUEBAOCODINH_H
#define THUEBAOCODINH_H

#include <string>
#include <iostream>

using namespace std;

class ThueBaoCoDinh {
protected: 
    string tenDonVi;
    string diaChi;
    string soDienThoai;

public:
    ThueBaoCoDinh(); 
    ThueBaoCoDinh(string ten, string dc, string sdt);
    
    virtual ~ThueBaoCoDinh(); 

    virtual void xuat() const; 
    virtual string taochuoi() const = 0; 
    string getSoDienThoai() const; 

    static ThueBaoCoDinh* chinhsuadata(string line);
};

class ThueBaoCaNhan : public ThueBaoCoDinh {
private:
    string cccd; 
public:
    ThueBaoCaNhan(string ten, string cc, string dc, string sdt);
    void xuat() const override;
    string taochuoi() const override;
};

class ThueBaoDoanhNghiep : public ThueBaoCoDinh {
private:
    string maSoThue; 
public:
    ThueBaoDoanhNghiep(string ten, string mst, string dc, string sdt);
    void xuat() const override;
    string taochuoi() const override;
};

#endif