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
    string soDuoi; 

public:
    ThueBaoCoDinh(); 

    ThueBaoCoDinh(const string& ten, const string& dc, const string& sd);
    virtual ~ThueBaoCoDinh(); 

    virtual void xuat(const string& maVung = "") const; 
    virtual string taochuoi() const = 0; 
    virtual int getLoai() const = 0;
    
    const string& getSoDuoi() const; 
    const string& getTenDonVi() const;

    static ThueBaoCoDinh* chinhsuadata(const string& line);
};

class ThueBaoCaNhan : public ThueBaoCoDinh 
{
private:
    string cccd; 
public:
    ThueBaoCaNhan(const string& ten, const string& cc, const string& dc, const string& sd);
    void xuat(const string& maVung = "") const override;
    string taochuoi() const override;
    int getLoai() const override;
};

class ThueBaoDoanhNghiep : public ThueBaoCoDinh 
{
private:
    string maSoThue; 
public:
    ThueBaoDoanhNghiep(const string& ten, const string& mst, const string& dc, const string& sd);
    void xuat(const string& maVung = "") const override;
    string taochuoi() const override;
    int getLoai() const override;
};

#endif