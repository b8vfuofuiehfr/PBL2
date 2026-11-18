#include "DanhBaWindow.h"

// ==================== DANHBAWINDOW (LOP CHA) ====================
DanhBaWindow::DanhBaWindow(NguoiDung* user, QWidget *parent)
    : QMainWindow(parent), currentUser(user), isLoggingOut(false) {}

DanhBaWindow::~DanhBaWindow()
{
    delete currentUser;
}

void DanhBaWindow::khoiTao()
{
    thietLapGiaoDienChung();
    thietLapChucNangRieng(); // Goi da hinh tuy theo Admin hay User
    taiDanhSachTinh();
}

void DanhBaWindow::thietLapGiaoDienChung()
{
    resize(950, 620);

    QWidget *centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // 0. THANH TAI KHOAN & DANG XUAT
    QHBoxLayout *authLayout = new QHBoxLayout();
    QString ten = currentUser ? QString::fromStdString(currentUser->getTenDangNhap()) : "User";
    QString role = currentUser ? QString::fromStdString(currentUser->getVaiTro()) : "USER";
    lblVaiTro = new QLabel("Nguoi dung: <b>" + ten + "</b> | Vai tro: <b>" + role + "</b>");
    btnDangXuat = new QPushButton("Dang Xuat / Doi Tai Khoan");
    authLayout->addWidget(lblVaiTro, 1);
    authLayout->addWidget(btnDangXuat);
    mainLayout->addLayout(authLayout);

    // 1. THANH CHON TINH + SAP XEP + THONG KE
    topLayout = new QHBoxLayout();
    cbTinh = new QComboBox();
    btnSapXep = new QPushButton("Sap Xep");
    btnThongKe = new QPushButton("Thong Ke");
    topLayout->addWidget(new QLabel("Tinh/TP:"));
    topLayout->addWidget(cbTinh, 1);
    topLayout->addWidget(btnSapXep);
    topLayout->addWidget(btnThongKe);
    mainLayout->addLayout(topLayout);

    // 2. THANH TIM KIEM
    QHBoxLayout *searchLayout = new QHBoxLayout();
    txtTimKiem = new QLineEdit();
    txtTimKiem->setPlaceholderText("Nhap so duoi can tim");
    btnTimKiem = new QPushButton("Tim Kiem");
    searchLayout->addWidget(txtTimKiem, 1);
    searchLayout->addWidget(btnTimKiem);
    mainLayout->addLayout(searchLayout);

    // 3. BANG DANH BA
    tableDanhBa = new QTableWidget();
    tableDanhBa->setColumnCount(6);
    tableDanhBa->setHorizontalHeaderLabels({"STT", "Loai", "Ten Chu / Doanh Nghiep", "CCCD / MST", "Dia Chi", "So Dien Thoai"});
    tableDanhBa->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableDanhBa->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableDanhBa->verticalHeader()->setVisible(false);
    tableDanhBa->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableDanhBa->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(tableDanhBa);

    // 4. DONG THONG KE NHANH THEO TINH
    lblThongKe = new QLabel("Thong ke: Tong: 0 | Ca nhan: 0 | Doanh nghiep: 0");
    mainLayout->addWidget(lblThongKe);

    setCentralWidget(centralWidget);

    connect(btnDangXuat, &QPushButton::clicked, this, &DanhBaWindow::onDangXuat);
    connect(cbTinh, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DanhBaWindow::onChonTinh);
    connect(btnTimKiem, &QPushButton::clicked, this, &DanhBaWindow::onTimKiem);
    connect(txtTimKiem, &QLineEdit::returnPressed, this, &DanhBaWindow::onTimKiem);
    connect(btnSapXep, &QPushButton::clicked, this, &DanhBaWindow::onSapXep);
    connect(btnThongKe, &QPushButton::clicked, this, &DanhBaWindow::onThongKe);
}

void DanhBaWindow::closeEvent(QCloseEvent *event)
{
    if (!isLoggingOut) {
        QApplication::quit();
    }
    QMainWindow::closeEvent(event);
}

void DanhBaWindow::onDangXuat()
{
    isLoggingOut = true;
    emit dangXuat();
    close();
}

