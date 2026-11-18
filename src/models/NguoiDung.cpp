#include "NguoiDung.h"
#include <fstream>
#include <sstream>

static string getPathTaiKhoan()
{
    ifstream f1("data/TaiKhoan.dat");
    if (f1.good()) return "data/TaiKhoan.dat";
    ifstream f2("data/DanhBa.dat");
    if (f2.good()) return "data/TaiKhoan.dat";
    return "C:/Users/Win/Desktop/PBL2/data/TaiKhoan.dat";
}

NguoiDung::NguoiDung(const string& user, const string& pass)
    : tenDangNhap(user), matKhau(pass) {}

NguoiDung::~NguoiDung() {}

string NguoiDung::taoChuoi() const
{
    return tenDangNhap + "|" + matKhau + "|" + getVaiTro();
}

NguoiDung* NguoiDung::tuChuoi(const string& line)
{
    stringstream ss(line);
    string user, pass, role;
    getline(ss, user, '|');
    getline(ss, pass, '|');
    getline(ss, role, '|');

    if (user.empty() || pass.empty()) return nullptr;
    if (role == "ADMIN") return new Admin(user, pass);
    if (role == "USER") return new User(user, pass);
    return nullptr;
}

Admin::Admin(const string& user, const string& pass)
    : NguoiDung(user, pass) {}

User::User(const string& user, const string& pass)
    : NguoiDung(user, pass) {}

QuanLyTaiKhoan::QuanLyTaiKhoan()
{
    docFile();
}

QuanLyTaiKhoan::~QuanLyTaiKhoan()
{
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        delete dsTaiKhoan[i];
    }
    dsTaiKhoan.clear();
}

void QuanLyTaiKhoan::docFile()
{
    ifstream in(getPathTaiKhoan());
    if (!in) {
        // Tao tai khoan mac dinh neu chua co file
        dsTaiKhoan.push_back(new Admin("admin", "123456"));
        dsTaiKhoan.push_back(new User("user", "123456"));
        ghiFile();
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        NguoiDung* nd = NguoiDung::tuChuoi(line);
        if (nd != nullptr) dsTaiKhoan.push_back(nd);
    }
    in.close();

    if (dsTaiKhoan.empty()) {
        dsTaiKhoan.push_back(new Admin("admin", "123456"));
        dsTaiKhoan.push_back(new User("user", "123456"));
        ghiFile();
    }
}

void QuanLyTaiKhoan::ghiFile()
{
    ofstream out(getPathTaiKhoan());
    if (!out) return;
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        out << dsTaiKhoan[i]->taoChuoi() << "\n";
    }
    out.close();
}

NguoiDung* QuanLyTaiKhoan::dangNhap(const string& user, const string& pass)
{
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        if (dsTaiKhoan[i]->getTenDangNhap() == user && dsTaiKhoan[i]->getMatKhau() == pass) {
            return dsTaiKhoan[i]->clone();
        }
    }
    return nullptr;
}

bool QuanLyTaiKhoan::dangKyUser(const string& user, const string& pass)
{
    if (user.empty() || pass.empty()) return false;
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        if (dsTaiKhoan[i]->getTenDangNhap() == user) return false;
    }
    dsTaiKhoan.push_back(new User(user, pass));
    ghiFile();
    return true;
}
