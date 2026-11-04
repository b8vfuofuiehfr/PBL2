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
    QuanLyDanhBa();
    ~QuanLyDanhBa();

public:
    QuanLyDanhBa(const QuanLyDanhBa&) = delete;
    QuanLyDanhBa& operator=(const QuanLyDanhBa&) = delete;

    static QuanLyDanhBa& getInstance(){
        static QuanLyDanhBa instance;
        return instance;
    }
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