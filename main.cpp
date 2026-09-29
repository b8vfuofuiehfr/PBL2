#include "QuanLyDanhBa.h"
#include <iostream>
#include <limits>
#include <cstdlib> 

using namespace std;

int main() {
    QuanLyDanhBa ql;
    int chon;

    do {
        system("cls"); 
        
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
            cin.ignore(10000, '\n');
            cout << " [!] Vui long nhap mot so!\n";
            system("pause"); 
            continue;
        }

        switch (chon) {
        case 1:
            system("cls");
            ql.themThueBao();
            cout << endl;
            system("pause"); 
            break;
            
        case 2:
            system("cls");
            ql.lietKeTheoTinh();
            cout << endl;
            system("pause"); 
            break;
            
        case 3:
            system("cls");
            ql.thongKeTheoTinh();
            cout << endl;
            system("pause"); 
            break;
            
        case 4:
            system("cls");
            ql.hienThiTinh();
            cout << endl;
            system("pause");
            break;
            
        case 5:
            system("cls");
            ql.kiemTraXoaTrung();
            cout << endl;
            system("pause");
            break;
            
        case 0:
            system("cls");
            cout << "\n Ket thuc chuong trinh. Chuc ban bao ve PBL2 thanh cong!\n\n";
            break;
            
        default:
            cout << " [!] Lua chon khong hop le!\n";
            system("pause");
        }
    } while (chon != 0);

    return 0;
}