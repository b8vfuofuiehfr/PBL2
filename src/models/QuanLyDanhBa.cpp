#include "QuanLyDanhBa.h"
#include <fstream>
#include <sstream>

static string getPathCSDL()
{
    ifstream f("data/DanhBa.dat");
    if (f.good()) return "data/DanhBa.dat";
    return "C:/Users/Win/Desktop/PBL2/data/DanhBa.dat";
}

QuanLyDanhBa::QuanLyDanhBa()
{
    ifstream file(getPathCSDL());
    if (!file) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string tinh;
        getline(ss, tinh, '|');
        bool daCo = false;
        for (const string& x : dsTinh) {
            if (x == tinh) { daCo = true; break; }
        }
        if (!daCo && !tinh.empty()) dsTinh.push_back(tinh);
    }
    file.close();
}

void QuanLyDanhBa::themTinh(const string& tinh)
{
    for (const string& x : dsTinh) if (x == tinh) return;
    dsTinh.push_back(tinh);
}

void QuanLyDanhBa::xoaTinh(const string& tinh)
{
    int viTri = -1;
    for (int i = 0; i < dsTinh.size(); i++) {
        if (dsTinh[i] == tinh) { viTri = i; break; }
    }
    if (viTri != -1) dsTinh.erase(viTri);

    Vector<string> cacDongGiuLai;
    ifstream in(getPathCSDL());
    if (in) {
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string ten;
            getline(ss, ten, '|');
            if (ten != tinh) cacDongGiuLai.push_back(line);
        }
        in.close();
    }

    ofstream out(getPathCSDL());
    for (int i = 0; i < cacDongGiuLai.size(); i++) out << cacDongGiuLai[i] << "\n";
    out.close();
}