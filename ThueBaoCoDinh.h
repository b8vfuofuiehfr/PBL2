#ifndef THUEBAOCODINH_H
#define THUEBAOCODINH_H

#include <string>

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

    virtual string taochuoi() const = 0;
    virtual int getLoai() const = 0;
    virtual string getDinhDanh() const = 0;
    virtual void setDinhDanh(const string& dd) = 0;

    const string& getTenDonVi() const;
    const string& getDiaChi() const;
    const string& getSoDuoi() const;
    void setTenDonVi(const string& ten);
    void setDiaChi(const string& dc);
    void setSoDuoi(const string& sd);

    static ThueBaoCoDinh* chinhsuadata(const string& line);
};

class ThueBaoCaNhan : public ThueBaoCoDinh
{
private:
    string cccd;
public:
    ThueBaoCaNhan(const string& ten, const string& cc, const string& dc, const string& sd);
    string taochuoi() const override;
    int getLoai() const override { return 1; }
    string getDinhDanh() const override { return cccd; }
    void setDinhDanh(const string& dd) override { cccd = dd; }
};

class ThueBaoDoanhNghiep : public ThueBaoCoDinh
{
private:
    string maSoThue;
public:
    ThueBaoDoanhNghiep(const string& ten, const string& mst, const string& dc, const string& sd);
    string taochuoi() const override;
    int getLoai() const override { return 2; }
    string getDinhDanh() const override { return maSoThue; }
    void setDinhDanh(const string& dd) override { maSoThue = dd; }
};

#endif