#ifndef THANHPHO_H
#define THANHPHO_H

#include "ThueBaoCoDinh.h"
#include <string>
#include <vector>

using namespace std;

class ThanhPho 
{
private:
    string tenTinh;
    string maVung; // Ma thanh pho do lop ThanhPho quan ly
    vector<ThueBaoCoDinh*> dsThueBao;

public:
    ThanhPho(string ten);
    ~ThanhPho();

    string getTenTinh() const;
    string getMaVung() const;
    void setMaVung(string ma);
    string getFileName() const;

    bool kiemTraTrungSDT(string soDuoi);
    bool kiemTraTonTai(string soDuoi);  // MỚI: kiểm tra và in chi tiết
    bool xoaThueBao(string soDuoi);     // MỚI: xóa 1 thuê bao theo số đuôi
    void themThueBao();
    void lietKeDanhBa();
    int demSoLuongThueBao();
    void xoaSoTrung();
    void docFile();
    void ghiFile();
};

#endif