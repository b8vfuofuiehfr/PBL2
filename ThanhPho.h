#ifndef THANHPHO_H
#define THANHPHO_H

#include "ThueBaoCoDinh.h"
#include "Vector.h"
#include <string>

using namespace std;

class ThanhPho
{
private:
    string tenTinh;
    string maVung;
    Vector<ThueBaoCoDinh*> dsThueBao;

    void quickSort(int low, int high, int tieuChi);
    int partition(int low, int high, int tieuChi);
    int binarySearchTheoSDT(const string& soDuoi);

public:
    ThanhPho(const string& ten);
    ~ThanhPho();

    const string& getTenTinh() const { return tenTinh; }
    const string& getMaVung() const { return maVung; }
    void setMaVung(const string& ma) { maVung = ma; }
    Vector<ThueBaoCoDinh*>& getDanhSachThueBao() { return dsThueBao; }

    void docFile();
    void ghiFile();

    bool kiemTraTrungSDT(const string& soDuoi);
    bool kiemTraTonTai(const string& soDuoi);
    bool themThueBao(ThueBaoCoDinh* tb);
    bool suaThueBao(int index, const string& ten, const string& dd, const string& dc, const string& sd);
    bool xoaThueBao(const string& soDuoi);
    int xoaSoTrung();
    void sapXepDanhBa(int tieuChi);
};

#endif