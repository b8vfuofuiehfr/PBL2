#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include "Vector.h"
#include <string>

using namespace std;

class QuanLyDanhBa 
{
private:
    Vector<string> dsTinh;
    void capNhatFileDanhSachTinh();

public:
    QuanLyDanhBa();
    ~QuanLyDanhBa();
    void themTinh(const string& tinh); 
    void themThueBao();
    void lietKeTheoTinh();
    void thongKeTheoTinh();
    void hienThiTinh();
    void kiemTraXoaTrung();

    void kiemTraTonTaiSDT();
    void sapXepDanhBa();
    void xoaThueBao();
    void xoaTinh();
};

#endif