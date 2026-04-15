#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class BacSi
{
private:
    int maBS;
    string hoTen;
    string nghiepVu;
    string chuyenKhoa;
    string hocVi;
    string quyenHan;
    static int dem;

public:
    BacSi();
    BacSi(string ht, string nv, string ck, string hv, string qh);
    ~BacSi();

    int getMaBS() const { return maBS; }
    string getHoTen() const { return hoTen; }
    string getNghiepVu() const { return nghiepVu; }
    string getChuyenKhoa() const { return chuyenKhoa; }
    string getHocVi() const { return hocVi; }
    string getQuyenHan() const { return quyenHan; }

    void setHoTen(string ht) { hoTen = ht; }
    void setNghiepVu(string nv) { nghiepVu = nv; }
    void setChuyenKhoa(string ck) { chuyenKhoa = ck; }
    void setHocVi(string hv) { hocVi = hv; }
    void setQuyenHan(string qh) { quyenHan = qh; }

    void nhap();
    void xuat() const;

    bool operator==(const BacSi &other) const { return maBS == other.maBS; }

    friend istream &operator>>(istream &in, BacSi &bs);
    friend ostream &operator<<(ostream &out, const BacSi &bs);
};

// ================================================================
// CLASS PhongBenh
// ================================================================
class PhongBenh
{
private:
    string maPhong;
    string tenPhong;
    string loaiPhong; // "Thuong", "VIP"
    int soGiuong;
    int soGiuongDaNhan;

public:
    PhongBenh();
    PhongBenh(string mp, string tp, string lp, int sg);
    ~PhongBenh();

    string getMaPhong();
    string getTenPhong();
    string getLoaiPhong();
    int getSoGiuong();
    int getSoGiuongThongTrong();

    bool nhanGiuong(int &soGiuongDcCap);
    void traGiuong();

    void nhap();
    void xuat();
};

const int MAX_THUOC = 50;
// ================================================================
// CLASS Thuoc
// ================================================================
class Thuoc
{
private:
    string tenThuoc;
    int soLuong;
    double gia;

public:
    Thuoc();
    Thuoc(string tt, int sl, double g);
    ~Thuoc();

    string getTenThuoc() const;
    int getSoLuong() const;
    double getGia() const;

    void setTenThuoc(string t);
    void setSoLuong(int sl);
    void setGia(double g);

    void nhap();
    void xuat() const;
};

// ================================================================
// CLASS HoaDon
// Bổ sung: tiền khám, tiền giường, tiền thuốc tách biệt
// ================================================================
class HoaDon
{
private:
    int maBN;
    Thuoc dsThuoc[MAX_THUOC];
    int soLuongThuoc;
    double tienGiuong;   // phi giuong (tu dong tinh)
    double tienKham;     // phi kham do nguoi dung nhap
    double tongTien;

public:
    HoaDon();
    HoaDon(int mbn);
    ~HoaDon();

    int getMaBN();
    double getTongTien();
    double getTienGiuong();
    double getTienKham();

    void setTienGiuong(double tg);
    void setTienKham(double tk);

    void themThuoc(Thuoc t);
    void tinhTongTien();
    void nhap();
    void xuat() const;

    friend ostream &operator<<(ostream &out, const HoaDon &hd);
};

class DichVu
{
private:
    string tenDichVu;
    double giaDichVu;

public:
    DichVu() : tenDichVu(""), giaDichVu(0) {}
    DichVu(string ten, double gia) : tenDichVu(ten), giaDichVu(gia) {}

    string getTen() { return tenDichVu; }
    double getGia() { return giaDichVu; }

    void nhap()
    {
        cout << "Nhap ten dich vu: ";
        getline(cin >> ws, tenDichVu);
        cout << "Nhap gia dich vu (VND): ";
        cin >> giaDichVu;
    }
    void xuat()
    {
        cout << "  Dich vu: " << tenDichVu << " - Gia: " << fixed << setprecision(0) << giaDichVu << " VND\n";
    }
};


const int MAX_HS = 50;

class BenhNhan
{
private:
    string ten;
    int maBN;
    int tuoi;
    string diaChi;
    static int dem;
    // HO SO KCB
    string trieuChung;   // Trieu chung (thay ten benh)
    string loaiBenhAn;
    string chanDoan;
    int maBacSiKCB;
    string ngayVaoVien;
    string ngayRaVienDuKien; // Ngay ra vien du kien (luc nhap vien)
    string ngayRaVien;       // Ngay ra vien thuc te
    int soNgayDieuTri;

    // Luu tru co so vat chat
    string maPhongLuuTru;
    int soGiuongLuuTru;

    HoaDon *dsHoaDon[MAX_HS];
    int slHoaDon;

public:
    BenhNhan();
    BenhNhan(string t, int tuoi_bn, string dc);
    ~BenhNhan();

    string getTen();
    int getMaBN();
    int getTuoi();
    string getDiaChi();
    string getLoaiBenhAn();

    void setTen(string t);
    void setDiaChi(string dc);
    void setTuoi(int t);

    void setPhongLuuTru(string maP, int soG);
    string getMaPhongLuuTru();

    void nhap();
    void xuat();

    int quyTrinhKhamBenh();
    void thuTucXuatVien(string loaiPhongLuuTru);
    void themHoaDon(double donGiaGiuong = 0, string loaiPhong = "");
    void xemDanhSachHoaDon();

    double tinhTongVienPhi() const;

    friend istream &operator>>(istream &in, BenhNhan &bn);
    friend ostream &operator<<(ostream &out, const BenhNhan &bn);
};

const int MAX_SIZE = 100;

// ================================================================
// CLASS BenhVien
// ================================================================
class BenhVien
{
private:
    BenhNhan *dsBN[MAX_SIZE];
    int slBN;

    BacSi *dsBS[MAX_SIZE];
    int slBS;

