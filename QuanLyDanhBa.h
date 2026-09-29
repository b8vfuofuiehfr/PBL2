#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include <string>
#include <vector>

using namespace std;

class QuanLyDanhBa {
private:
    vector<string> dsTinh;
    string thuMucDuLieu;
public:
    QuanLyDanhBa();
    ~QuanLyDanhBa();
    void themTinh(string tinh);
    void themThueBao();
    void lietKeTheoTinh();
    void thongKeTheoTinh();
    void hienThiTinh();
    void kiemTraXoaTrung();
};

#endif
