#ifndef THANHPHO_H
#define THANHPHO_H

#include <string>

using namespace std;

class ThanhPho {
private:
    string tenTinh;

public:
    ThanhPho(string ten);

    string getTenTinh();
    string getFileName();
    bool kiemTraTrungSDT(string sdt);
    void themThueBao();
    void lietKeDanhBa();
    int demSoLuongThueBao();
    void xoaSoTrung();
};

#endif