void DanhBaWindow::taiDanhSachTinh()
{
    cbTinh->blockSignals(true);
    cbTinh->clear();
    const auto& ds = QuanLyDanhBa::getInstance().getDanhSachTinh();
    for (int i = 0; i < ds.size(); i++) {
        cbTinh->addItem(QString::fromStdString(ds[i]));
    }
    cbTinh->blockSignals(false);

    if (cbTinh->count() > 0) hienThiLenBang(cbTinh->currentText().toStdString());
    else {
        tableDanhBa->setRowCount(0);
        lblThongKe->setText("Thong ke: Tong: 0 | Ca nhan: 0 | Doanh nghiep: 0");
    }
}

void DanhBaWindow::hienThiLenBang(const string& tenTinh)
{
    tableDanhBa->setRowCount(0);
    if (tenTinh.empty()) {
        lblThongKe->setText("Thong ke: Tong: 0 | Ca nhan: 0 | Doanh nghiep: 0");
        return;
    }

    ThanhPho tp(tenTinh);
    auto& ds = tp.getDanhSachThueBao();
    string mv = tp.getMaVung();

    for (int i = 0; i < ds.size(); i++) {
        tableDanhBa->insertRow(i);
        tableDanhBa->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        tableDanhBa->setItem(i, 1, new QTableWidgetItem(ds[i]->getLoai() == 1 ? "Ca Nhan" : "Doanh Nghiep"));
        tableDanhBa->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(ds[i]->getTenDonVi())));
        tableDanhBa->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(ds[i]->getDinhDanh())));
        tableDanhBa->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(ds[i]->getDiaChi())));
        tableDanhBa->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("(" + mv + ") " + ds[i]->getSoDuoi())));
    }

    lblThongKe->setText(
        QString("<b>Thong ke [%1]:</b> Tong: <b>%2</b> thue bao | Ca nhan: <b>%3</b> | Doanh nghiep: <b>%4</b>")
            .arg(QString::fromStdString(tenTinh))
            .arg(tp.getTongThueBao())
            .arg(tp.getSoCaNhan())
            .arg(tp.getSoDoanhNghiep())
        );
}

void DanhBaWindow::onChonTinh(int index)
{
    if (index >= 0) hienThiLenBang(cbTinh->currentText().toStdString());
}

void DanhBaWindow::onTimKiem()
{
    QString tuKhoa = txtTimKiem->text().trimmed();
    if (tuKhoa.isEmpty()) return;

    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    if (tp.kiemTraTonTai(tuKhoa.toStdString())) {
        for (int i = 0; i < tableDanhBa->rowCount(); i++) {
            if (tableDanhBa->item(i, 5)->text().endsWith(" " + tuKhoa)) {
                tableDanhBa->selectRow(i);
                QMessageBox::information(this, "Binary Search", "Tim thay thue bao tren bang!");
                return;
            }
        }
    } else {
        QMessageBox::information(this, "Ket qua", "Khong tim thay so dien thoai nay!");
    }
}

void DanhBaWindow::onSapXep()
{
    if (cbTinh->count() == 0) return;
    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    bool ok;
    QString chon = QInputDialog::getItem(this, "Sap Xep", "Chon tieu chi:", {"1. Theo So dien thoai", "2. Theo Ten (A-Z)"}, 0, false, &ok);
    if (!ok) return;

    tp.sapXepDanhBa(chon.startsWith("1") ? 1 : 2);
    hienThiLenBang(tinh);
}

