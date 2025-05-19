#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// Struktur data untuk menyimpan informasi siswa
struct Siswa {
    string nama;
    string npm;
    vector<string> kursusDiambil; // Menyimpan kursus yang diambil siswa
    Siswa* next; // Pointer untuk linked list
};

// Struktur data untuk menyimpan informasi kursus
struct Kursus {
    string judul;
    string kategori;
    int durasi; // dalam menit
    Siswa* siswaTerdaftar; // Pointer ke siswa yang mengambil kursus ini
};

class SmartEduSystem {
private:
    // Array untuk menyimpan kursus
    Kursus daftarKursus[7] = {
        {"Pendidikan Pancasila", "Sosial", 90, nullptr},
        {"Kalkulus", "Matematika", 90, nullptr},
        {"Struktur Data dan Algoritma", "Teknologi", 150, nullptr},
        {"Sistem Basis Data", "Teknologi", 180, nullptr},
        {"Statistika dan Probabilitas", "Matematika", 120, nullptr},
        {"Pemrograman Web I", "Teknologi", 90, nullptr},
        {"Estetika dan Humanisme", "Sosial", 90, nullptr},
    };
    
    queue<string> antrianKonsultasi; // Queue untuk antrian konsultasi
    
    stack<string> riwayatPembelajaran; // Stack untuk riwayat pembelajaran
    
    Siswa* headSiswa; // Head dari linked list siswa
    
public:
    SmartEduSystem() {
        headSiswa = nullptr;
    }
    
    // Method untuk menambahkan siswa ke linked list
    void tambahSiswa(string nama, string npm) {
        Siswa* siswaBaru = new Siswa();
        siswaBaru->nama = nama;
        siswaBaru->npm = npm;
        siswaBaru->next = headSiswa;
        headSiswa = siswaBaru;
        cout << "Siswa " << nama << " berhasil ditambahkan.\n";
    }

    // Method untuk menampilkan semua siswa dalam linked list
    void tampilkanSemuaSiswa() {
        if (headSiswa == nullptr) {
            cout << "Belum ada siswa terdaftar.\n";
            return;
        }
        
        cout << "\nDaftar Siswa Terdaftar:\n";
        Siswa* current = headSiswa;
        while (current != nullptr) {
            cout << "Nama: " << current->nama << ", NPM: " << current->npm << "\n";
            if (!current->kursusDiambil.empty()) {
                cout << "  Kursus yang diambil: ";
                for (const auto& kursus : current->kursusDiambil) {
                    cout << kursus << ", ";
                }
                cout << "\n";
            }
            current = current->next;
        }
    }

