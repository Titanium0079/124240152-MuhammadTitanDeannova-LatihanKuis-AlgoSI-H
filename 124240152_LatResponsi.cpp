#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype> // Library untuk fungsi tolower
#include <iomanip>
using namespace std;

//Struct data untuk simpan informasi buku
struct data_buku {
    char ID[20]; 
    char judul[100];  
    char penulis[100]; 
    int stok;  
};

data_buku buku[100]; // Array untuk menyimpan daftar buku
int jumlah_buku = 0;  // Jumlah buku dalam database

// Fungsi untuk mengubah string menjadi huruf kecil
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Fungsi untuk menyimpan daftar buku ke dalam file "data.dat"
void simpan_ke_file() {
    ofstream file("data.dat"); // Mode teks
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }

  // Menulis setiap buku ke dalam file
    for (int i = 0; i < jumlah_buku; i++) {
        file << buku[i].ID << endl;
        file << buku[i].judul << endl;
        file << buku[i].penulis << endl;
        file << buku[i].stok << endl;
    }
    file.close();
}

// Fungsi untuk membaca daftar buku dari file "data.dat"
void baca_dari_file() {
    ifstream file("data.dat"); // Mode teks
    if (!file) {
        cout << "File tidak ditemukan, memulai database baru.\n";
        return;
    }

    jumlah_buku = 0;
    while (file >> buku[jumlah_buku].ID) {
        file.ignore();
        file.getline(buku[jumlah_buku].judul, 100);
        file.getline(buku[jumlah_buku].penulis, 100);
        file >> buku[jumlah_buku].stok;
        file.ignore();
        jumlah_buku++;
    }
    file.close();
}

// Fungsi untuk mencari buku berdasarkan judul
void cari_buku() {
    bool found = false;
    char cari_nama[100];
    cout << "Masukkan kata kunci dari judul buku yang dicari: ";
    cin.ignore();
    cin.getline(cari_nama, 100);
    toLowerCase(cari_nama);

    cout << "Hasil Pencarian:\n";
    for (int i = 0; i < jumlah_buku; i++) {
        char temp[100];
        strcpy(temp, buku[i].judul);
        toLowerCase(temp);

        if (strstr(temp, cari_nama)) {
            cout << "-----------------------------------\n";
            cout << "ID      : " << buku[i].ID << endl;
            cout << "Judul   : " << buku[i].judul << endl;
            cout << "Penulis : " << buku[i].penulis << endl;
            cout << "Stok    : " << buku[i].stok << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Buku tidak ditemukan dalam database.\n";
    }
}

// Fungsi untuk menambahkan data buku baru
void tambah_data_buku() {
    cout << "\n===== Tambah data buku =====\n";
    cout << "ID buku: ";
    cin >> buku[jumlah_buku].ID;
    cin.ignore();
    cout << "Judul buku: ";
    cin.getline(buku[jumlah_buku].judul, 100);
    cout << "Penulis: ";
    cin.getline(buku[jumlah_buku].penulis, 100);
    cout << "Stok: ";
    cin >> buku[jumlah_buku].stok;
    jumlah_buku++;
    simpan_ke_file();
    cout << "\nBuku berhasil ditambahkan!\n";
}

// Fungsi untuk mengurutkan buku berdasarkan ID menggunakan Bubble Sort
void sort_data_buku() {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < jumlah_buku - 1; i++) {
            if (strcmp(buku[i].ID, buku[i + 1].ID) > 0) {
                swap(buku[i], buku[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

// Fungsi untuk menghapus data buku berdasarkan ID
void hapus_data_buku() {
    char ID_hapus[20];
    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> ID_hapus;

    int index = -1;
    for (int i = 0; i < jumlah_buku; i++) {
        if (strcmp(ID_hapus, buku[i].ID) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Buku tidak ditemukan!\n";
        return;
    }

    for (int i = index; i < jumlah_buku - 1; i++) {
        buku[i] = buku[i + 1];
    }
    jumlah_buku--;

    simpan_ke_file();
    cout << "Buku berhasil dihapus!\n";
}

// Fungsi untuk menampilkan daftar buku
void tampilkan_data_buku() {
    cout << "\n===== Daftar Buku =====\n";
    if (jumlah_buku == 0) {
        cout << "Tidak ada data buku yang tersimpan.\n";
        return;
    }
    for (int i = 0; i < jumlah_buku; i++) {
        cout << "-----------------------------------\n";
        cout << "ID      : " << buku[i].ID << endl;
        cout << "Judul   : " << buku[i].judul << endl;
        cout << "Penulis : " << buku[i].penulis << endl;
        cout << "Stok    : " << buku[i].stok << endl;
    }
}

// Fungsi menu utama
void menu(const string &username) {
    int pilih;
    do {
        cout << "\n===== SELAMAT DATANG, " << username << "! =====\n";
        cout << "Jumlah buku saat ini: " << jumlah_buku << " buku\n";
        cout << "1. Tambah data buku\n";
        cout << "2. Tampilkan daftar buku\n";
        cout << "3. Cari buku\n";
        cout << "4. Hapus buku\n";
        cout << "5. Keluar\n";
        cout << ">> Pilih menu: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: tambah_data_buku(); break;
            case 2: sort_data_buku(); tampilkan_data_buku(); break;
            case 3: cari_buku(); break;
            case 4: hapus_data_buku(); break;
            case 5: cout << "Terima kasih telah menggunakan sistem perpustakaan!\n"; break;
            default: cout << "Pilihan tidak valid, coba lagi!\n";
        }
    } while (pilih != 5);
}

int main() {
    baca_dari_file();
    const string correctUsername = "titan";
    const string correctPassword = "152";
    string username, password;

    while (true) {
        cout << "\nLOGIN KE DATABASE PERPUSTAKAAN INFORMATIKA\n";
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (username == correctUsername && password == correctPassword) {
            break;
        } else {
            cout << "\nUsername atau password salah.\n";
        }
    }

    menu(username);
    return 0;
}
