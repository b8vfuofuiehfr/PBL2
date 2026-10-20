#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include <string>
#include <vector>

using namespace std;

class QuanLyDanhBa 
{
private:
    vector<string> dsTinh;
    string thuMucDuLieu;
    void capNhatFileDanhSachTinh(); // Ham phu ghi lai dsTinh vao file

public:
    QuanLyDanhBa();
    ~QuanLyDanhBa();
    void themTinh(string tinh);
    void themThueBao();
    void lietKeTheoTinh();
    void thongKeTheoTinh();
    void hienThiTinh();
    void kiemTraXoaTrung();

    // CÁC HÀM MỚI BỔ SUNG:
    void kiemTraTonTaiSDT();
    void xoaThueBao();
    void xoaTinh();
};

#endif