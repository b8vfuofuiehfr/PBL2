#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include <string>
#include <vector>

using namespace std;

class QuanLyDanhBa {
private:
    vector<string> dsTinh;
    string thuMucDuLieu;

    void taiDanhSachTinhTuThuMuc();
public:
    QuanLyDanhBa();
    ~QuanLyDanhBa();
    void themTinh(string tinh);
    void themThueBao(string tinh);
    void lietKeTheoTinh(string tinh);
    void thongKeTheoTinh();
    void hienThiTinh();
    void kiemTraXoaTrung(string tinh);
};

#endif
