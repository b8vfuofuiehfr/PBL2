#include "ThanhPho.h"
#include "ThueBaoCoDinh.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

ThanhPho::ThanhPho(const string& ten) 
    : tenTinh(ten), maVung("") 
{
    docFile();   
}

ThanhPho::~ThanhPho()
{
    for (int i = 0; i < dsThueBao.size(); i++) delete dsThueBao[i];
    dsThueBao.clear();
}

const string& ThanhPho::getTenTinh() const { return tenTinh; }
const string& ThanhPho::getMaVung() const { return maVung; }
void ThanhPho::setMaVung(const string& ma) { maVung = ma; }
string ThanhPho::getFileName() const { return "data/" + tenTinh + ".dat"; }

void ThanhPho::docFile()
{
    ifstream in(getFileName());
    if (!in) return;

    getline(in, maVung);

    string line;
    while (getline(in, line)){
        if (line.empty()) continue;
        ThueBaoCoDinh* tb = ThueBaoCoDinh::chinhsuadata(line);
        if (tb != nullptr) dsThueBao.push_back(tb);
    }
    in.close();
}

void ThanhPho::ghiFile()
{
    ofstream out(getFileName());
    if (!out) return;

    out << maVung << "\n";

    for (int i = 0; i < dsThueBao.size(); i++) 
        out << dsThueBao[i]->taochuoi() << "\n";
    out.close();
}

int ThanhPho::partition(int low, int high, int tieuChi) 
{
    ThueBaoCoDinh* pivot = dsThueBao[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool thoaMan = false;

        if (dsThueBao[j]->getLoai() != pivot->getLoai()) 
            thoaMan = (dsThueBao[j]->getLoai() < pivot->getLoai());
        else {
            if (tieuChi == 1) 
                thoaMan = (dsThueBao[j]->getSoDuoi() < pivot->getSoDuoi());
            else 
                thoaMan = (dsThueBao[j]->getTenDonVi() < pivot->getTenDonVi());
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
    while (ranhGioi < dsThueBao.size() && dsThueBao[ranhGioi]->getLoai() == 1) {
        ranhGioi++;
    }

    int left = 0, right = ranhGioi - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dsThueBao[mid]->getSoDuoi() == soDuoi) return mid;
        if (dsThueBao[mid]->getSoDuoi() < soDuoi) left = mid + 1;
        else right = mid - 1;
    }

    left = ranhGioi;
    right = dsThueBao.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dsThueBao[mid]->getSoDuoi() == soDuoi) return mid;
        if (dsThueBao[mid]->getSoDuoi() < soDuoi) left = mid + 1;
        else right = mid - 1;
    }

    return -1; 
}

bool ThanhPho::kiemTraTrungSDT(const string& soDuoi) 
{
    if (dsThueBao.empty()) return false;

    quickSort(0, dsThueBao.size() - 1, 1);
    if (binarySearchTheoSDT(soDuoi) != -1) {
        cout << " [!] So dien thoai " << soDuoi << " da ton tai trong tinh/thanh pho nay!\n";
        return true;
    }
    return false;
}

bool ThanhPho::kiemTraTonTai(const string& soDuoi) 
{
    if (dsThueBao.empty()) {
        cout << "[-] Danh ba rong!\n";
        return false;
    }

    quickSort(0, dsThueBao.size() - 1, 1);
    int viTri = binarySearchTheoSDT(soDuoi);

    if (viTri != -1) {
        cout << "\n[+] TIM THAY THUE BAO (Qua Binary Search):\n";
        dsThueBao[viTri]->xuat(maVung);
        return true;
    }

    cout << "\n[-] Khong tim thay so dien thoai " << soDuoi << " tai " << tenTinh << "!\n";
    return false;
}

bool ThanhPho::xoaThueBao(const string& soDuoi) 
{
    if (dsThueBao.empty()) {
        cout << "[-] Danh ba rong!\n";
        return false;
    }

    quickSort(0, dsThueBao.size() - 1, 1);
    int viTri = binarySearchTheoSDT(soDuoi);

    if (viTri != -1) {
        delete dsThueBao[viTri];
        dsThueBao.erase(viTri);
        ghiFile();
        cout << "xoa thanh cong thue bao: " << soDuoi << "!\n";
        return true;
    }

    cout << "[-] Khong tim thay thue bao co so " << soDuoi << " de xoa!\n";
    return false;
}

