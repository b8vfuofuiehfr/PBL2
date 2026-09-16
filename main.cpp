#include "QuanLyDanhBa.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

int main() 
{
    QuanLyDanhBa ql;
    int chon;
    string tinh; 

    do{
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

        if (!(cin >> chon)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap mot so!\n";
            cout << "\nNhan enter de quay lai menu...";
            cin.get();
            system("cls");
            continue;
        }

        switch (chon){
        case 1:
            cout << "Nhap tinh thanh (khong dung khoang trang): "; 
            cin >> tinh;
            system("cls"); 
            ql.themThueBao(tinh); 
            break;
        case 2:
            cout << "Nhap tinh can xem: "; 
            cin >> tinh;
            system("cls"); 
            ql.lietKeTheoTinh(tinh); 
            break;
        case 3:
            system("cls");
            ql.thongKeTheoTinh();
            break;
        case 4:
            system("cls");
            ql.hienThiTinh();
            break;
        case 5:
            cout << "Nhap tinh can kiem tra: ";
            cin >> tinh;
            system("cls");
            ql.kiemTraXoaTrung(tinh); 
            break;
        case 0:
            cout << "Ket thuc chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (chon != 0){
            cout << "\nNhan enter de quay lai menu...";
            cin.clear();
            if (chon != 1) { 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.get(); 
            system("cls"); 
        }

    } while (chon != 0);

    return 0;
}