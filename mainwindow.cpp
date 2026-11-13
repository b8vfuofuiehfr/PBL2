#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("HE THONG QUAN LY DANH BA DIEN THOAI CO DINH (PBL2)");
    resize(950, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 1. THANH CHON TINH
    QHBoxLayout *topLayout = new QHBoxLayout();
    cbTinh = new QComboBox();
    btnThemTinh = new QPushButton("Them Tinh Moi");
    btnXoaTinh = new QPushButton("Xoa Tinh Nay");
    topLayout->addWidget(cbTinh, 1);
    topLayout->addWidget(btnThemTinh);
    topLayout->addWidget(btnXoaTinh);
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

    // 4. CAC NUT CHUC NANG
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnThemThueBao = new QPushButton("Them Thue Bao");
    btnSuaThueBao  = new QPushButton("Sua Thue Bao");
    btnXoaThueBao  = new QPushButton("Xoa Thue Bao");
    btnSapXep      = new QPushButton("Sap Xep");
    btnXoaTrung    = new QPushButton("Loc Xoa Trung");

    btnLayout->addWidget(btnThemThueBao);
    btnLayout->addWidget(btnSuaThueBao);
    btnLayout->addWidget(btnXoaThueBao);
    btnLayout->addWidget(btnSapXep);
    btnLayout->addWidget(btnXoaTrung);
    mainLayout->addLayout(btnLayout);

    setCentralWidget(centralWidget);

    connect(cbTinh, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onChonTinh);
    connect(btnThemTinh, &QPushButton::clicked, this, &MainWindow::onThemTinh);
    connect(btnXoaTinh, &QPushButton::clicked, this, &MainWindow::onXoaTinh);
    connect(btnThemThueBao, &QPushButton::clicked, this, &MainWindow::onThemThueBao);
    connect(btnSuaThueBao, &QPushButton::clicked, this, &MainWindow::onSuaThueBao);
    connect(btnXoaThueBao, &QPushButton::clicked, this, &MainWindow::onXoaThueBao);
    connect(btnTimKiem, &QPushButton::clicked, this, &MainWindow::onTimKiem);
    connect(btnSapXep, &QPushButton::clicked, this, &MainWindow::onSapXep);
    connect(btnXoaTrung, &QPushButton::clicked, this, &MainWindow::onXoaTrung);

    taiDanhSachTinh();
}

MainWindow::~MainWindow(){}

void MainWindow::taiDanhSachTinh()
{
    cbTinh->blockSignals(true);
    cbTinh->clear();
    const auto& ds = QuanLyDanhBa::getInstance().getDanhSachTinh();
    for (int i = 0; i < ds.size(); i++) {
        cbTinh->addItem(QString::fromStdString(ds[i]));
    }
    cbTinh->blockSignals(false);

    if (cbTinh->count() > 0) hienThiLenBang(cbTinh->currentText().toStdString());
    else tableDanhBa->setRowCount(0);
}

void MainWindow::hienThiLenBang(const string& tenTinh)
{
    tableDanhBa->setRowCount(0);
    if (tenTinh.empty()) return;

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
}

void MainWindow::onChonTinh(int index){ if (index >= 0) hienThiLenBang(cbTinh->currentText().toStdString()); }

void MainWindow::onThemTinh()
{
    bool ok;
    QString ten = QInputDialog::getText(this, "Them Tinh", "Nhap ten tinh/thanh pho moi:", QLineEdit::Normal, "", &ok);
    if (ok && !ten.trimmed().isEmpty()) {
        QuanLyDanhBa::getInstance().themTinh(ten.trimmed().toStdString());
        taiDanhSachTinh();
        cbTinh->setCurrentText(ten.trimmed());
    }
}

void MainWindow::onXoaTinh()
{
    if (cbTinh->count() == 0) return;
    QString tinh = cbTinh->currentText();
    if (QMessageBox::question(this, "Xac nhan", "Xoa tinh " + tinh + " va toan bo danh ba?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QuanLyDanhBa::getInstance().xoaTinh(tinh.toStdString());
        taiDanhSachTinh();
    }
}

void MainWindow::onThemThueBao()
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

void MainWindow::onSuaThueBao()
{
    int row = tableDanhBa->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Chu y", "Vui long click chon mot thue bao tren bang de sua!");
        return;
    }

    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);
    auto& ds = tp.getDanhSachThueBao();

    bool ok;
    QString ten = QInputDialog::getText(this, "Sua", "Ten moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getTenDonVi()), &ok);
    if (!ok) return;
    QString dd = QInputDialog::getText(this, "Sua", "Dinh danh (CCCD/MST) moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getDinhDanh()), &ok);
    if (!ok) return;
    QString dc = QInputDialog::getText(this, "Sua", "Dia chi moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getDiaChi()), &ok);
    if (!ok) return;
    QString sd = QInputDialog::getText(this, "Sua", "So duoi moi:", QLineEdit::Normal, QString::fromStdString(ds[row]->getSoDuoi()), &ok);
    if (!ok) return;

    if (sd.toStdString() != ds[row]->getSoDuoi() && tp.kiemTraTrungSDT(sd.toStdString())) {
        QMessageBox::critical(this, "Loi", "So dien thoai moi bi trung lap!");
        return;
    }

    tp.suaThueBao(row, ten.toStdString(), dd.toStdString(), dc.toStdString(), sd.toStdString());
    hienThiLenBang(tinh);
    QMessageBox::information(this, "Thanh cong", "Da cap nhat thong tin thue bao!");
}

void MainWindow::onXoaThueBao()
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

void MainWindow::onTimKiem()
{
    QString tuKhoa = txtTimKiem->text().trimmed();
    if (tuKhoa.isEmpty()) return;

    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    if (tp.kiemTraTonTai(tuKhoa.toStdString())) {
        for (int i = 0; i < tableDanhBa->rowCount(); i++) {
            if (tableDanhBa->item(i, 5)->text().contains(tuKhoa)) {
                tableDanhBa->selectRow(i);
                QMessageBox::information(this, "Binary Search", "Tim thay thue bao tren bang!");
                return;
            }
        }
    } else {
        QMessageBox::information(this, "Ket qua", "Khong tim thay so dien thoai nay!");
    }
}

void MainWindow::onSapXep()
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

void MainWindow::onXoaTrung()
{
    if (cbTinh->count() == 0) return;
    string tinh = cbTinh->currentText().toStdString();
    ThanhPho tp(tinh);

    int dem = tp.xoaSoTrung();
    hienThiLenBang(tinh);
    if (dem > 0) QMessageBox::information(this, "Loc trung", "Da xoa " + QString::number(dem) + " so dien thoai bi trung lap!");
    else QMessageBox::information(this, "Loc trung", "Khong co so nao bi trung!");
}