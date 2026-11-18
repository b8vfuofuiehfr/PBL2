#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include "Vector.h"
#include <string>

using namespace std;

class NguoiDung
{
protected:
    string tenDangNhap;
    string matKhau;

public:
    NguoiDung(const string& user, const string& pass);
    virtual ~NguoiDung();

    const string& getTenDangNhap() const { return tenDangNhap; }
    const string& getMatKhau() const { return matKhau; }

    virtual string getVaiTro() const = 0;
    virtual bool coQuyenChinhSua() const = 0;
    virtual NguoiDung* clone() const = 0;

    string taoChuoi() const;
    static NguoiDung* tuChuoi(const string& line);
};

class Admin : public NguoiDung
{
public:
    Admin(const string& user, const string& pass);
    string getVaiTro() const override { return "ADMIN"; }
    bool coQuyenChinhSua() const override { return true; }
    NguoiDung* clone() const override { return new Admin(*this); }
};

class User : public NguoiDung
{
public:
    User(const string& user, const string& pass);
    string getVaiTro() const override { return "USER"; }
    bool coQuyenChinhSua() const override { return false; }
    NguoiDung* clone() const override { return new User(*this); }
};

class QuanLyTaiKhoan
{
private:
    Vector<NguoiDung*> dsTaiKhoan;
    QuanLyTaiKhoan();
    ~QuanLyTaiKhoan();

    void docFile();
    void ghiFile();

public:
    QuanLyTaiKhoan(const QuanLyTaiKhoan&) = delete;
    QuanLyTaiKhoan& operator=(const QuanLyTaiKhoan&) = delete;

    static QuanLyTaiKhoan& getInstance() {
        static QuanLyTaiKhoan instance;
        return instance;
    }

    NguoiDung* dangNhap(const string& user, const string& pass);
    bool dangKyUser(const string& user, const string& pass);
};

#endif
