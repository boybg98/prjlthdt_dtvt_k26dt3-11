#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
// ================================================================
// CLASS BacSi
// Thuoc tinh: maBS, hoTen, nghiepVu, chuyenKhoa, hocVi, quyenHan
// ================================================================
class BacSi
{
private:
    int maBS;          // Ma dinh danh bac si
    string hoTen;      // Ho va ten bac si
    string nghiepVu;   // Nghiep vu (VD: Noi khoa, Ngoai khoa, ...)
    string chuyenKhoa; // Chuyen khoa (VD: Tim mach, Than kinh, ...)
    string hocVi;      // Hoc vi (VD: Tien si, Thac si, Bac si, ...)
    string quyenHan;   // Quyen han (VD: Truong khoa, Pho khoa, Bac si dieu tri, ...)

    static int dem; // Bien dem de tu dong tang maBS

public:
    // ---- Constructors ----
    BacSi();
    BacSi(string hoTen, string nghiepVu, string chuyenKhoa,
          string hocVi, string quyenHan);

    // ---- Destructor ----
    ~BacSi();

    // ---- Getters ----
    int getMaBS() const { return maBS; }
    string getHoTen() const { return hoTen; }
    string getNghiepVu() const { return nghiepVu; }
    string getChuyenKhoa() const { return chuyenKhoa; }
    string getHocVi() const { return hocVi; }
    string getQuyenHan() const { return quyenHan; }

    // ---- Setters ----
    void setHoTen(string ht) { hoTen = ht; }
    void setNghiepVu(string nv) { nghiepVu = nv; }
    void setChuyenKhoa(string ck) { chuyenKhoa = ck; }
    void setHocVi(string hv) { hocVi = hv; }
    void setQuyenHan(string qh) { quyenHan = qh; }

    // ---- Nhap / Xuat ----
    void nhap();
    void xuat() const;

    // ---- Nap chong toan tu ----
    bool operator==(const BacSi &other) const { return maBS == other.maBS; }

    friend istream &operator>>(istream &in, BacSi &bs);
    friend ostream &operator<<(ostream &out, const BacSi &bs);
};

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
    PhongBenh(string maPhong, string tenPhong, string loaiPhong, int soGiuong);
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
    Thuoc(string tenThuoc, int soLuong, double gia);
    ~Thuoc();

    // Getter
    string getTenThuoc() const;
    int getSoLuong() const;
    double getGia() const;

    // Setter voi validation
    void setTenThuoc(string t);
    void setSoLuong(int sl);
    void setGia(double g);

    void nhap();
    void xuat() const;
};
// ================================================================
// CLASS HoaDon - Chua danh sach thuoc, lien ket voi BenhNhan
// ================================================================
class HoaDon
{
private:
    int maBN;
    Thuoc dsThuoc[MAX_THUOC];
    int soLuongThuoc;
    double tongTien;

public:
    HoaDon();
    HoaDon(int maBN);
    ~HoaDon();

    // Getter
    int getMaBN();
    double getTongTien();

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
        cout << "Nhap gia dich vu: ";
        cin >> giaDichVu;
    }
    void xuat()
    {
        cout << "Dich vu: " << tenDichVu << " - Gia: " << giaDichVu << "\n";
    }
};

class DanhMuc
{
private:
    Thuoc dsThuoc[MAX_THUOC];
    int soLuongThuoc;

    DichVu dsDichVu[MAX_THUOC];
    int soLuongDichVu;

public:
    DanhMuc();
    ~DanhMuc();

    void themThuoc();
    void themDichVu();
    void xemDanhSach();
};

const int MAX_HS = 50;
// ================================================================
// CLASS BenhNhan - Chua cac thuoc tinh KCB rui trưc tiêp
// ================================================================
class BenhNhan
{
private:
    string ten;
    int maBN;
    int tuoi;
    string diaChi;
    static int dem; // tu tang ma benh nhan
    // ------------------------------------
    // THUOC TINH HO SO KCB (Truc tiep)
    // ------------------------------------
    string tenBenh;     // Ten benh moi them
    string loaiBenhAn;  // "Noi tru", "Ngoai tru", hoac rong (chua lap)
    string chanDoan;    // Noi tru: Ly do nhap vien | Ngoai tru: Ten benh / Chan doan
    int maBacSiKCB;     // Ma BS tiep thuc
    string ngayVaoVien; // Chung cho Ngoai tru (ngay kham) va Noi tru
    string ngayRaVien;  // Chi danh cho Noi tru
    int soNgayDieuTri;  // Chi danh cho Noi tru

    // Thong tin luu tru co so vat chat
    string maPhongLuuTru;
    int soGiuongLuuTru;

    // ------------------------------------
    HoaDon *dsHoaDon[MAX_HS];
    int slHoaDon;

public:
    BenhNhan();
    BenhNhan(string ten, int tuoi, string diaChi);
    ~BenhNhan();

