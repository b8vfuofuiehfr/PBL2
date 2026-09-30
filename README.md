# 📞 ĐỒ ÁN PBL2: HỆ THỐNG QUẢN LÝ DANH BẠ ĐIỆN THOẠI CỐ ĐỊNH

Dự án Lập trình Hướng đối tượng (OOP) bằng ngôn ngữ C++, tập trung vào việc quản lý danh bạ thuê bao điện thoại cố định theo từng Tỉnh/Thành phố với kiến trúc xử lý dữ liệu đồng bộ giữa RAM và File.

## 🎓 Thông tin sinh viên
* **Sinh viên thực hiện:** Nguyễn Quốc Thịnh, Phan Huỳnh Khánh Bảo
* **Lớp:** 25T-DT3, 25T-DT2
* **Trường:** Đại học Bách khoa – Đại học Đà Nẵng

---

## 🚀 Chức năng chính
Chương trình cung cấp giao diện Console (CLI) với các chức năng:
1. **Thêm thuê bao:** Phân loại tự động giữa **Cá nhân** (lưu CCCD) và **Doanh nghiệp** (lưu Mã Số Thuế).
2. **Liệt kê danh bạ:** Hiển thị danh sách thuê bao chi tiết theo Tỉnh/Thành phố được yêu cầu.
3. **Thống kê:** Thống kê tổng số lượng thuê bao hiện có của từng Tỉnh/Thành phố.
4. **Hiển thị danh sách Tỉnh/Thành phố:** Quản lý linh hoạt số lượng tỉnh thành đang có trong hệ thống.
5. **Tìm và xóa số trùng lặp:** Tự động rà soát, dọn dẹp các số điện thoại bị trùng trong cùng một tỉnh và cập nhật lại file dữ liệu.

---

## 💻 Kiến trúc & Kỹ thuật Hướng đối tượng (OOP) áp dụng
Đồ án được thiết kế tuân thủ nghiêm ngặt 4 tính chất của OOP và cơ chế quản lý bộ nhớ an toàn:

* **Tính Đóng gói (Encapsulation):** Các thuộc tính nhạy cảm (`soDienThoai`, `cccd`, `maSoThue`) được bảo vệ bằng access modifiers `private/protected`, chỉ truy xuất qua các phương thức public/getter.
* **Tính Kế thừa (Inheritance):** Các lớp `ThueBaoCaNhan` và `ThueBaoDoanhNghiep` kế thừa từ lớp cơ sở `ThueBaoCoDinh`, giúp tái sử dụng mã nguồn hiệu quả.
* **Tính Trừu tượng (Abstraction):** Lớp `ThueBaoCoDinh` là một Abstract Class chứa hàm thuần ảo (Pure Virtual Function) `virtual string taochuoi() const = 0;`, ép buộc các lớp con phải tự định nghĩa lại format dữ liệu lưu file.
* **Tính Đa hình (Polymorphism):** 
  * Quản lý danh sách chung thông qua mảng con trỏ lớp cha: `vector<ThueBaoCoDinh*> dsThueBao`.
  * Trình biên dịch tự động gọi đúng phương thức `xuat()` tương ứng với kiểu thuê bao thực tế lúc Runtime (Late Binding).
* **Quản lý bộ nhớ (Memory Management):** Sử dụng **Hàm hủy ảo (Virtual Destructor)** `virtual ~ThueBaoCoDinh()` để đảm bảo dọn dẹp triệt để dữ liệu cấp phát động (Dynamic Allocation), ngăn chặn hoàn toàn lỗi rò rỉ bộ nhớ (Memory Leak).
* **Kiến trúc Dữ liệu (RAM & File-based Sync):** Load dữ liệu từ file `.dat` lên RAM (Vector) khi đối tượng được khởi tạo, xử lý logic tốc độ cao trên RAM và tự động đồng bộ (ghi đè) xuống ổ cứng khi có thay đổi.

---

## 📂 Cấu trúc thư mục (Directory Tree)
```text
📦 PBL2_QuanLyDanhBa
 ┣ 📂 data                      # Thư mục chứa dữ liệu hệ thống (Tự sinh/Đồng bộ)
 ┃ ┣ 📜 0_DanhSachTinh.dat      # Lưu danh sách các tỉnh đang quản lý
 ┃ ┣ 📜 DaNang.dat              # File dữ liệu thuê bao mẫu
 ┃ ┣ 📜 HaNoi.dat
 ┃ ┗ 📜 HCM.dat
 ┣ 📜 main.cpp                  # Khởi chạy giao diện Menu (CLI)
 ┣ 📜 QuanLyDanhBa.h/.cpp       # Class quản lý luồng cấp cao & danh sách tỉnh
 ┣ 📜 ThanhPho.h/.cpp           # Class xử lý logic tập trung (Đọc/Ghi file, Lưu trữ vector)
 ┣ 📜 ThueBaoCoDinh.h/.cpp      # Class Lớp cha (Trừu tượng) và các Lớp con (Cá nhân, Doanh nghiệp)
 ┗ 📜 README.md