    // Method untuk menampilkan kursus berdasarkan kategori
    void tampilkanKursusKategori(string kategori) {
        cout << "\nDaftar Kursus Berdasarkan Kategori '" << kategori << "':\n";
        bool ditemukan = false;
        for (int i = 0; i < 7; i++) {
            if (daftarKursus[i].kategori == kategori) {
                cout << "- " << daftarKursus[i].judul 
                     << " (" << daftarKursus[i].durasi << " menit)\n";
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Tidak ada kursus dalam kategori '" << kategori << "'.\n";
        }
    }

    // Method untuk menambahkan permintaan konsultasi ke queue
    void tambahPermintaanKonsultasi(string nama) {
        antrianKonsultasi.push(nama);
        cout << "Permintaan konsultasi untuk " << nama << " telah ditambahkan.\n";
    }

    // Method untuk memproses konsultasi dari queue
    void prosesKonsultasi() {
        if (antrianKonsultasi.empty()) {
            cout << "Tidak ada antrian konsultasi.\n";
        } else {
            string nama = antrianKonsultasi.front();
            antrianKonsultasi.pop();
            cout << "Konsultasi untuk " << nama << " sedang diproses.\n";
        }
    }

    // Method untuk menampilkan antrian konsultasi
    void tampilkanAntrianKonsultasi() {
        if (antrianKonsultasi.empty()) {
            cout << "Antrian konsultasi kosong.\n";
            return;
        }
        
        cout << "\nDaftar Antrian Konsultasi:\n";
        queue<string> temp = antrianKonsultasi;
        int posisi = 1;
        while (!temp.empty()) {
            cout << posisi++ << ". " << temp.front() << "\n";
            temp.pop();
        }
    }

    // Method untuk menampilkan riwayat pembelajaran dari stack
    void tampilkanRiwayatPembelajaran() {
        if (riwayatPembelajaran.empty()) {
            cout << "Belum ada riwayat pembelajaran.\n";
        } else {
            cout << "\nRiwayat Pembelajaran Terakhir (terbaru ke terlama):\n";
            stack<string> temp = riwayatPembelajaran;
            int counter = 1;
            while (!temp.empty()) {
                cout << counter++ << ". " << temp.top() << "\n";
                temp.pop();
            }
        }
    }
    
    // Method untuk menambahkan riwayat pembelajaran ke stack
    void tambahRiwayatPembelajaran(string namaKursus) {
        riwayatPembelajaran.push(namaKursus);
        cout << "Kursus '" << namaKursus << "' telah ditambahkan ke riwayat.\n";
    }
    
    // Method untuk mendaftarkan siswa ke kursus tertentu
    void daftarkanSiswaKeKursus(string npm, string namaKursus) {
        // Cari siswa berdasarkan NPM
        Siswa* siswa = headSiswa;
        while (siswa != nullptr && siswa->npm != npm) {
            siswa = siswa->next;
        }
        
        if (siswa == nullptr) {
            cout << "Siswa dengan NPM " << npm << " tidak ditemukan.\n";
            return;
        }
        
        // Cari kursus
        bool kursusDitemukan = false;
        for (int i = 0; i < 7; i++) {
            if (daftarKursus[i].judul == namaKursus) {
                kursusDitemukan = true;
                // Tambahkan ke riwayat siswa
                siswa->kursusDiambil.push_back(namaKursus);
                // Tambahkan ke stack riwayat sistem
                riwayatPembelajaran.push(namaKursus + " oleh " + siswa->nama);
                cout << siswa->nama << " berhasil didaftarkan ke kursus " << namaKursus << ".\n";
                break;
            }
        }
        
        if (!kursusDitemukan) {
            cout << "Kursus '" << namaKursus << "' tidak ditemukan.\n";
        }
    }
    
    // Method untuk menampilkan menu utama
    void tampilkanMenu() {
        int pilihan;
        string input, input2;
        string nama, npm;
        
        do {
            cout << "\n=== SMARTEDU SYSTEM ===\n";
            cout << "1. Tampilkan Kursus Berdasarkan Kategori\n";
            cout << "2. Tambah Permintaan Konsultasi\n";
            cout << "3. Proses Konsultasi\n";
            cout << "4. Tampilkan Antrian Konsultasi\n";
            cout << "5. Tambah Riwayat Pembelajaran\n";
            cout << "6. Tampilkan Riwayat Pembelajaran\n";
            cout << "7. Tambah Siswa Baru\n";
            cout << "8. Tampilkan Semua Siswa\n";
            cout << "9. Daftarkan Siswa ke Kursus\n";
            cout << "0. Keluar\n";
            cout << "Pilihan: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    cout << "Masukkan kategori (Teknologi/Matematika/Sosial): ";
                    cin >> input;
                    tampilkanKursusKategori(input);
                    break;
                case 2:
                    cout << "Masukkan nama siswa: ";
                    cin.ignore();
                    getline(cin, input);
                    tambahPermintaanKonsultasi(input);
                    break;
                case 3:
                    prosesKonsultasi();
                    break;
                case 4:
                    tampilkanAntrianKonsultasi();
                    break;
                case 5:
                    cout << "Masukkan nama kursus: ";
                    cin.ignore();
                    getline(cin, input);
                    tambahRiwayatPembelajaran(input);
                    break;
                case 6:
                    tampilkanRiwayatPembelajaran();
                    break;
                case 7:
                    cout << "Masukkan nama siswa: ";
                    cin.ignore();
                    getline(cin, nama);
                    cout << "Masukkan NPM siswa: ";
                    getline(cin, npm);
                    tambahSiswa(nama, npm);
                    break;
                case 8:
                    tampilkanSemuaSiswa();
                    break;
                case 9:
                    cout << "Masukkan NPM siswa: ";
                    cin.ignore();
                    getline(cin, npm);
                    cout << "Masukkan nama kursus: ";
                    getline(cin, input);
                    daftarkanSiswaKeKursus(npm, input);
                    break;
                case 0:
                    cout << "Keluar dari sistem.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 0);
    }
};

int main() {
    SmartEduSystem smartEdu;
    smartEdu.tampilkanMenu();
    return 0;
}