    HoaDon *dsHD[MAX_SIZE];
    int slHD;

    PhongBenh *dsPB[MAX_SIZE];
    int slPB;

    static int nhapSoNguyen(const string &prompt);
    static double nhapSoThuc(const string &prompt);
    void hienThiMenu() const;

    void themHoSoBenhNhan();
    void xemDanhSachBenhNhan() const;
    void thaoTacBenhNhan();
    void dieuPhoiXepGiuong(int indexBN);

    void themThongTinBacSi();
    void xemDanhSachBacSi() const;
    void thaoTacBacSi();

    void quanLyPhongBenh();
    void soDoGiuongBenh() const;

    void baoCaoThongKe() const;

public:
    BenhVien();
    ~BenhVien();

    void chay();
};

// ==================================================================
// IMPLEMENTATIONS
// ==================================================================

int BacSi::dem = 1;

BacSi::BacSi()
    : maBS(dem++), hoTen(""), nghiepVu(""),
      chuyenKhoa(""), hocVi(""), quyenHan("") {}

BacSi::BacSi(string ht, string nv, string ck, string hv, string qh)
    : maBS(dem++), hoTen(ht), nghiepVu(nv),
      chuyenKhoa(ck), hocVi(hv), quyenHan(qh) {}

BacSi::~BacSi() {}

void BacSi::nhap()
{
    do
    {
        cout << "Nhap ho va ten bac si (khong duoc de trong): ";
        getline(cin >> ws, hoTen);
        if (hoTen.empty())
            cout << "  [!] Ho ten khong duoc de trong!\n";
    } while (hoTen.empty());

    cout << "Nhap nghiep vu (VD: Noi khoa, Ngoai khoa, ...): ";
    getline(cin >> ws, nghiepVu);
    cout << "Nhap chuyen khoa (VD: Tim mach, Than kinh, ...): ";
    getline(cin >> ws, chuyenKhoa);
    cout << "Nhap hoc vi (VD: Tien si, Thac si, Bac si, ...): ";
    getline(cin >> ws, hocVi);
    cout << "Nhap quyen han (VD: Truong khoa, Pho khoa, Bac si dieu tri, ...): ";
    getline(cin >> ws, quyenHan);
}

void BacSi::xuat() const
{
    cout << "Ma BS      : " << maBS << endl;
    cout << "Ho va ten  : " << hoTen << endl;
    cout << "Nghiep vu  : " << nghiepVu << endl;
    cout << "Chuyen khoa: " << chuyenKhoa << endl;
    cout << "Hoc vi     : " << hocVi << endl;
    cout << "Quyen han  : " << quyenHan << endl;
}

istream &operator>>(istream &in, BacSi &bs)
{
    do
    {
        cout << "Nhap ho va ten bac si (khong duoc de trong): ";
        getline(in >> ws, bs.hoTen);
        if (bs.hoTen.empty())
            cout << "  [!] Ho ten khong duoc de trong!\n";
    } while (bs.hoTen.empty());
    cout << "Nhap nghiep vu: ";
    getline(in >> ws, bs.nghiepVu);
    cout << "Nhap chuyen khoa: ";
    getline(in >> ws, bs.chuyenKhoa);
    cout << "Nhap hoc vi: ";
    getline(in >> ws, bs.hocVi);
    cout << "Nhap quyen han: ";
    getline(in >> ws, bs.quyenHan);
    return in;
}

ostream &operator<<(ostream &out, const BacSi &bs)
{
    out << "Ma BS      : " << bs.maBS << endl;
    out << "Ho va ten  : " << bs.hoTen << endl;
    out << "Nghiep vu  : " << bs.nghiepVu << endl;
    out << "Chuyen khoa: " << bs.chuyenKhoa << endl;
    out << "Hoc vi     : " << bs.hocVi << endl;
    out << "Quyen han  : " << bs.quyenHan << endl;
    return out;
}

// ==================== PHONG BENH ====================

PhongBenh::PhongBenh() : maPhong(""), tenPhong(""), loaiPhong("Thuong"), soGiuong(0), soGiuongDaNhan(0) {}

PhongBenh::PhongBenh(string mp, string tp, string lp, int sg)
{
    this->maPhong = mp;
    this->tenPhong = tp;
    this->loaiPhong = lp;
    this->soGiuong = sg;
    this->soGiuongDaNhan = 0;
}

PhongBenh::~PhongBenh() {}

string PhongBenh::getMaPhong() { return maPhong; }
string PhongBenh::getTenPhong() { return tenPhong; }
string PhongBenh::getLoaiPhong() { return loaiPhong; }
int PhongBenh::getSoGiuong() { return soGiuong; }
int PhongBenh::getSoGiuongThongTrong() { return soGiuong - soGiuongDaNhan; }

bool PhongBenh::nhanGiuong(int &soGiuongDcCap)
{
    if (soGiuongDaNhan < soGiuong)
    {
        soGiuongDaNhan++;
        soGiuongDcCap = soGiuongDaNhan;
        return true;
    }
    return false;
}

void PhongBenh::traGiuong()
{
    if (soGiuongDaNhan > 0)
        soGiuongDaNhan--;
}

void PhongBenh::nhap()
{
    cout << "Nhap ma phong: ";
    getline(cin >> ws, maPhong);
    cout << "Nhap ten phong: ";
    getline(cin >> ws, tenPhong);
    int loai;
    cout << "Chon loai phong (1. Thuong, 2. VIP): ";
    cin >> loai;
    loaiPhong = (loai == 2) ? "VIP" : "Thuong";
    cout << "Nhap so giuong toi da: ";
    cin >> soGiuong;
    soGiuongDaNhan = 0;
}