    // Getter
    string getTen();
    int getMaBN();
    int getTuoi();
    string getDiaChi();

    // Setter
    void setTen(string t);
    void setDiaChi(string dc);
    void setTuoi(int t);

    void setPhongLuuTru(string maP, int soG);
    string getMaPhongLuuTru();

    // Ham nhap xuat thong tin ca nhan co ban
    void nhap();
    void xuat();

    // NGHIEP VU KCB TREN CHINH BENH NHAN (Linear Flow)
    int quyTrinhKhamBenh();
    void thuTucXuatVien(string loaiPhongLuuTru);
    void themHoaDon(double donGiaGiuong = 0, string loaiPhong = "");
    void xemDanhSachHoaDon();

    double tinhTongVienPhi() const;

    // Nap chong
    friend istream &operator>>(istream &in, BenhNhan &bn);
    friend ostream &operator<<(ostream &out, const BenhNhan &bn);
};

const int MAX_SIZE = 100;

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

    DanhMuc danhMucTraCuu;

    static int nhapSoNguyen(const string &prompt);
    void hienThiMenu() const;

    // --- I. QUAN LY DOI TUONG ---
    void themHoSoBenhNhan();             // 1
    void xemDanhSachBenhNhan() const;    // 2
    void thaoTacBenhNhan();              // 3
    void dieuPhoiXepGiuong(int indexBN); // Helper xep giuong

    void themThongTinBacSi();      // 4
    void xemDanhSachBacSi() const; // 5
    void thaoTacBacSi();           // 6

    // --- II. QUAN LY CO SO VAT CHAT ---
    void quanLyPhongBenh();      // 7
    void soDoGiuongBenh() const; // 8

    // --- III. QUAN LY HE THONG & THONG KE ---
    void quanLyDanhMuc();       // 9
    void baoCaoThongKe() const; // 10
    void saoLuuDuLieu();        // 11
    void khoiPhucDuLieu();      // 12

public:
    BenhVien();
    ~BenhVien();

    void chay();
};

// Khoi tao bien static
int BacSi::dem = 1;

// ---- Constructor mac dinh ----
BacSi::BacSi()
    : maBS(dem++), hoTen(""), nghiepVu(""),
      chuyenKhoa(""), hocVi(""), quyenHan("") {}

// ---- Constructor co tham so ----
BacSi::BacSi(string hoTen, string nghiepVu, string chuyenKhoa,
             string hocVi, string quyenHan)
    : maBS(dem++), hoTen(hoTen), nghiepVu(nghiepVu),
      chuyenKhoa(chuyenKhoa), hocVi(hocVi), quyenHan(quyenHan) {}

// ---- Destructor ----
BacSi::~BacSi() {}

