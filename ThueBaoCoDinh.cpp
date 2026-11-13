#include "ThueBaoCoDinh.h"
#include <sstream>

ThueBaoCoDinh::ThueBaoCoDinh() {}
ThueBaoCoDinh::ThueBaoCoDinh(const string& ten, const string& dc, const string& sd)
    : tenDonVi(ten), diaChi(dc), soDuoi(sd) {}
ThueBaoCoDinh::~ThueBaoCoDinh() {}

const string& ThueBaoCoDinh::getSoDuoi() const { return soDuoi; }
const string& ThueBaoCoDinh::getTenDonVi() const { return tenDonVi; }
const string& ThueBaoCoDinh::getDiaChi() const { return diaChi; }
void ThueBaoCoDinh::setTenDonVi(const string& ten) { tenDonVi = ten; }
void ThueBaoCoDinh::setDiaChi(const string& dc) { diaChi = dc; }
void ThueBaoCoDinh::setSoDuoi(const string& sd) { soDuoi = sd; }

ThueBaoCaNhan::ThueBaoCaNhan(const string& ten, const string& cc, const string& dc, const string& sd)
    : ThueBaoCoDinh(ten, dc, sd), cccd(cc) {}
string ThueBaoCaNhan::taochuoi() const { return "1|" + tenDonVi + "|" + cccd + "|" + diaChi + "|" + soDuoi; }

ThueBaoDoanhNghiep::ThueBaoDoanhNghiep(const string& ten, const string& mst, const string& dc, const string& sd)
    : ThueBaoCoDinh(ten, dc, sd), maSoThue(mst) {}
string ThueBaoDoanhNghiep::taochuoi() const { return "2|" + tenDonVi + "|" + maSoThue + "|" + diaChi + "|" + soDuoi; }

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
    if (flag == "2") return new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, soDuoi);
    return nullptr;
}