void PhongBenh::xuat()
{
    double donGia = (loaiPhong == "VIP") ? 1500000 : 1000000;
    cout << "Phong " << loaiPhong << " [" << maPhong << "] " << tenPhong
         << " - Giuong da nhan: " << soGiuongDaNhan << "/" << soGiuong
         << " - Phi/ngay: " << fixed << setprecision(0) << donGia << " VND\n";
}



// ==================== THUOC ====================

Thuoc::Thuoc() : tenThuoc(""), soLuong(0), gia(0) {}

Thuoc::Thuoc(string tt, int sl, double g)
{
    this->tenThuoc = tt;
    setSoLuong(sl);
    setGia(g);
}

Thuoc::~Thuoc() {}

string Thuoc::getTenThuoc() const { return tenThuoc; }
int Thuoc::getSoLuong() const { return soLuong; }
double Thuoc::getGia() const { return gia; }

void Thuoc::setTenThuoc(string t) { this->tenThuoc = t; }
void Thuoc::setSoLuong(int sl) { this->soLuong = (sl > 0) ? sl : 0; }
void Thuoc::setGia(double g) { this->gia = (g > 0) ? g : 0; }

void Thuoc::nhap()
{
    cout << "  Nhap ten thuoc/dich vu (khong de trong): ";
    do
    {
        getline(cin >> ws, tenThuoc);
        if (tenThuoc.empty())
            cout << "  [!] Ten khong duoc de trong! Nhap lai: ";
    } while (tenThuoc.empty());

    cout << "  Nhap so luong (> 0): ";
    while (!(cin >> soLuong) || soLuong <= 0)
    {
        cin.clear(); cin.ignore();
        cout << "  [!] So luong phai > 0! Nhap lai: ";
    }

    cout << "  Nhap don gia (VND, > 0): ";
    while (!(cin >> gia) || gia <= 0)
    {
        cin.clear(); cin.ignore();
        cout << "  [!] Don gia phai > 0! Nhap lai: ";
    }
    setGia(gia);
}

void Thuoc::xuat() const
{
    cout << "  Ten       : " << tenThuoc << endl;
    cout << "  So luong  : " << soLuong << endl;
    cout << "  Don gia   : " << fixed << setprecision(0) << gia << " VND" << endl;
    cout << "  Thanh tien: " << fixed << setprecision(0) << soLuong * gia << " VND" << endl;
}

// ==================== HOA DON ====================

HoaDon::HoaDon() : maBN(0), soLuongThuoc(0), tienGiuong(0), tienKham(0), tongTien(0) {}
HoaDon::HoaDon(int mbn) : maBN(mbn), soLuongThuoc(0), tienGiuong(0), tienKham(0), tongTien(0) {}
HoaDon::~HoaDon() {}

int HoaDon::getMaBN() { return maBN; }
double HoaDon::getTongTien() { return tongTien; }
double HoaDon::getTienGiuong() { return tienGiuong; }
double HoaDon::getTienKham() { return tienKham; }

void HoaDon::setTienGiuong(double tg) { tienGiuong = tg; }
void HoaDon::setTienKham(double tk) { tienKham = tk; }

void HoaDon::themThuoc(Thuoc t)
{
    if (soLuongThuoc < MAX_THUOC)
        dsThuoc[soLuongThuoc++] = t;
    else
        cout << "[!] Hoa don da day (toi da " << MAX_THUOC << " loai)!\n";
}

void HoaDon::tinhTongTien()
{
    double tienThuoc = 0;
    for (int i = 0; i < soLuongThuoc; i++)
        tienThuoc += dsThuoc[i].getSoLuong() * dsThuoc[i].getGia();
    tongTien = tienGiuong + tienKham + tienThuoc;
}

void HoaDon::nhap()
{
    cout << "--- Lap hoa don ---\n";

    // Nhap phi kham
    cout << "Nhap phi kham benh (VND, >= 0): ";
    while (!(cin >> tienKham) || tienKham < 0)
    {
        cin.clear(); cin.ignore();
        cout << "  [!] Phi kham khong hop le! Nhap lai: ";
    }

    // Nhap thuoc
    int n;
    cout << "Nhap so loai thuoc/dich vu can them: ";
    cin >> n;
    if (n < 0) n = 0;

    if (soLuongThuoc + n > MAX_THUOC)
    {
        cout << "Khong the them qua " << MAX_THUOC - soLuongThuoc << " loai nua.\n";
        n = MAX_THUOC - soLuongThuoc;
    }

    int start = soLuongThuoc;
    soLuongThuoc += n;
    for (int i = start; i < soLuongThuoc; i++)
    {
        cout << "\nThuoc/dich vu thu " << i + 1 << ":\n";
        dsThuoc[i].nhap();
    }
    tinhTongTien();
}

void HoaDon::xuat() const
{
    double tienThuoc = 0;
    for (int i = 0; i < soLuongThuoc; i++)
        tienThuoc += dsThuoc[i].getSoLuong() * dsThuoc[i].getGia();

    cout << "\n===== HOA DON =====\n";
    cout << "Benh nhan (Ma BN) : " << (maBN > 0 ? to_string(maBN) : "Chua xac dinh") << "\n";
    cout << "--------------------\n";
    cout << "Phi kham benh     : " << fixed << setprecision(0) << tienKham << " VND\n";
    if (tienGiuong > 0)
        cout << "Phi luu tru giuong: " << fixed << setprecision(0) << tienGiuong << " VND\n";
    if (soLuongThuoc > 0)
    {
        cout << "--------------------\n";
        cout << "Chi tiet thuoc/dich vu:\n";
        for (int i = 0; i < soLuongThuoc; i++)
        {
            cout << "\n  [" << i + 1 << "] ";
            dsThuoc[i].xuat();
        }
        cout << "  => Tong tien thuoc: " << fixed << setprecision(0) << tienThuoc << " VND\n";
    }
    cout << "====================\n";
    cout << "TONG CONG          : " << fixed << setprecision(0) << tongTien << " VND\n";
    cout << "====================\n";
}

