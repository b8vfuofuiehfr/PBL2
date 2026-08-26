#include "QuanLyDanhBa.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    QuanLyDanhBa ql;
    int chon;

    do {
        cout << "\n===================================\n";
        cout << " QUAN LY DANH BA DIEN THOAI CO DINH\n";
        cout << "===================================\n";
        cout << "1. Them thue bao\n";
        cout << "2. Liet ke danh ba theo Tinh/Thanh Pho\n";
        cout << "3. Thong ke so luong thue bao theo Tinh/Thanh Pho\n";
        cout << "4. Hien thi cac tinh dang quan ly\n";
        cout << "5. Tim va xoa so dien thoai trung\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";

        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap mot so!\n";
            continue;
        }

        switch (chon) {
        case 1:
            ql.themThueBao();
            break;
        case 2:
            ql.lietKeTheoTinh();
            break;
        case 3:
            ql.thongKeTheoTinh();
            break;
        case 4:
            ql.hienThiTinh();
            break;
        case 5:
            ql.kiemTraXoaTrung();
            break;
        case 0:
            cout << "Ket thuc chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);

    return 0;
}