// ---- Nhap ----
void BacSi::nhap()
{
    // Ho ten (khong duoc de trong)
    do
    {
        cout << "Nhap ho va ten bac si (khong duoc de trong): ";
        getline(cin >> ws, hoTen);
        if (hoTen.empty())
            cout << "  [!] Ho ten khong duoc de trong! Nhap lai.\n";
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

// ---- Xuat ----
void BacSi::xuat() const
{
    cout << "Ma BS      : " << maBS << endl;
    cout << "Ho va ten  : " << hoTen << endl;
    cout << "Nghiep vu  : " << nghiepVu << endl;
    cout << "Chuyen khoa: " << chuyenKhoa << endl;
    cout << "Hoc vi     : " << hocVi << endl;
    cout << "Quyen han  : " << quyenHan << endl;
}

// ---- Nap chong >> ----
istream &operator>>(istream &in, BacSi &bs)
{
    do
    {
        cout << "Nhap ho va ten bac si (khong duoc de trong): ";
        getline(in >> ws, bs.hoTen);
        if (bs.hoTen.empty())
            cout << "  [!] Ho ten khong duoc de trong! Nhap lai.\n";
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

// ---- Nap chong << ----
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

PhongBenh::PhongBenh() : maPhong(""), tenPhong(""), loaiPhong("Thuong"), soGiuong(0), soGiuongDaNhan(0) {}

PhongBenh::PhongBenh(string maPhong, string tenPhong, string loaiPhong, int soGiuong)
{
    this->maPhong = maPhong;
    this->tenPhong = tenPhong;
    this->loaiPhong = loaiPhong;
    this->soGiuong = soGiuong;
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
        soGiuongDcCap = soGiuongDaNhan; // Cap cho ho giuong ke tiep
        return true;
    }
    return false;
}

void PhongBenh::traGiuong()
{
    if (soGiuongDaNhan > 0)
    {
        soGiuongDaNhan--;
    }
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
    if (loai == 2)
        loaiPhong = "VIP";
    else
        loaiPhong = "Thuong";

    cout << "Nhap so giuong toi da: ";
    cin >> soGiuong;
    soGiuongDaNhan = 0;
}

void PhongBenh::xuat()
{
    cout << "Phong " << loaiPhong << " [" << maPhong << "] " << tenPhong
         << " - Giuong da nhan: " << soGiuongDaNhan << "/" << soGiuong << "\n";
}

DanhMuc::DanhMuc() : soLuongThuoc(0), soLuongDichVu(0) {}
DanhMuc::~DanhMuc() {}

void DanhMuc::themThuoc()
{
    if (soLuongThuoc < MAX_THUOC)
    {
        dsThuoc[soLuongThuoc].nhap();
        soLuongThuoc++;
    }
    else
    {
        cout << "Danh sach da day!\n";
    }
}

void DanhMuc::themDichVu()
{
    if (soLuongDichVu < MAX_THUOC)
    {
        dsDichVu[soLuongDichVu].nhap();
        soLuongDichVu++;
    }
    else
    {
        cout << "Danh sach da day!\n";
    }
}

void DanhMuc::xemDanhSach()
{
    cout << "\n--- DANH MUC THUOC ---\n";
    for (int i = 0; i < soLuongThuoc; i++)
        dsThuoc[i].xuat();
    cout << "\n--- DANH MUC DICH VU ---\n";
    for (int i = 0; i < soLuongDichVu; i++)
        dsDichVu[i].xuat();
}
// ================== THUOC ==================
Thuoc::Thuoc() : tenThuoc(""), soLuong(0), gia(0) {}

Thuoc::Thuoc(string tenThuoc, int soLuong, double gia)
{
    this->tenThuoc = tenThuoc;
    setSoLuong(soLuong);
    setGia(gia);
}

Thuoc::~Thuoc() {}

// Getter
string Thuoc::getTenThuoc() const { return tenThuoc; }
int Thuoc::getSoLuong() const { return soLuong; }
double Thuoc::getGia() const { return gia; }

// Setter
void Thuoc::setTenThuoc(string t) { this->tenThuoc = t; }
void Thuoc::setSoLuong(int sl) { this->soLuong = (sl > 0) ? sl : 0; }
void Thuoc::setGia(double g) { this->gia = (g > 0) ? g : 0; }

// Loi #5: fix cin.ignore() thua - su dung getline(cin >> ws, ...)
// Loi #4: them validation so luong va gia phai > 0
void Thuoc::nhap()
{
    cout << "  Nhap ten thuoc (khong duoc de trong): ";
    do
    {
        getline(cin >> ws, tenThuoc);
        if (tenThuoc.empty())
            cout << "  [!] Ten thuoc khong duoc de trong! Nhap lai: ";
    } while (tenThuoc.empty());

    cout << "  Nhap so luong (> 0): ";
    while (!(cin >> soLuong) || soLuong <= 0)
    {
        cin.clear();
        cin.ignore();
        cout << "  [!] So luong phai la so nguyen duong! Nhap lai: ";
    }

    cout << "  Nhap don gia (VND, > 0): ";
    while (!(cin >> gia) || gia <= 0)
    {
        cin.clear();
        cin.ignore();
        cout << "  [!] Don gia phai lon hon 0! Nhap lai: ";
    }
    setGia(gia);
}

void Thuoc::xuat() const
{
    cout << "  Ten thuoc : " << tenThuoc << endl;
    cout << "  So luong  : " << soLuong << endl;
    cout << "  Don gia   : " << fixed << setprecision(0) << gia << " VND" << endl;
    cout << "  Thanh tien: " << fixed << setprecision(0) << soLuong * gia << " VND" << endl;
}
// ================== HOA DON ==================
// Loi #10: constructor mac dinh - maBN = 0 (chua xac dinh)
HoaDon::HoaDon() : maBN(0), soLuongThuoc(0), tongTien(0) {}

// Loi #10: constructor co ma benh nhan
HoaDon::HoaDon(int maBN) : maBN(maBN), soLuongThuoc(0), tongTien(0) {}

// Loi #2: Destructor KHONG in gi (tranh spam)
HoaDon::~HoaDon() {}

// Getter
int HoaDon::getMaBN() { return maBN; }
double HoaDon::getTongTien() { return tongTien; }

// Them thuoc
void HoaDon::themThuoc(Thuoc t)
{
    if (soLuongThuoc < MAX_THUOC)
        dsThuoc[soLuongThuoc++] = t;
    else
        cout << "[!] Hoa don da day (toi da " << MAX_THUOC << " loai thuoc)!\n";
}

// Tinh tong tien
void HoaDon::tinhTongTien()
{
    tongTien = 0;
    for (int i = 0; i < soLuongThuoc; i++)
        tongTien += dsThuoc[i].getSoLuong() * dsThuoc[i].getGia();
}

void HoaDon::nhap()
{
    cout << "--- Lap hoa don ---\n";
    int n;
    cout << "Nhap so luong loai thuoc / dich vu KCB can them: ";
    cin >> n;

    if (soLuongThuoc + n > MAX_THUOC)
    {
        cout << "Khong the them qua " << MAX_THUOC - soLuongThuoc << " loai thuoc nua.\n";
        n = MAX_THUOC - soLuongThuoc;
    }

    int start = soLuongThuoc;
    soLuongThuoc += n;
    for (int i = start; i < soLuongThuoc; i++)
    {
        cout << "\nThuoc / dich vu thu " << i + 1 << ":\n";
        dsThuoc[i].nhap();
    }
    tinhTongTien();
}

// Loi #10: xuat hien thi maBN
void HoaDon::xuat() const
{
    cout << "\n===== HOA DON =====\n";
    cout << "Benh nhan (Ma BN): " << (maBN > 0 ? to_string(maBN) : "Chua xac dinh") << "\n";
    if (soLuongThuoc == 0)
    {
        cout << "  (Khong co thuoc nao)\n";
    }
    else
    {
        for (int i = 0; i < soLuongThuoc; i++)
        {
            cout << "\n  Thuoc " << i + 1 << ":\n";
            dsThuoc[i].xuat();
        }
    }
    cout << "\nTong tien: " << fixed << setprecision(0) << tongTien << " VND\n";
}

// Nap chong <<
ostream &operator<<(ostream &out, const HoaDon &hd)
{
    out << "\n===== HOA DON =====\n";
    out << "Benh nhan (Ma BN): " << (hd.maBN > 0 ? to_string(hd.maBN) : "Chua xac dinh") << "\n";
    for (int i = 0; i < hd.soLuongThuoc; i++)
    {
        out << "\n  Thuoc " << i + 1 << ":\n";
        out << "  Ten thuoc : " << hd.dsThuoc[i].getTenThuoc() << endl;
        out << "  So luong  : " << hd.dsThuoc[i].getSoLuong() << endl;
        out << "  Don gia   : " << fixed << setprecision(0) << hd.dsThuoc[i].getGia() << " VND\n";
    }
    out << "\nTong tien: " << fixed << setprecision(0) << hd.tongTien << " VND\n";
    return out;
}

int BenhNhan::dem = 1;

BenhNhan::BenhNhan() : tenBenh(""), loaiBenhAn(""), chanDoan(""), maBacSiKCB(0), ngayVaoVien(""), ngayRaVien(""), soNgayDieuTri(0), maPhongLuuTru(""), soGiuongLuuTru(0), slHoaDon(0)
{
    this->maBN = dem++;
    this->ten = "";
    this->tuoi = 0;
    this->diaChi = "";
}

BenhNhan::BenhNhan(string ten, int tuoi, string diaChi) : tenBenh(""), loaiBenhAn(""), chanDoan(""), maBacSiKCB(0), ngayVaoVien(""), ngayRaVien(""), soNgayDieuTri(0), maPhongLuuTru(""), soGiuongLuuTru(0), slHoaDon(0)
{
    this->maBN = dem++;
    this->ten = ten;
    this->tuoi = tuoi;
    this->diaChi = diaChi;
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
            if (t > 0)
            {
                tuoi = t;
                validAge = true;
            }
            else
            {
                cout << "  [!] Tuoi phai lon hon 0!\n";
            }
        }
        catch (...)
        {
            cout << "  [!] Tuoi gi do sai roi! Vui long nhap so.\n";
        }
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
        cout << "  - Ma BS kham     : " << maBacSiKCB << "\n";
        cout << "  - Ngay kham/vao  : " << ngayVaoVien << "\n";
        cout << "  - Ten benh       : " << tenBenh << "\n";
        cout << "  - Chuan doan BS  : " << chanDoan << "\n";
        if (loaiBenhAn == "Noi tru (Nhap vien)" || loaiBenhAn == "Noi tru (Da xuat vien)")
        {
            if (maPhongLuuTru != "")
            {
                cout << "  - Vi tri giuong  : Phong " << maPhongLuuTru << " (Giuong " << soGiuongLuuTru << ")\n";
            }
            cout << "  - Ngay ra vien   : " << ngayRaVien << "\n";
            cout << "  - So ngay DB/DT  : " << soNgayDieuTri << " ngay\n";
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
// ----------------------------------------------------
// QUAN LY NGHIEP VU KCB (PATIENT-CENTRIC TRUC TIEP)
// ----------------------------------------------------
int BenhNhan::quyTrinhKhamBenh()
{
    cout << "\n--- LICH TRINH KHAM BENH CHO " << ten << " ---\n";
    cout << "Nhap ma bac si kham: ";
    cin >> maBacSiKCB;

    cout << "Nhap ngay kham (dd/mm/yyyy): ";
    getline(cin >> ws, ngayVaoVien);

    cout << "Nhap ten benh: ";
    getline(cin >> ws, tenBenh);

    cout << "Chuan doan cua bac si: ";
    getline(cin >> ws, chanDoan);

    cout << "\nYeu cau cua bac si muc do tinh trang benh:\n";
    cout << "  1. NANG => Phai NHAP VIEN dieu tri noi tru.\n";
    cout << "  2. NHE  => Ke thuoc, xuat hoa don va DI VE.\n";
    cout << "Chon yeu cau (1 hoac 2): ";
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
        cout << "[!] Tinh trang NANG: Yeu cau tiep tiep Noi Tru.\n";
        cout << "Yeu cau nhap so ngay dieu tri du kien (tu 1 ngay): ";
        cin >> soNgayDieuTri;
        ngayRaVien = "";
        cout << "[OK] Da lap ho so nhap vien. Dang chuyen yeu cau xep giuong...\n";
        return 1; // Tin hieu => Can xep giuong
    }
    else
    {
        loaiBenhAn = "Ngoai tru (Ke thuoc)";
        soNgayDieuTri = 0;
        ngayRaVien = "";
        cout << "[!] Tinh trang NHE: Ho so se chuyen sang ke thuoc va xuat Hoa Don.\n";
        themHoaDon(); // Truc tiep tien hanh xuat hoa don va di ve
        cout << "[OK] Benh nhan da duoc xuat hoa don va co electric the di ve.\n";
        return 0; // Khong can giuong
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
    cout << "Nhap ngay ra vien chinh thuc (dd/mm/yyyy): ";
    getline(cin >> ws, ngayRaVien);

    double donGia = (loaiPhongLuuTru == "VIP") ? 1000000 : 200000;

    loaiBenhAn = "Noi tru (Da xuat vien)";
    cout << "[OK] Da ghi nhan xuat vien. Chuyen sang he thong thanh toan vien phi...\n";
    themHoaDon(donGia, loaiPhongLuuTru);
    cout << "[OK] THU TUC XUAT VIEN HOAN TAT!\n";
}

void BenhNhan::themHoaDon(double donGiaGiuong, string loaiPhong)
{
    if (slHoaDon >= MAX_HS)
    {
        cout << "[!] Vuot qua so luong hoa don cho phep.\n";
        return;
    }
    cout << "\n--- Lap hoa don cho Benh nhan " << maBN << " ---\n";
    dsHoaDon[slHoaDon] = new HoaDon(maBN); // passing maBN

    if (donGiaGiuong > 0 && soNgayDieuTri > 0)
    {
        Thuoc phiGV("Phi luu tru giuong " + loaiPhong, soNgayDieuTri, donGiaGiuong);
        dsHoaDon[slHoaDon]->themThuoc(phiGV);
        cout << " [+] He thong da tu dong tich hop Phi luu tru Giang vao Hoa don!\n";
    }

    dsHoaDon[slHoaDon]->nhap();
    slHoaDon++;
    cout << "[OK] Hoa don thu " << slHoaDon << " lap xong!\n";
}

void BenhNhan::xemDanhSachHoaDon()
{
    cout << "\n--- Danh sach Hoa don cua Benh nhan " << ten << " (" << maBN << ") ---\n";
    if (slHoaDon == 0)
    {
        cout << "  (Chua co hoa don nao)\n";
        return;
    }
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
    {
        total += dsHoaDon[i]->getTongTien();
    }
    return total;
}

BenhVien::BenhVien() : slBN(0), slBS(0), slHD(0), slPB(0)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        dsBN[i] = nullptr;
        dsBS[i] = nullptr;
        dsHD[i] = nullptr;
        dsPB[i] = nullptr;
    }
    // Yeu cau tu dong nap san 20 phong Thuong (moi phong 6 giuong)
    for (int i = 1; i <= 20; i++)
    {
        string ma = "T" + to_string(i);
        if (i < 10)
            ma = "T0" + to_string(i);
        dsPB[slPB++] = new PhongBenh(ma, "Phong Thuong", "Thuong", 6);
    }
    // Yeu cau tu dong nap san 5 phong VIP (moi phong 1 giuong)
    for (int i = 1; i <= 5; i++)
    {
        string ma = "V0" + to_string(i);
        dsPB[slPB++] = new PhongBenh(ma, "Phong VIP", "VIP", 1);
    }
    // 20 bac si 
    dsBS[slBS++] = new BacSi("Nguyen Van An", "Noi khoa", "Tim mach", "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Nguyen Van Bao", "Ngoai khoa", "Phau thuat tong hop", "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Nguyen Van Vu", "San phu khoa", "Phu khoa", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Nguyen Thi Dung", "Than kinh", "Than kinh trung uong", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Tran Van Anh", "Nhi khoa", "Nhi khoa tong hop", "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Than Van Chien", "Tay xuong khop", "Chot tay", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Chu Van Tai", "Mat khoa", "Mat khoa", "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Bui Thi Ha", "Tai mui hong", "Tai mui hong", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Ngo Van Hung", "Rang ham mat", "Rang ham mat", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Cao Thi Huong", "Da lieu", "Da lieu", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Ngo Thi Trang", "Noi khoa", "Tieu hoa - Gan", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Dao Thi Linh", "Ngoai khoa", "Ung thu", "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Ha Van Khanh", "Phuong champs tac y", "Phau thuat tham my", "Tien si", "Truong khoa");
    dsBS[slBS++] = new BacSi("Ha Thi Ngoc", "Noi tang", "Mach mau - Khoi u", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("La Van Phuong", "Benh truyền nhiem", "Benh truyền nhiem", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Duong Thi Oanh", "Chuyen khoa Y tam ly", "Benh tam ly", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Doan Van Quang", "Noi khoa", "Tiet nieu - Huyet ap", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Vu Van Tuan", "Ngoai khoa", "Nhan khoa", "Thac si", "Bac si dieu tri");
    dsBS[slBS++] = new BacSi("Truong Van Sang", "San phu khoa", "Vo sinh", "Tien si", "Pho khoa");
    dsBS[slBS++] = new BacSi("Vo Thi Lan", "Nhi khoa", "Soi sinh", "Thac si", "Bac si dieu tri");
}

BenhVien::~BenhVien()
{
    for (int i = 0; i < slBN; i++)
        delete dsBN[i];
    for (int i = 0; i < slBS; i++)
        delete dsBS[i];
    for (int i = 0; i < slPB; i++)
        delete dsPB[i];
}

int BenhVien::nhapSoNguyen(const string &prompt)
{
    int val;
    while (true)
    {
        cout << prompt;
        cin >> val;
        if (!cin.fail())
            break;
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
    cout << "  --- I. QUAN LY DOI TUONG (Benh Nhan & Bac Si) ---\n";
    cout << "  1. Them benh nhan moi\n";
    cout << "  2. Xem danh sach benh nhan\n";
    cout << "  3. Tra cuu / Cap nhat / Xoa thong tin benh nhan\n\n";

    cout << "  4. Them thong tin bac si\n";
    cout << "  5. Danh sach doi ngu bac si\n";
    cout << "  6. Tra cuu / Cap nhat / Xoa thong tin bac si\n\n";

    cout << "  --- II. QUAN LY CO SO VAT CHAT ---\n";
    cout << "  7. Quan ly danh muc phong benh (Them/Sua/Xoa)\n";
    cout << "  8. So do phan bo va Hien trang giuong benh\n\n";

    cout << "  --- III. QUAN LY HE THONG & THONG KE ---\n";
    cout << "  9. Quan ly danh muc he thong (Thuoc & Dich vu)\n";
    cout << "  10. Bao cao tong doanh thu benh vien\n";
    cout << "  11. Sao luu he thong ra File (.txt)\n";
    cout << "  12. Khoi phuc du lieu he thong tu File\n";
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
    cout << "\n--- Nhap ho so benh nhan mong muon ---\n";
    dsBN[slBN] = new BenhNhan();
    dsBN[slBN]->nhap();
    cout << "[OK] Da them benh nhan. Ma BN = " << dsBN[slBN]->getMaBN() << "\n";
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
        cout << "[!] Benh vien chua co he thong phong luu tru. Khong the xep giuong!\n";
        return;
    }
    cout << "\n--- CHUYEN SANG BUOC XEP GIUONG BENH ---\n";
    cout << "Danh sach phong con giuong trong:\n";
    bool coPhongTrong = false;
    for (int i = 0; i < slPB; i++)
    {
        if (dsPB[i]->getSoGiuongThongTrong() > 0)
        {
            cout << "  - Phong " << dsPB[i]->getLoaiPhong() << " [" << dsPB[i]->getMaPhong() << "] : " << dsPB[i]->getTenPhong() << " | Con " << dsPB[i]->getSoGiuongThongTrong() << " giuong\n";
            coPhongTrong = true;
        }
    }
    if (!coPhongTrong)
    {
        cout << "[!] Benh vien hien DA HET GIUONG! Khong the xep giuong.\n";
        return;
    }

    string maChon;
    int viTriPhong = -1;
    while (true)
    {
        cout << "Nhap Ma Phong muon chon de nhan giuong: ";
        getline(cin >> ws, maChon);
        for (int i = 0; i < slPB; i++)
        {
            if (dsPB[i]->getMaPhong() == maChon && dsPB[i]->getSoGiuongThongTrong() > 0)
            {
                viTriPhong = i;
                break;
            }
        }
        if (viTriPhong != -1)
            break;
        cout << "  [!] Ma phong khong hop le hoac phong da day! Nhap lai.\n";
    }

    int giuongDuocCap = 0;
    if (dsPB[viTriPhong]->nhanGiuong(giuongDuocCap))
    {
        dsBN[indexBN]->setPhongLuuTru(dsPB[viTriPhong]->getMaPhong(), giuongDuocCap);
        cout << "======> XEP GIUONG THANH CONG <======\n";
        cout << "Benh nhan da duoc len Giuong so: " << giuongDuocCap << " | Tai Phong: " << dsPB[viTriPhong]->getMaPhong() << "\n";
    }
}

void BenhVien::xemDanhSachBenhNhan() const
{
    cout << "\n--- DANH SACH CHI TIET BENH NHAN (" << slBN << " nguoi) ---\n";
    if (slBN == 0)
    {
        cout << "  (Chua co benh nhan nao)\n";
        return;
    }
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
        cout << "[!] Chua co benh nhan nao de thao tac!\n";
        return;
    }

    int ma = nhapSoNguyen("\nNhap ma benh nhan can tim (Hoac 0 de thoat): ");
    if (ma == 0)
        return;

    int index = -1;
    for (int i = 0; i < slBN; i++)
    {
        if (dsBN[i]->getMaBN() == ma)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "[!] Khong tim thay benh nhan co ma " << ma << ".\n";
        return;
    }

    cout << "\n--- BAN DANG THAO TAC VOI BENH NHAN ---\n";
    dsBN[index]->xuat();

    cout << "\nThao tac ban muon thuc hien:\n";
    cout << "  1. Tra cuu Chi tiet Ho so Benh An / KCB\n";
    cout << "  2. Cap nhat Lai Thong Tin Ca Nhan\n";
    cout << "  3. XOA benh nhan khoi he thong benh vien\n";
    cout << "  4. Lam thu tuc XUAT VIEN & Thanh toan (Chi danh cho Noi tru)\n";
    cout << "  0. Huy bo thao tac\n";
    int choice = nhapSoNguyen("Lua chon cua ban: ");

    if (choice == 1)
    {
        dsBN[index]->xuat(); // Xuat da tich hop ho so KCB
    }
    else if (choice == 2)
    {
        cout << "[!] Moi ban cap nhat thong tin hien tai cho benh nhan:\n";
        dsBN[index]->nhap();
        cout << "[OK] Cap nhat thanh cong!\n";
    }
    else if (choice == 3)
    {
        string xacNhan;
        cout << "Ban co chac chan muon xoa TOAN BO DU LIEU NAY khoi benh vien (y/n)? ";
        cin >> xacNhan;
        if (xacNhan == "y" || xacNhan == "Y")
        {
            delete dsBN[index];
            for (int i = index; i < slBN - 1; i++)
                dsBN[i] = dsBN[i + 1];
            slBN--;
            cout << "[OK] Da xoa xoa sach se!\n";
        }
        else
        {
            cout << "[INFO] Da huy thao tac xoa.\n";
        }
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
                    dsBN[index]->setPhongLuuTru("", 0); // Xoa thong tin phong sau khi tra
                    break;
                }
            }
        }
        dsBN[index]->thuTucXuatVien(lp);
    }
}

void BenhVien::themThongTinBacSi()
{
    if (slBS >= MAX_SIZE)
    {
        cout << "[!] Danh sach bac si da day!\n";
        return;
    }
    cout << "\n--- Nhap thong tin bac si ---\n";
    dsBS[slBS] = new BacSi();
    dsBS[slBS]->nhap();
    cout << "[OK] Da them bac si. Ma BS = " << dsBS[slBS]->getMaBS() << "\n";
    slBS++;
}

void BenhVien::xemDanhSachBacSi() const
{
    cout << "\n--- DANH SACH BAC SI (" << slBS << " nguoi) ---\n";
    if (slBS == 0)
    {
        cout << "  (Chua co bac si nao)\n";
        return;
    }
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
        cout << "[!] Chua co bac si nao de thao tac!\n";
        return;
    }

    int ma = nhapSoNguyen("\nNhap ma bac si can tim (Hoac 0 de thoat): ");
    if (ma == 0)
        return;
    int index = -1;
    for (int i = 0; i < slBS; i++)
    {
        if (dsBS[i]->getMaBS() == ma)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "[!] Khong tim thay. \n";
        return;
    }

    cout << "\n--- THONG TIN BAC SI TIM THAY ---\n";
    dsBS[index]->xuat();
    cout << "\nThao tac ban muon thuc hien:\n  1. Cap nhat thong tin\n  2. Xoa bac si\n  0. Huy\n";
    int choice = nhapSoNguyen("Lua chon: ");

    if (choice == 1)
    {
        dsBS[index]->nhap();
        cout << "[OK] Da cap nhat.\n";
    }
    else if (choice == 2)
    {
        delete dsBS[index];
        for (int i = index; i < slBS - 1; i++)
            dsBS[i] = dsBS[i + 1];
        slBS--;
        cout << "[OK] Da xoa!\n";
    }
}