ostream &operator<<(ostream &out, const HoaDon &hd)
{
    double tienThuoc = 0;
    for (int i = 0; i < hd.soLuongThuoc; i++)
        tienThuoc += hd.dsThuoc[i].getSoLuong() * hd.dsThuoc[i].getGia();

    out << "\n===== HOA DON =====\n";
    out << "Benh nhan (Ma BN) : " << (hd.maBN > 0 ? to_string(hd.maBN) : "Chua xac dinh") << "\n";
    out << "Phi kham benh     : " << fixed << setprecision(0) << hd.tienKham << " VND\n";
    if (hd.tienGiuong > 0)
        out << "Phi luu tru giuong: " << fixed << setprecision(0) << hd.tienGiuong << " VND\n";
    for (int i = 0; i < hd.soLuongThuoc; i++)
    {
        out << "\n  Thuoc " << i + 1 << ":\n";
        out << "  Ten: " << hd.dsThuoc[i].getTenThuoc() << endl;
        out << "  SL : " << hd.dsThuoc[i].getSoLuong() << endl;
        out << "  Gia: " << fixed << setprecision(0) << hd.dsThuoc[i].getGia() << " VND\n";
    }
    out << "TONG CONG: " << fixed << setprecision(0) << hd.tongTien << " VND\n";
    return out;
}

// ==================== BENH NHAN ====================

int BenhNhan::dem = 1;

BenhNhan::BenhNhan()
    : trieuChung(""), loaiBenhAn(""), chanDoan(""), maBacSiKCB(0),
      ngayVaoVien(""), ngayRaVienDuKien(""), ngayRaVien(""),
      soNgayDieuTri(0), maPhongLuuTru(""), soGiuongLuuTru(0), slHoaDon(0)
{
    this->maBN = dem++;
    this->ten = "";
    this->tuoi = 0;
    this->diaChi = "";
}

BenhNhan::BenhNhan(string t, int tuoi_bn, string dc)
    : trieuChung(""), loaiBenhAn(""), chanDoan(""), maBacSiKCB(0),
      ngayVaoVien(""), ngayRaVienDuKien(""), ngayRaVien(""),
      soNgayDieuTri(0), maPhongLuuTru(""), soGiuongLuuTru(0), slHoaDon(0)
{
    this->maBN = dem++;
    this->ten = t;
    this->tuoi = tuoi_bn;
    this->diaChi = dc;
}

BenhNhan::~BenhNhan()
{
    for (int i = 0; i < slHoaDon; i++)
        delete dsHoaDon[i];
}

string BenhNhan::getTen() { return ten; }
int BenhNhan::getMaBN() { return maBN; }
int BenhNhan::getTuoi() { return tuoi; }
string BenhNhan::getDiaChi() { return diaChi; }
string BenhNhan::getMaPhongLuuTru() { return maPhongLuuTru; }
string BenhNhan::getLoaiBenhAn() { return loaiBenhAn; }

void BenhNhan::setTen(string t) { ten = t; }
void BenhNhan::setDiaChi(string dc) { diaChi = dc; }
void BenhNhan::setTuoi(int t) { tuoi = t; }
void BenhNhan::setPhongLuuTru(string maP, int soG)
{
    maPhongLuuTru = maP;
    soGiuongLuuTru = soG;
}

void BenhNhan::nhap()
{
    cout << "Nhap ho ten (khong de trong): ";
    getline(cin >> ws, ten);
    while (ten.empty())
    {
        cout << "  [!] Ho ten khong duoc de trong! Nhap lai: ";
        getline(cin >> ws, ten);
    }

    string ageStr;
    bool validAge = false;
    do
    {
        cout << "Nhap tuoi (>0): ";
        cin >> ageStr;
        try
        {
            int t = stoi(ageStr);
            if (t > 0) { tuoi = t; validAge = true; }
            else cout << "  [!] Tuoi phai lon hon 0!\n";
        }
        catch (...) { cout << "  [!] Vui long nhap so nguyen!\n"; }
    } while (!validAge);

    cout << "Nhap dia chi: ";
    getline(cin >> ws, diaChi);
}

void BenhNhan::xuat()
{
    cout << "\n--- THONG TIN BENH NHAN ---\n";
    cout << "Benh nhan: " << ten << " | Ma BN: " << maBN
         << " | Tuoi: " << tuoi << " | Dia chi: " << diaChi << "\n";

    if (loaiBenhAn != "")
    {
        cout << " ==> HO SO CHUYEN MON (" << loaiBenhAn << ") <==\n";
        cout << "  - Ma BS kham         : " << maBacSiKCB << "\n";
        cout << "  - Ngay kham/vao vien : " << ngayVaoVien << "\n";
        cout << "  - Trieu chung        : " << trieuChung << "\n";
        cout << "  - Chuan doan BS      : " << chanDoan << "\n";
        if (loaiBenhAn == "Noi tru (Nhap vien)" || loaiBenhAn == "Noi tru (Da xuat vien)")
        {
            if (maPhongLuuTru != "")
                cout << "  - Vi tri giuong      : Phong " << maPhongLuuTru << " (Giuong " << soGiuongLuuTru << ")\n";
            cout << "  - Ngay ra vien du kien: " << ngayRaVienDuKien << "\n";
            cout << "  - Ngay ra vien thuc te: " << (ngayRaVien.empty() ? "(Chua xuat vien)" : ngayRaVien) << "\n";
            cout << "  - So ngay dieu tri   : " << soNgayDieuTri << " ngay\n";
        }
        if (slHoaDon > 0)
        {
            double tongPhi = tinhTongVienPhi();
            cout << "  - Tong vien phi phat sinh: " << fixed << setprecision(0) << tongPhi << " VND\n";
        }
    }
}

