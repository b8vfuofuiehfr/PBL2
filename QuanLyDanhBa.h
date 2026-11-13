#ifndef QUANLYDANHBA_H
#define QUANLYDANHBA_H

#include "Vector.h"
#include <string>

using namespace std;

class QuanLyDanhBa
{
private:
    Vector<string> dsTinh;
    QuanLyDanhBa();

public:
    QuanLyDanhBa(const QuanLyDanhBa&) = delete;
    QuanLyDanhBa& operator=(const QuanLyDanhBa&) = delete;

    static QuanLyDanhBa& getInstance() {
        static QuanLyDanhBa instance;
        return instance;
    }

    const Vector<string>& getDanhSachTinh() const { return dsTinh; }
    void themTinh(const string& tinh);
    void xoaTinh(const string& tinh);
};
#endif