void BenhVien::quanLyPhongBenh()
{
    cout << "\n--- II. QUAN LY DANH MUC PHONG BENH ---\n";
    cout << "1. Them phong benh moi\n2. Sua thong tin phong benh\n3. Xoa phong benh khoi he thong\n0. Huy/Quay lai\n";
    int choice = nhapSoNguyen("Lua chon chuc nang: ");

    if (choice == 1)
    {
        if (slPB >= MAX_SIZE)
        {
            cout << "[!] Danh sach phong day!\n";
            return;
        }
        dsPB[slPB] = new PhongBenh();
        dsPB[slPB]->nhap();
        slPB++;
        cout << "[OK] Them phong thanh cong.\n";
    }
    else if (choice == 2 || choice == 3)
    {
        if (slPB == 0)
        {
            cout << "Chua co phong de thao tac!\n";
            return;
        }
        string ma;
        cout << "Nhap ma phong: ";
        getline(cin >> ws, ma);
        int index = -1;
        for (int i = 0; i < slPB; i++)
        {
            if (dsPB[i]->getMaPhong() == ma)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Khong tim thay phong!\n";
            return;
        }

        if (choice == 2)
        {
            dsPB[index]->nhap();
            cout << "[OK] Da sua.\n";
        }
        else
        {
            delete dsPB[index];
            for (int i = index; i < slPB - 1; i++)
                dsPB[i] = dsPB[i + 1];
            slPB--;
            cout << "[OK] Da xoa!\n";
        }
    }
}