istream &operator>>(istream &in, BenhNhan &bn)
{
    bn.nhap();
    return in;
}

ostream &operator<<(ostream &out, const BenhNhan &bn)
{
    out << "Ma BN: " << bn.maBN << " | Ho ten: " << bn.ten;
    return out;
}

// ==================== KCB ====================

int BenhNhan::quyTrinhKhamBenh()
{
    cout << "\n--- QUY TRINH KHAM BENH CHO BENH NHAN " << ten << " ---\n";
    cout << "Nhap ma bac si kham: ";
    cin >> maBacSiKCB;

    cout << "Nhap ngay kham (dd/mm/yyyy): ";
    getline(cin >> ws, ngayVaoVien);

    cout << "Nhap trieu chung: ";
    getline(cin >> ws, trieuChung);

    cout << "Chuan doan cua bac si: ";
    getline(cin >> ws, chanDoan);

    cout << "\nDanh gia ket qua cua bac si - Muc do tinh trang benh:\n";
    cout << "  1. Nang => Phai NHAP VIEN dieu tri noi tru.\n";
    cout << "  2. Nhe => Ke thuoc, xuat hoa don va dieu tri ngoai tru.\n";
    cout << "Chon danh gia (1 hoac 2): ";
    int mucDo;
    cin >> mucDo;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        mucDo = 2;
    }

    if (mucDo == 1)
    {
        loaiBenhAn = "Noi tru (Nhap vien)";
        cout << "[!] Tinh trang NANG: Yeu cau dieu tri Noi Tru.\n";
        cout << "Nhap so ngay dieu tri du kien (tu 1 ngay): ";
        cin >> soNgayDieuTri;
        cout << "Nhap ngay ra vien du kien (dd/mm/yyyy): ";
        getline(cin >> ws, ngayRaVienDuKien);
        ngayRaVien = "";
        cout << "Da lap ho so nhap vien. Dang chuyen xep giuong...\n";
        return 1;
    }
    else
    {
        loaiBenhAn = "Ngoai tru (Ke thuoc)";
        soNgayDieuTri = 0;
        ngayRaVien = "";
        ngayRaVienDuKien = "";
        cout << "[!] Tinh trang NHE: Chuyen sang ke thuoc va xuat Hoa Don.\n";
        themHoaDon();
        cout << "Benh nhan da duoc xuat hoa don va co the di ve.\n";
        return 0;
    }
}

void BenhNhan::thuTucXuatVien(string loaiPhongLuuTru)
{
    if (loaiBenhAn != "Noi tru (Nhap vien)")
    {
        cout << "[!] Benh nhan nay KHONG co ho so dang nam vien Noi tru.\n";
        return;
    }
    cout << "\n--- THU TUC XUAT VIEN CHO " << ten << " ---\n";
    cout << "Ngay vao vien       : " << ngayVaoVien << "\n";
    cout << "Ngay ra vien du kien: " << ngayRaVienDuKien << "\n";
    cout << "Nhap ngay ra vien chinh thuc (dd/mm/yyyy): ";
    getline(cin >> ws, ngayRaVien);

    // Phi giuong: VIP = 1.5tr/ngay, Thuong = 1tr/ngay
    double donGia = (loaiPhongLuuTru == "VIP") ? 1500000.0 : 1000000.0;
    double tienGiuong = donGia * soNgayDieuTri;

    cout << "\nThong tin phi luu tru:\n";
    cout << "  Loai phong  : " << loaiPhongLuuTru << "\n";
    cout << "  Don gia/ngay: " << fixed << setprecision(0) << donGia << " VND\n";
    cout << "  So ngay DT  : " << soNgayDieuTri << " ngay\n";
    cout << "  Phi giuong  : " << fixed << setprecision(0) << tienGiuong << " VND\n";

    loaiBenhAn = "Noi tru (Da xuat vien)";
    cout << "Da ghi nhan xuat vien. Chuyen sang thanh toan vien phi...\n";
    themHoaDon(tienGiuong, loaiPhongLuuTru);
    cout << "THU TUC XUAT VIEN HOAN TAT!\n";
}

void BenhNhan::themHoaDon(double donGiaGiuong, string loaiPhong)
{
    if (slHoaDon >= MAX_HS)
    {
        cout << "[!] Vuot qua so luong hoa don cho phep.\n";
        return;
    }
    cout << "\n--- Lap hoa don cho Benh nhan " << maBN << " ---\n";
    dsHoaDon[slHoaDon] = new HoaDon(maBN);
    dsHoaDon[slHoaDon]->setTienGiuong(donGiaGiuong);
    if (donGiaGiuong > 0 && soNgayDieuTri > 0)
    {
        cout << " [+] Phi luu tru giuong " << loaiPhong
             << " (" << soNgayDieuTri << " ngay x "
             << fixed << setprecision(0) << (donGiaGiuong / soNgayDieuTri)
             << " VND) = " << fixed << setprecision(0) << donGiaGiuong << " VND da duoc tinh.\n";
    }
    dsHoaDon[slHoaDon]->nhap();
    slHoaDon++;
    cout << "Hoa don thu " << slHoaDon << " lap xong!\n";
}

void BenhNhan::xemDanhSachHoaDon()
{
    cout << "\n--- Danh sach Hoa don - BN: " << ten << " (" << maBN << ") ---\n";
    if (slHoaDon == 0) { cout << "  (Chua co hoa don nao)\n"; return; }
    for (int i = 0; i < slHoaDon; i++)
    {
        cout << "--- Phieu [" << i + 1 << "] ---\n";
        dsHoaDon[i]->xuat();
    }
}

double BenhNhan::tinhTongVienPhi() const
{
    double total = 0;
    for (int i = 0; i < slHoaDon; i++)
        total += dsHoaDon[i]->getTongTien();
    return total;
}

