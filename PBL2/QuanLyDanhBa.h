#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include <string>
#include <vector>
#include <filesystem>

using namespace std;

class QuanLyDanhBa {
private:
    vector<string> dsTinh;

public:
    void themTinh(string tinh);
    void themThueBao();
    void lietKeTheoTinh();
    void thongKeTheoTinh();
    void hienThiTinh();
    void kiemTraXoaTrung();
};

#endif
