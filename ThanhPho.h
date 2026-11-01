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

    const string& getTenTinh() const;
    const string& getMaVung() const;
    void setMaVung(const string& ma);
    string getFileName() const;

    bool kiemTraTrungSDT(const string& soDuoi);
    bool kiemTraTonTai(const string& soDuoi); 
    bool xoaThueBao(const string& soDuoi);    
    void themThueBao();
    void lietKeDanhBa();
    int demSoLuongThueBao() const;
    void xoaSoTrung();
    void docFile();
    void ghiFile();
    void sapXepDanhBa();
};

#endif