// ==================== BENH VIEN ====================

BenhVien::BenhVien() : slBN(0), slBS(0), slHD(0), slPB(0)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        dsBN[i] = nullptr;
        dsBS[i] = nullptr;
        dsHD[i] = nullptr;
        dsPB[i] = nullptr;
    }
    // 20 phong Thuong
    for (int i = 1; i <= 20; i++)
    {
        string ma = (i < 10) ? "T0" + to_string(i) : "T" + to_string(i);
        dsPB[slPB++] = new PhongBenh(ma, "Phong Thuong", "Thuong", 6);
    }
    // 5 phong VIP
    for (int i = 1; i <= 5; i++)
    {
        string ma = "V0" + to_string(i);
        dsPB[slPB++] = new PhongBenh(ma, "Phong VIP", "VIP", 1);
    }
    // 20 bac si
    dsBS[slBS++] = new BacSi("Nguyen Van An",    "Noi khoa",       "Tim mach",              "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Nguyen Van Bao",   "Ngoai khoa",     "Phau thuat tong hop",   "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Nguyen Van Vu",    "San phu khoa",   "Phu khoa",              "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Nguyen Thi Dung",  "Than kinh",      "Than kinh trung uong",  "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Tran Van Anh",     "Nhi khoa",       "Nhi khoa tong hop",     "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Than Van Chien",   "Co Xuong Khop",  "Chinh hinh",            "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Chu Van Tai",      "Mat khoa",       "Khuc xa - Glauco",      "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Bui Thi Ha",       "Tai Mui Hong",   "Tai mui hong",          "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Ngo Van Hung",     "Rang Ham Mat",   "Chinh nha - Cay ghep",  "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Cao Thi Huong",    "Da lieu",        "Da lieu tham my",       "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Ngo Thi Trang",    "Noi khoa",       "Tieu hoa - Gan",        "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Dao Thi Linh",     "Ung buou",       "Ung thu noi khoa",      "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Ha Van Khanh",     "Tham my",        "Phau thuat tham my",    "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Ha Thi Ngoc",      "Noi khoa",       "Mach mau - Khoi u",     "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("La Van Phuong",    "Truyen nhiem",   "Benh truyen nhiem",     "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Duong Thi Oanh",   "Tam than",       "Tam ly lam sang",       "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Doan Van Quang",   "Noi khoa",       "Tiet nieu - Huyet ap",  "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Vu Van Tuan",      "Ngoai khoa",     "Phau thuat nao",        "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Truong Van Sang",  "San phu khoa",   "Vo sinh - Hiem muon",   "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Vo Thi Lan",       "Nhi khoa",       "So sinh - Cap cuu Nhi", "Thac si", "Bac si dieu tri");
}

BenhVien::~BenhVien()
{
    for (int i = 0; i < slBN; i++) delete dsBN[i];
    for (int i = 0; i < slBS; i++) delete dsBS[i];
    for (int i = 0; i < slPB; i++) delete dsPB[i];
}

int BenhVien::nhapSoNguyen(const string &prompt)
{
    int val;
    while (true)
    {
        cout << prompt;
        cin >> val;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  [!] Chi duoc nhap so! Nhap lai.\n";
    }
    return val;
}

double BenhVien::nhapSoThuc(const string &prompt)
{
    double val;
    while (true)
    {
        cout << prompt;
        cin >> val;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  [!] Chi duoc nhap so! Nhap lai.\n";
    }
    return val;
}

void BenhVien::hienThiMenu() const
{
    cout << "\n==========================================================\n";
    cout << "               HE THONG QUAN LY BENH VIEN\n";
    cout << "==========================================================\n";
    cout << "  --- I. QUAN LY DOI TUONG ---\n";
    cout << "  1. Them benh nhan moi (Dang ky kham)\n";
    cout << "  2. Xem danh sach benh nhan\n";
    cout << "  3. Tra cuu / Cap nhat / Xoa benh nhan\n\n";
    cout << "  4. Them bac si moi\n";
    cout << "  5. Danh sach doi ngu bac si\n";
    cout << "  6. Tra cuu / Cap nhat / Xoa bac si\n\n";
    cout << "  --- II. QUAN LY CO SO VAT CHAT ---\n";
    cout << "  7. Quan ly phong benh (Them/Sua/Xoa)\n";
    cout << "  8. So do phan bo giuong benh\n\n";
    cout << "  --- III. HE THONG & THONG KE ---\n";
    cout << "  9. Bao cao tong doanh thu\n";
    cout << "  0. Thoat chuong trinh\n";
    cout << "==========================================================\n";
}

void BenhVien::themHoSoBenhNhan()
{
    if (slBN >= MAX_SIZE)
    {
        cout << "[!] Danh sach benh nhan da day!\n";
        return;
    }
    cout << "\n--- Dang ky kham cho benh nhan moi ---\n";

    // Hien thi danh sach bac si truoc khi nhap
    cout << "\nDanh sach bac si hien co:\n";
    for (int i = 0; i < slBS; i++)
    {
        cout << "  Ma " << dsBS[i]->getMaBS()
             << " | " << dsBS[i]->getHoTen()
             << " (" << dsBS[i]->getChuyenKhoa() << ")\n";
    }
    cout << "\n";

    dsBN[slBN] = new BenhNhan();
    dsBN[slBN]->nhap();
    slBN++;

    int tinHieuXepGiuong = dsBN[slBN - 1]->quyTrinhKhamBenh();
    if (tinHieuXepGiuong == 1)
    {
        dieuPhoiXepGiuong(slBN - 1);
    }
}

