#ifndef THANHPHO_H
#define THANHPHO_H

#include <string>

using namespace std;

class ThanhPho {
private:
    string tenTinh;
    string thuMucDuLieu;

public:
    ThanhPho(string ten = "");
    ~ThanhPho();
    string TenTinh();
    string TenFile();
    bool kiemTraTrungSDT(string sdt);
    void themThueBao();
    void lietKeDanhBa();
    int demSoLuongThueBao();
    void xoaSoTrung();
};

#endif
