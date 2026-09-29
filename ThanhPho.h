#ifndef THANHPHO_H
#define THANHPHO_H

#include "ThueBaoCoDinh.h"
#include <string>
#include <vector>

using namespace std;

class ThanhPho {
private:
    string tenTinh;
    vector <ThueBaoCoDinh*> dsThueBao;

public:
    ThanhPho(string ten);
    ~ThanhPho();

    string getTenTinh() const;
    string getFileName() const;
    bool kiemTraTrungSDT(string sdt);
    void themThueBao();
    void lietKeDanhBa();
    int demSoLuongThueBao();
    void xoaSoTrung();
    void docFile();
    void ghiFile();
};

#endif