void DanhBaWindow::onThongKe()
{
    const auto& dsTinh = QuanLyDanhBa::getInstance().getDanhSachTinh();

    QDialog dlg(this);
    dlg.setWindowTitle("BAO CAO THONG KE THUE BAO TOAN QUOC");
    dlg.resize(650, 400);

    QVBoxLayout *layout = new QVBoxLayout(&dlg);

    QTableWidget *tbl = new QTableWidget(&dlg);
    tbl->setColumnCount(5);
    tbl->setHorizontalHeaderLabels({"Tinh / Thanh Pho", "Ma Vung", "Ca Nhan", "Doanh Nghiep", "Tong Cong"});
    tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tbl->verticalHeader()->setVisible(false);
    tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int tongCN = 0, tongDN = 0, tongAll = 0;

    for (int i = 0; i < dsTinh.size(); i++) {
        ThanhPho tp(dsTinh[i]);
        int cn = tp.getSoCaNhan();
        int dn = tp.getSoDoanhNghiep();
        int tong = tp.getTongThueBao();

        tongCN += cn;
        tongDN += dn;
        tongAll += tong;

        tbl->insertRow(i);
        tbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dsTinh[i])));
        tbl->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(tp.getMaVung())));
        tbl->setItem(i, 2, new QTableWidgetItem(QString::number(cn)));
        tbl->setItem(i, 3, new QTableWidgetItem(QString::number(dn)));
        tbl->setItem(i, 4, new QTableWidgetItem(QString::number(tong)));
    }

    layout->addWidget(tbl);

    QLabel *lblTong = new QLabel(
        QString("<b>TONG HOP:</b> %1 Tinh/TP | <b>%2</b> Thue bao (Ca nhan: <b>%3</b> - Doanh nghiep: <b>%4</b>)")
            .arg(dsTinh.size())
            .arg(tongAll)
            .arg(tongCN)
            .arg(tongDN)
        );
    layout->addWidget(lblTong);

    QPushButton *btnDong = new QPushButton("Dong");
    connect(btnDong, &QPushButton::clicked, &dlg, &QDialog::accept);
    layout->addWidget(btnDong);

    dlg.exec();
}

// ==================== ADMINWINDOW (LOP CON) ====================
AdminWindow::AdminWindow(NguoiDung* user, QWidget *parent)
    : DanhBaWindow(user, parent)
{
    khoiTao();
}

void AdminWindow::thietLapChucNangRieng()
{
    setWindowTitle("QUAN TRI DANH BA DIEN THOAI - ADMIN (PBL2)");

    // Them nut quan ly tinh vao thanh tren cung
    btnThemTinh = new QPushButton("Them Tinh Moi");
    btnXoaTinh  = new QPushButton("Xoa Tinh Nay");
    topLayout->addWidget(btnThemTinh);
    topLayout->addWidget(btnXoaTinh);

    // Them hang nut chuc nang quan tri duoi bang
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnThemThueBao = new QPushButton("Them Thue Bao");
    btnSuaThueBao  = new QPushButton("Sua Thue Bao");
    btnXoaThueBao  = new QPushButton("Xoa Thue Bao");
    btnXoaTrung    = new QPushButton("Loc Xoa Trung");

    btnLayout->addWidget(btnThemThueBao);
    btnLayout->addWidget(btnSuaThueBao);
    btnLayout->addWidget(btnXoaThueBao);
    btnLayout->addWidget(btnXoaTrung);
    mainLayout->addLayout(btnLayout);

    connect(btnThemTinh, &QPushButton::clicked, this, &AdminWindow::onThemTinh);
    connect(btnXoaTinh, &QPushButton::clicked, this, &AdminWindow::onXoaTinh);
    connect(btnThemThueBao, &QPushButton::clicked, this, &AdminWindow::onThemThueBao);
    connect(btnSuaThueBao, &QPushButton::clicked, this, &AdminWindow::onSuaThueBao);
    connect(btnXoaThueBao, &QPushButton::clicked, this, &AdminWindow::onXoaThueBao);
    connect(btnXoaTrung, &QPushButton::clicked, this, &AdminWindow::onXoaTrung);
}

void AdminWindow::onThemTinh()
{
    bool ok;
    QString ten = QInputDialog::getText(this, "Them Tinh", "Nhap ten tinh/thanh pho moi:", QLineEdit::Normal, "", &ok);
    if (ok && !ten.trimmed().isEmpty()) {
        QuanLyDanhBa::getInstance().themTinh(ten.trimmed().toStdString());
        taiDanhSachTinh();
        cbTinh->setCurrentText(ten.trimmed());
    }
}