void BenhVien::dieuPhoiXepGiuong(int indexBN)
{
    if (slPB == 0)
    {
        cout << "[!] Benh vien chua co phong luu tru. Khong the xep giuong!\n";
        return;
    }
    cout << "\n--- XEP GIUONG CHO BENH NHAN ---\n";
    cout << "Danh sach phong con giuong trong:\n";
    bool coPhongTrong = false;
    for (int i = 0; i < slPB; i++)
    {
        if (dsPB[i]->getSoGiuongThongTrong() > 0)
        {
            double donGia = (dsPB[i]->getLoaiPhong() == "VIP") ? 1500000 : 1000000;
            cout << "  - [" << dsPB[i]->getMaPhong() << "] " << dsPB[i]->getTenPhong()
                 << " (" << dsPB[i]->getLoaiPhong() << ")"
                 << " | Trong: " << dsPB[i]->getSoGiuongThongTrong() << " giuong"
                 << " | Phi: " << fixed << setprecision(0) << donGia << " VND/ngay\n";
            coPhongTrong = true;
        }
    }
    if (!coPhongTrong)
    {
        cout << "[!] Benh vien DA HET GIUONG!\n";
        return;
    }

    string maChon;
    int viTriPhong = -1;
    while (true)
    {
        cout << "Nhap Ma Phong muon chon: ";
        getline(cin >> ws, maChon);
        for (int i = 0; i < slPB; i++)
        {
            if (dsPB[i]->getMaPhong() == maChon && dsPB[i]->getSoGiuongThongTrong() > 0)
            {
                viTriPhong = i;
                break;
            }
        }
        if (viTriPhong != -1) break;
        cout << "  [!] Ma phong khong hop le hoac da day! Nhap lai.\n";
    }

    int giuongDuocCap = 0;
    if (dsPB[viTriPhong]->nhanGiuong(giuongDuocCap))
    {
        dsBN[indexBN]->setPhongLuuTru(dsPB[viTriPhong]->getMaPhong(), giuongDuocCap);
        cout << "=====> XEP GIUONG THANH CONG <=====\n";
        cout << "Benh nhan vao Giuong so " << giuongDuocCap
             << " - Phong " << dsPB[viTriPhong]->getMaPhong()
             << " (" << dsPB[viTriPhong]->getLoaiPhong() << ")\n";
    }
}

void BenhVien::xemDanhSachBenhNhan() const
{
    cout << "\n--- DANH SACH BENH NHAN (" << slBN << " nguoi) ---\n";
    if (slBN == 0) { cout << "  (Chua co benh nhan nao)\n"; return; }
    for (int i = 0; i < slBN; i++)
    {
        cout << "\n  [" << i + 1 << "] ";
        dsBN[i]->xuat();
    }
}

void BenhVien::thaoTacBenhNhan()
{
    if (slBN == 0)
    {
        cout << "[!] Chua co benh nhan nao!\n";
        return;
    }

    int ma = nhapSoNguyen("\nNhap ma benh nhan can tim (0 de quay lai): ");
    if (ma == 0) return;

    int index = -1;
    for (int i = 0; i < slBN; i++)
    {
        if (dsBN[i]->getMaBN() == ma) { index = i; break; }
    }
    if (index == -1)
    {
        cout << "[!] Khong tim thay benh nhan co ma " << ma << ".\n";
        return;
    }

    int choice;
    do
    {
        cout << "\n--- THAO TAC VOI BENH NHAN ---\n";
        dsBN[index]->xuat();
        cout << "\nThao tac:\n";
        cout << "  1. Xem chi tiet ho so benh an\n";
        cout << "  2. Cap nhat thong tin ca nhan\n";
        cout << "  3. Xoa benh nhan\n";
        cout << "  4. Lam thu tuc XUAT VIEN & Thanh toan (Noi tru)\n";
        cout << "  5. Xem danh sach hoa don\n";
        cout << "  0. Quay lai menu chinh\n";
        choice = nhapSoNguyen("Lua chon: ");

        if (choice == 1)
        {
            dsBN[index]->xuat();
        }
        else if (choice == 2)
        {
            cout << "Cap nhat thong tin cho benh nhan:\n";
            dsBN[index]->nhap();
            cout << "Cap nhat thanh cong!\n";
        }
        else if (choice == 3)
        {
            string xacNhan;
            cout << "Xac nhan xoa benh nhan nay (y/n)? ";
            cin >> xacNhan;
            if (xacNhan == "y" || xacNhan == "Y")
            {
                delete dsBN[index];
                for (int i = index; i < slBN - 1; i++)
                    dsBN[i] = dsBN[i + 1];
                slBN--;
                cout << "Da xoa benh nhan.\n";
                return;
            }
            else cout << "Huy thao tac xoa.\n";
        }
        else if (choice == 4)
        {
            string mp = dsBN[index]->getMaPhongLuuTru();
            string lp = "Thuong";
            if (mp != "")
            {
                for (int i = 0; i < slPB; i++)
                {
                    if (dsPB[i]->getMaPhong() == mp)
                    {
                        lp = dsPB[i]->getLoaiPhong();
                        dsPB[i]->traGiuong();
                        dsBN[index]->setPhongLuuTru("", 0);
                        break;
                    }
                }
            }
            dsBN[index]->thuTucXuatVien(lp);
        }
        else if (choice == 5)
        {
            dsBN[index]->xemDanhSachHoaDon();
        }
    } while (choice != 0);
}

void BenhVien::themThongTinBacSi()
{
    if (slBS >= MAX_SIZE)
    {
        cout << "[!] Danh sach bac si da day!\n";
        return;
    }
    cout << "\n--- Nhap thong tin bac si moi ---\n";
    dsBS[slBS] = new BacSi();
    dsBS[slBS]->nhap();
    cout << "Da them bac si: " << dsBS[slBS]->getHoTen()
         << " | Ma BS = " << dsBS[slBS]->getMaBS()
         << " | Chuyen khoa: " << dsBS[slBS]->getChuyenKhoa() << "\n";
    slBS++;
}