void BenhVien::soDoGiuongBenh() const
{
    cout << "\n--- SO DO PHAN BO VA HIEN TRANG GIUONG BENH ---\n";
    if (slPB == 0)
    {
        cout << "  (Chua co co so vat chat nao)\n";
        return;
    }
    for (int i = 0; i < slPB; i++)
    {
        cout << "  [" << i + 1 << "] ";
        dsPB[i]->xuat();
    }
}

void BenhVien::quanLyDanhMuc() { cout << "[INFO] Dang phat trien (Phan He Thong)... \n"; }

void BenhVien::baoCaoThongKe() const
{
    cout << "\n============================================\n";
    cout << "   BAO CAO DOANH THU TOAN HE THONG\n";
    cout << "============================================\n";
    if (slBN == 0)
    {
        cout << "  (Chua co du lieu luu luong benh nhan)\n";
        return;
    }
    double tongToanVien = 0;
    int soLuongCoTraPhe = 0;
    for (int i = 0; i < slBN; i++)
    {
        double phi = dsBN[i]->tinhTongVienPhi();
        if (phi > 0)
        {
            cout << " - BN: " << dsBN[i]->getTen() << "     | Phat sinh chi phi: " << phi << "\n";
            tongToanVien += phi;
            soLuongCoTraPhe++;
        }
    }
    cout << "--------------------------------------------\n";
    cout << " > Tong luot benh nhan phat sinh phi: " << soLuongCoTraPhe << "\n";
    cout << " > TONG DOANH THU HOP LE: " << tongToanVien << " VNĐ\n";
    cout << "============================================\n";
}