void AdminWindow::onXoaTinh()
{
    if (cbTinh->count() == 0) return;
    QString tinh = cbTinh->currentText();
    if (QMessageBox::question(this, "Xac nhan", "Xoa tinh " + tinh + " va toan bo danh ba?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QuanLyDanhBa::getInstance().xoaTinh(tinh.toStdString());
        taiDanhSachTinh();
    }
}

void AdminWindow::onThemThueBao()
{
    if (cbTinh->count() == 0) return;
    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    bool ok;
    QString loai = QInputDialog::getItem(this, "Loai", "Chon loai:", {"1. Ca Nhan", "2. Doanh Nghiep"}, 0, false, &ok);
    if (!ok) return;

    QString ten = QInputDialog::getText(this, "Nhap lieu", "Ten Chu / Doanh nghiep:", QLineEdit::Normal, "", &ok);
    if (!ok || ten.isEmpty()) return;
    QString dd = QInputDialog::getText(this, "Nhap lieu", loai.startsWith("1") ? "So CCCD:" : "Ma so thue:", QLineEdit::Normal, "", &ok);
    if (!ok || dd.isEmpty()) return;
    QString dc = QInputDialog::getText(this, "Nhap lieu", "Dia chi:", QLineEdit::Normal, "", &ok);
    if (!ok || dc.isEmpty()) return;
    QString sd = QInputDialog::getText(this, "Nhap lieu", "So duoi dien thoai:", QLineEdit::Normal, "", &ok);
    if (!ok || sd.isEmpty()) return;

    ThueBaoCoDinh* tb = nullptr;
    if (loai.startsWith("1")) tb = new ThueBaoCaNhan(ten.toStdString(), dd.toStdString(), dc.toStdString(), sd.toStdString());
    else tb = new ThueBaoDoanhNghiep(ten.toStdString(), dd.toStdString(), dc.toStdString(), sd.toStdString());

    if (!tp.themThueBao(tb)) {
        delete tb;
        QMessageBox::critical(this, "Loi", "So dien thoai da ton tai trong tinh!");
        return;
    }

    hienThiLenBang(tinh);
    QMessageBox::information(this, "Thanh cong", "Da them thue bao moi thanh cong!");
}

void AdminWindow::onSuaThueBao()
{
    int row = tableDanhBa->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Chu y", "Vui long click chon mot thue bao tren bang de sua!");
        return;
    }

    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);
    auto& ds = tp.getDanhSachThueBao();
    if (row >= ds.size()) return;

    bool ok;
    QString ten = QInputDialog::getText(this, "Sua", "Ten moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getTenDonVi()), &ok);
    if (!ok) return;
    QString dd = QInputDialog::getText(this, "Sua", "Dinh danh (CCCD/MST) moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getDinhDanh()), &ok);
    if (!ok) return;
    QString dc = QInputDialog::getText(this, "Sua", "Dia chi moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getDiaChi()), &ok);
    if (!ok) return;
    QString sd = QInputDialog::getText(this, "Sua", "So duoi moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getSoDuoi()), &ok);
    if (!ok) return;

    if (!tp.suaThueBao(row, ten.toStdString(), dd.toStdString(), dc.toStdString(), sd.toStdString())) {
        QMessageBox::critical(this, "Loi", "So dien thoai moi bi trung lap!");
        return;
    }

    hienThiLenBang(tinh);
    QMessageBox::information(this, "Thanh cong", "Da cap nhat thong tin thue bao!");
}

void AdminWindow::onXoaThueBao()
{
    int row = tableDanhBa->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Chu y", "Vui long click chon thue bao can xoa!");
        return;
    }

    QString ten = tableDanhBa->item(row, 2)->text();
    QString sdtRaw = tableDanhBa->item(row, 5)->text();
    string sd = sdtRaw.split(" ").last().toStdString();
    string tinh = cbTinh->currentText().toStdString();

    if (QMessageBox::question(this, "Xac nhan", "Xoa thue bao " + ten + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        ThanhPho tp(tinh);
        tp.xoaThueBao(sd);
        hienThiLenBang(tinh);
    }
}

void AdminWindow::onXoaTrung()
{
    if (cbTinh->count() == 0) return;
    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    int dem = tp.xoaSoTrung();
    hienThiLenBang(tinh);
    if (dem > 0) QMessageBox::information(this, "Loc trung", "Da xoa " + QString::number(dem) + " so dien thoai bi trung lap!");
    else QMessageBox::information(this, "Loc trung", "Khong co so nao bi trung!");
}

// ==================== USERWINDOW (LOP CON) ====================
UserWindow::UserWindow(NguoiDung* user, QWidget *parent)
    : DanhBaWindow(user, parent)
{
    khoiTao();
}

void UserWindow::thietLapChucNangRieng()
{
    setWindowTitle("TRA CUU DANH BA DIEN THOAI - NGUOI DUNG (PBL2)");
    // Neu muon an cot CCCD/MST voi User, bo comment dong duoi:
    // tableDanhBa->setColumnHidden(3, true);
}
