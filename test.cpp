#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::path thuMuc = "data";
    ofstream fileDanhSach("DanhSachTinh.dat");

    if (!fileDanhSach) {
        cout << "Khong tao duoc file DanhSachTinh.dat";
        return 0;
    }

    if (!fs::exists(thuMuc)) {
        cout << "Thu muc data khong ton tai";
        return 0;
    }

    for (const auto& thanhPhan : fs::directory_iterator(thuMuc)) {
        if (thanhPhan.is_regular_file() &&
            thanhPhan.path().extension() == ".dat") {

            string tenTinh = thanhPhan.path().stem().string();
            fileDanhSach << tenTinh << '\n';
        }
    }

    fileDanhSach.close();

    cout << "Da tao danh sach tinh";
    return 0;
}