void BenhVien::saoLuuDuLieu() { cout << "[INFO] Dang phat trien (File I/O)...\n"; }
void BenhVien::khoiPhucDuLieu() { cout << "[INFO] Dang phat trien (File I/O)...\n"; }

void BenhVien::chay()
{
    int choice;
    do
    {
        hienThiMenu();
        choice = nhapSoNguyen("Lua chon cua ban (0-12): ");
        switch (choice)
        {
        case 1:
            themHoSoBenhNhan();
            break;
        case 2:
            xemDanhSachBenhNhan();
            break;
        case 3:
            thaoTacBenhNhan();
            break;
        case 4:
            themThongTinBacSi();
            break;
        case 5:
            xemDanhSachBacSi();
            break;
        case 6:
            thaoTacBacSi();
            break;
        case 7:
            quanLyPhongBenh();
            break;
        case 8:
            soDoGiuongBenh();
            break;
        case 9:
            quanLyDanhMuc();
            break;
        case 10:
            baoCaoThongKe();
            break;
        case 11:
            saoLuuDuLieu();
            break;
        case 12:
            khoiPhucDuLieu();
            break;
        case 0:
            cout << "\nDong he thong. Tam biet!\n";
            break;
        default:
            cout << "[!] Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}
// ====================================================
// main.cpp - Rat gon: chi tao doi tuong va chay
// Toan bo logic nam trong class BenhVien (OOP dung nghia)
// ====================================================
int main()
{
    BenhVien benhVien;
    benhVien.chay();
    return 0;
}