void ThanhPho::xoaSoTrung() 
{
    if (dsThueBao.size() < 2) {
        cout << "Danh sach khong co so trung!\n";
        return;
    }

    quickSort(0, dsThueBao.size() - 1, 1);

    int count = 0;
    for (int i = 0; i < dsThueBao.size() - 1; ) {
        if (dsThueBao[i]->getSoDuoi() == dsThueBao[i + 1]->getSoDuoi()) {
            delete dsThueBao[i + 1];
            dsThueBao.erase(i + 1);
            count++;
        } else {
            i++;
        }
    }
    ghiFile(); 
    cout << "=> Da sap xep va xoa " << count << " so bi trung trong tinh " << tenTinh << "!\n";
}

void ThanhPho::themThueBao() 
{
    if (maVung.empty()) {
        cout << "- Nhap ma vung dien thoai cho " << tenTinh << " (VD: 024, 028, 0236...): ";
        cin >> maVung;
    }

    int loai;
    cout << "\n+--- CHON LOAI THUE BAO CAN THEM ---+" << "\n";
    cout << "| 1. Thue bao Ca nhan               |" << "\n";
    cout << "| 2. Thue bao Doanh nghiep          |" << "\n";
    cout << "+-----------------------------------+" << "\n";
    cout << " >> Nhap lua chon (1 hoac 2): ";
    if (!(cin >> loai)){
        cout << "Loi nhap du lieu, huy thao tac!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    
    cin.ignore(10000, '\n');

    string ten, diaChi, soDuoi, thongTinRieng;

    cout << "- Nhap ten (Nguoi/Doanh Nghiep): ";
    getline(cin, ten);
    if (loai == 1){
        cout << "- Nhap CCCD: ";
        getline(cin, thongTinRieng);
    }
    else if (loai == 2){
        cout << "- Nhap Ma so thue: ";
        getline(cin, thongTinRieng);
    }
    else {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    cout << "- Nhap dia chi: ";
    getline(cin, diaChi);
    
    cout << "- Nhap so duoi dien thoai (khong nhap ma vung " << maVung << "): ";
    getline(cin, soDuoi);

    if (kiemTraTrungSDT(soDuoi)) {
        cout << "Them that bai do so dien thoai da ton tai!\n";
        return;
    }

    ThueBaoCoDinh* tb = nullptr;
    if (loai == 1) tb = new ThueBaoCaNhan(ten, thongTinRieng, diaChi, soDuoi);
    else tb = new ThueBaoDoanhNghiep(ten, thongTinRieng, diaChi, soDuoi);

    dsThueBao.push_back(tb);
    ghiFile();

    cout << "Them thue bao thanh cong! SDT hoan chinh: (" << maVung << ") " << soDuoi << "\n";
}

void ThanhPho::lietKeDanhBa() 
{
    cout << "\n--- Danh sach thue bao tai " << tenTinh << " (Ma vung: " << maVung << ") ---\n";
    if (dsThueBao.empty()) {
        cout << "(Chua co thue bao nao)\n";
        return;
    }
    for (int i = 0; i < dsThueBao.size(); i++) 
        dsThueBao[i]->xuat(maVung); 
}

int ThanhPho::demSoLuongThueBao() const{ return dsThueBao.size(); }

void ThanhPho::sapXepDanhBa() 
{
    if (dsThueBao.empty()) {
        cout << "Danh ba tinh " << tenTinh << " rong!\n";
        return;
    }

    cout << "\n+--- CHON KIEU SAP XEP ---+\n";
    cout << "| 1. Sap xep theo So dien thoai  |\n";
    cout << "| 2. Sap xep theo Ten chu thue bao |\n";
    cout << "+--------------------------------+\n";
    cout << ">> Nhap lua chon: ";
    int chon;
    cin >> chon;

    if (chon == 1) {
        quickSort(0, dsThueBao.size() - 1, 1);
        ghiFile();
        cout << "=> Da sap xep danh ba theo SO DIEN THOAI thanh cong!\n";
    } else if (chon == 2) {
        quickSort(0, dsThueBao.size() - 1, 2);
        ghiFile();
        cout << "=> Da sap xep danh ba theo TEN thanh cong!\n";
    } else {
        cout << "Lua chon khong hop le!\n";
    }
}