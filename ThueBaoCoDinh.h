#ifndef THUEBAOCODINH_H
#define THUEBAOCODINH_H

#include <string>
#include <iostream>

using namespace std;

class ThueBaoCoDinh 
{
protected: 
    string tenDonVi;
    string diaChi;
    string soDuoi; // Thay the soDienThoai cu bang soDuoi

public:
    ThueBaoCoDinh(); 
    ThueBaoCoDinh(string ten, string dc, string sd);
    virtual ~ThueBaoCoDinh(); 

    // Cho phep truyen maVung tu ThanhPho vao de hien thi so hoan chinh
    virtual void xuat(string maVung = "") const; 
    virtual string taochuoi() const = 0; 
    string getSoDuoi() const; 

    static ThueBaoCoDinh* chinhsuadata(string line);
};

class ThueBaoCaNhan : public ThueBaoCoDinh 
{
private:
    string cccd; 
public:
    ThueBaoCaNhan(string ten, string cc, string dc, string sd);
    void xuat(string maVung = "") const override;
    string taochuoi() const override;
};

class ThueBaoDoanhNghiep : public ThueBaoCoDinh 
{
private:
    string maSoThue; 
public:
    ThueBaoDoanhNghiep(string ten, string mst, string dc, string sd);
    void xuat(string maVung = "") const override;
    string taochuoi() const override;
};

#endif