void BenhVien::xemDanhSachBacSi() const
{
    cout << "\n--- DANH SACH BAC SI (" << slBS << " nguoi) ---\n";
    if (slBS == 0) { cout << "  (Chua co bac si nao)\n"; return; }
    for (int i = 0; i < slBS; i++)
    {
        cout << "\n  [" << i + 1 << "] ";
        dsBS[i]->xuat();
    }
}

void BenhVien::thaoTacBacSi()
{
    if (slBS == 0)
    {
        cout << "[!] Chua co bac si nao!\n";
        return;
    }

    int ma = nhapSoNguyen("\nNhap ma bac si can tim (0 de quay lai): ");
    if (ma == 0) return;
    int index = -1;
    for (int i = 0; i < slBS; i++)
    {
        if (dsBS[i]->getMaBS() == ma) { index = i; break; }
    }
    if (index == -1) { cout << "[!] Khong tim thay.\n"; return; }

    cout << "\n--- THONG TIN BAC SI ---\n";
    dsBS[index]->xuat();
    cout << "\n  1. Cap nhat thong tin\n  2. Xoa bac si\n  0. Quay lai\n";
    int choice = nhapSoNguyen("Lua chon: ");

    if (choice == 1)
    {
        dsBS[index]->nhap();
        cout << "Da cap nhat.\n";
    }
    else if (choice == 2)
    {
        delete dsBS[index];
        for (int i = index; i < slBS - 1; i++)
            dsBS[i] = dsBS[i + 1];
        slBS--;
        cout << "Da xoa bac si.\n";
    }
}

void BenhVien::quanLyPhongBenh()
{
    cout << "\n--- QUAN LY PHONG BENH ---\n";
    cout << "1. Them phong moi\n2. Sua thong tin phong\n3. Xoa phong\n0. Quay lai\n";
    int choice = nhapSoNguyen("Lua chon: ");

    if (choice == 1)
    {
        if (slPB >= MAX_SIZE) { cout << "[!] Danh sach phong day!\n"; return; }
        dsPB[slPB] = new PhongBenh();
        dsPB[slPB]->nhap();
        slPB++;
        cout << "Them phong thanh cong.\n";
    }
    else if (choice == 2 || choice == 3)
    {
        if (slPB == 0) { cout << "Chua co phong!\n"; return; }
        string ma;
        cout << "Nhap ma phong: ";
        getline(cin >> ws, ma);
        int index = -1;
        for (int i = 0; i < slPB; i++)
        {
            if (dsPB[i]->getMaPhong() == ma) { index = i; break; }
        }
        if (index == -1) { cout << "Khong tim thay phong!\n"; return; }
        if (choice == 2)
        {
            dsPB[index]->nhap();
            cout << "Da sua.\n";
        }
        else
        {
            delete dsPB[index];
            for (int i = index; i < slPB - 1; i++) dsPB[i] = dsPB[i + 1];
            slPB--;
            cout << "Da xoa.\n";
        }
    }
}

void BenhVien::soDoGiuongBenh() const
{
    cout << "\n--- SO DO PHAN BO GIUONG BENH ---\n";
    if (slPB == 0) { cout << "  (Chua co co so vat chat nao)\n"; return; }
    int tongGiuong = 0, tongDaNhan = 0;
    for (int i = 0; i < slPB; i++)
    {
        cout << "  [" << i + 1 << "] ";
        dsPB[i]->xuat();
        tongGiuong += dsPB[i]->getSoGiuong();
        tongDaNhan += (dsPB[i]->getSoGiuong() - dsPB[i]->getSoGiuongThongTrong());
    }
    cout << "------------------------------------\n";
    cout << "  Tong giuong: " << tongGiuong << " | Da nhan: " << tongDaNhan
         << " | Con trong: " << tongGiuong - tongDaNhan << "\n";
}



void BenhVien::baoCaoThongKe() const
{
    cout << "\n============================================\n";
    cout << "      BAO CAO DOANH THU BENH VIEN\n";
    cout << "============================================\n";
    if (slBN == 0) { cout << "  (Chua co benh nhan nao)\n"; return; }

    double tongToanVien = 0;
    int soCoBill = 0;

    for (int i = 0; i < slBN; i++)
    {
        double phi = dsBN[i]->tinhTongVienPhi();
        if (phi > 0)
        {
            cout << "  BN: " << dsBN[i]->getTen()
                 << " [" << dsBN[i]->getLoaiBenhAn() << "]"
                 << " | Chi phi: " << fixed << setprecision(0) << phi << " VND\n";
            tongToanVien += phi;
            soCoBill++;
        }
    }
    cout << "--------------------------------------------\n";
    cout << " > Benh nhan co phat sinh phi: " << soCoBill << "/" << slBN << "\n";
    cout << " > TONG DOANH THU: " << fixed << setprecision(0) << tongToanVien << " VND\n";
    cout << "============================================\n";
}



void BenhVien::chay()
{
    int choice;
    do
    {
        hienThiMenu();
        choice = nhapSoNguyen("Lua chon cua ban (0-9): ");
        switch (choice)
        {
        case 1:  themHoSoBenhNhan(); break;
        case 2:  xemDanhSachBenhNhan(); break;
        case 3:  thaoTacBenhNhan(); break;
        case 4:  themThongTinBacSi(); break;
        case 5:  xemDanhSachBacSi(); break;
        case 6:  thaoTacBacSi(); break;
        case 7:  quanLyPhongBenh(); break;
        case 8:  soDoGiuongBenh(); break;
        case 9:  baoCaoThongKe(); break;
        case 0:  cout << "\nDong he thong. Tam biet!\n"; break;
        default: cout << "[!] Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

int main()
{
    BenhVien benhVien;
    benhVien.chay();
    return 0;
}
