#include "ThanhPho.h"
#include "ThueBaoCoDinh.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

ThanhPho::ThanhPho(string ten) {
    tenTinh = ten;
}

string ThanhPho::getTenTinh() const {
    return tenTinh;
}

string ThanhPho::getFileName() const {
    return tenTinh + ".dat";
}

bool ThanhPho::kiemTraTrungSDT(string sdt) {
    ifstream in(getFileName());
    string line;

    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        ThueBaoCoDinh tb = ThueBaoCoDinh::fromString(line);
        if (tb.getSoDienThoai() == sdt) {
            return true;
        }
    }

    return false;
}

void ThanhPho::themThueBao() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ThueBaoCoDinh tb;
    tb.nhap();

    if (kiemTraTrungSDT(tb.getSoDienThoai())) {
        cout << "\nSO DIEN THOAI DA TON TAI TRONG TINH NAY!\n";
        return;
    }

    ofstream out(getFileName(), ios::app);
    if (!out) {
        cout << "Khong the mo file de ghi!\n";
        return;
    }

    out << tb.toString() << endl;
    cout << "\nThem thanh cong!\n";
}

void ThanhPho::lietKeDanhBa() {
    ifstream in(getFileName());
    if (!in) {
        cout << "Khong ton tai file du lieu!\n";
        return;
    }

    string line;
    cout << "\n===== DANH BA " << tenTinh << " =====\n";

    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        ThueBaoCoDinh tb = ThueBaoCoDinh::fromString(line);
        tb.xuat();
    }
}

int ThanhPho::demSoLuongThueBao() {
    ifstream in(getFileName());
    string line;
    int dem = 0;

    while (getline(in, line)) {
        if (!line.empty()) {
            dem++;
        }
    }

    return dem;
}

void ThanhPho::xoaSoTrung() {
    ifstream in(getFileName());
    if (!in) {
        cout << "Khong tim thay file!\n";
        return;
    }

    vector<ThueBaoCoDinh> ds;
    string line;

    while (getline(in, line)) {
        if (!line.empty()) {
            ds.push_back(ThueBaoCoDinh::fromString(line));
        }
    }
    in.close();

    bool trung = false;

    for (size_t i = 0; i < ds.size(); i++) {
        for (size_t j = i + 1; j < ds.size();) {
            if (ds[i].getSoDienThoai() == ds[j].getSoDienThoai()) {
                cout << "Phat hien trung so: "
                     << ds[j].getSoDienThoai() << endl;
                ds.erase(ds.begin() + j);
                trung = true;
            } else {
                j++;
            }
        }
    }

    ofstream out(getFileName());
    if (!out) {
        cout << "Khong the mo file de cap nhat!\n";
        return;
    }

    for (auto &x : ds) {
        out << x.toString() << endl;
    }

    if (trung) {
        cout << "Da xoa cac ban ghi trung.\n";
    } else {
        cout << "Khong co so trung.\n";
    }
}
