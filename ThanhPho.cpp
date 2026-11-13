#include "ThanhPho.h"
#include <fstream>
#include <sstream>

// Ham lay dung duong dan file CSDL
static string getPathCSDL()
{
    ifstream f("data/DanhBa.dat");
    if (f.good()) return "data/DanhBa.dat";
    return "C:/Users/Win/Desktop/PBL2/data/DanhBa.dat";
}

ThanhPho::ThanhPho(const string& ten) : tenTinh(ten), maVung("")
{
    docFile();
}

ThanhPho::~ThanhPho() {
    for (int i = 0; i < dsThueBao.size(); i++) delete dsThueBao[i];
    dsThueBao.clear();
}

void ThanhPho::docFile()
{
    ifstream in(getPathCSDL());
    if (!in) return;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string tinh, mv, phanDuoi;
        getline(ss, tinh, '|');
        getline(ss, mv, '|');
        getline(ss, phanDuoi);

        if (tinh == tenTinh) {
            maVung = mv;
            ThueBaoCoDinh* tb = ThueBaoCoDinh::chinhsuadata(phanDuoi);
            if (tb != nullptr) dsThueBao.push_back(tb);
        }
    }
    in.close();
}

void ThanhPho::ghiFile()
{
    Vector<string> dongTinhKhac;
    ifstream in(getPathCSDL());
    if (in) {
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string tinh;
            getline(ss, tinh, '|');
            if (tinh != tenTinh) dongTinhKhac.push_back(line);
        }
        in.close();
    }

    ofstream out(getPathCSDL());
    if (!out) return;
    for (int i = 0; i < dongTinhKhac.size(); i++) out << dongTinhKhac[i] << "\n";
    for (int i = 0; i < dsThueBao.size(); i++) {
        out << tenTinh << "|" << maVung << "|" << dsThueBao[i]->taochuoi() << "\n";
    }
    out.close();
}

int ThanhPho::partition(int low, int high, int tieuChi)
{
    ThueBaoCoDinh* pivot = dsThueBao[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool thoaMan = false;
        if (dsThueBao[j]->getLoai() != pivot->getLoai()) {
            thoaMan = (dsThueBao[j]->getLoai() < pivot->getLoai());
        } else {
            if (tieuChi == 1) thoaMan = (dsThueBao[j]->getSoDuoi() < pivot->getSoDuoi());
            else thoaMan = (dsThueBao[j]->getTenDonVi() < pivot->getTenDonVi());
        }
        if (thoaMan) {
            i++;
            ThueBaoCoDinh* temp = dsThueBao[i];
            dsThueBao[i] = dsThueBao[j];
            dsThueBao[j] = temp;
        }
    }
    ThueBaoCoDinh* temp = dsThueBao[i + 1];
    dsThueBao[i + 1] = dsThueBao[high];
    dsThueBao[high] = temp;
    return i + 1;
}

void ThanhPho::quickSort(int low, int high, int tieuChi)
{
    if (low < high) {
        int pi = partition(low, high, tieuChi);
        quickSort(low, pi - 1, tieuChi);
        quickSort(pi + 1, high, tieuChi);
    }
}

int ThanhPho::binarySearchTheoSDT(const string& soDuoi)
{
    if (dsThueBao.empty()) return -1;
    int ranhGioi = 0;
    while (ranhGioi < dsThueBao.size() && dsThueBao[ranhGioi]->getLoai() == 1) ranhGioi++;

    int l = 0, r = ranhGioi - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (dsThueBao[m]->getSoDuoi() == soDuoi) return m;
        if (dsThueBao[m]->getSoDuoi() < soDuoi) l = m + 1;
        else r = m - 1;
    }

    l = ranhGioi; r = dsThueBao.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (dsThueBao[m]->getSoDuoi() == soDuoi) return m;
        if (dsThueBao[m]->getSoDuoi() < soDuoi) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

bool ThanhPho::kiemTraTrungSDT(const string& soDuoi)
{
    if (dsThueBao.empty()) return false;
    quickSort(0, dsThueBao.size() - 1, 1);
    return (binarySearchTheoSDT(soDuoi) != -1);
}

bool ThanhPho::kiemTraTonTai(const string& soDuoi)
{
    return kiemTraTrungSDT(soDuoi);
}

bool ThanhPho::themThueBao(ThueBaoCoDinh* tb)
{
    if (kiemTraTrungSDT(tb->getSoDuoi())) return false;
    dsThueBao.push_back(tb);
    ghiFile();
    return true;
}

bool ThanhPho::suaThueBao(int index, const string& ten, const string& dd, const string& dc, const string& sd)
{
    if (index < 0 || index >= dsThueBao.size()) return false;
    dsThueBao[index]->setTenDonVi(ten);
    dsThueBao[index]->setDinhDanh(dd);
    dsThueBao[index]->setDiaChi(dc);
    dsThueBao[index]->setSoDuoi(sd);
    ghiFile();
    return true;
}

bool ThanhPho::xoaThueBao(const string& soDuoi)
{
    quickSort(0, dsThueBao.size() - 1, 1);
    int idx = binarySearchTheoSDT(soDuoi);
    if (idx != -1) {
        delete dsThueBao[idx];
        dsThueBao.erase(idx);
        ghiFile();
        return true;
    }
    return false;
}

int ThanhPho::xoaSoTrung()
{
    if (dsThueBao.size() < 2) return 0;
    quickSort(0, dsThueBao.size() - 1, 1);
    int dem = 0;
    for (int i = 0; i < dsThueBao.size() - 1; ) {
        if (dsThueBao[i]->getSoDuoi() == dsThueBao[i + 1]->getSoDuoi()) {
            delete dsThueBao[i + 1];
            dsThueBao.erase(i + 1);
            dem++;
        } else {
            i++;
        }
    }
    if (dem > 0) ghiFile();
    return dem;
}

void ThanhPho::sapXepDanhBa(int tieuChi)
{
    if (dsThueBao.empty()) return;
    quickSort(0, dsThueBao.size() - 1, tieuChi);
    ghiFile();
}