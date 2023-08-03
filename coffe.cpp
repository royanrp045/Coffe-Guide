#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#define MAX 10
using namespace std;
int jmlMenu;
void header();
void footer();
void menuu();
// FUNGSI SORTING
void tukar(string &a, string &b)
{
  string temp = a;
  a = b;
  b = temp;
}
void selSort(string *arr, int length)
{
  int x;
  for (int i = 0; i < length - 1; i++)
  {
    x = i;
    for (int j = i + 1; j < length; j++)
    {
      // ascending
      if (arr[j] < arr[x])
        x = j;
    }
    tukar(arr[i], arr[x]);
  }
}
void tampilSort(string *arr, int length)
{
  for (int i = 0; i < length; i++)
    cout << arr[i] << " | ";
}
// struct
struct st
{
  string data[MAX];
  string label;
  int harga_beli, harga_jual, jml_beli, jml_jual;
  int awal, akhir;
  string nama_konsumen;
  int nomor_meja;
} menu[MAX];
// queue
bool isFull(int x)
{
  if (menu[x].awal == 0 && menu[x].akhir == MAX - 1)
  {
    return true;
  }
  return false;
}
bool isEmpty(int x)
{
  if (menu[x].akhir == -1)
  {
    return true;
  }
  return false;
}
void inQueue(int x, string value)
{
  if (isFull(x))
  {
    cout << "Menu untuk \"" << menu[x].label << "\" Penuh";
  }
  else
  {
    if (menu[x].awal == -1)
      menu[x].awal = 0;
    menu[x].akhir++;
    menu[x].data[menu[x].akhir] = value;
  }
}
void deQueue(int x)
{
  if (isEmpty(x))
  {
    cout << "Menu untuk \"" << menu[x].label << "\" Kosong" << endl;
  }
  else
  {
    menu[x].data[menu[x].awal] = "";
    menu[x].awal++;
    if (menu[x].awal > menu[x].akhir)
    {
      menu[x].awal = -1;
      menu[x].akhir = -1;
    }
  }
}
void tampilMenu(int x)
{
  if (!isEmpty(x))
  {
    int stok = 0;
    cout << "Barang dalam menu \"" << menu[x].label << "\":\n";
    for (int i = menu[x].awal; i <= menu[x].akhir; i++)
    {
      stok++;
    }
    cout << "Stok Menu \"" << menu[x].label << "\" = " << stok << endl;
  }
  else
  {
    cout << "Stok Menu \"" << menu[x].label << "\" = kosong" << endl;
  }
}
//--------------------------------
// Fungsi SEARCHING
int SequentialSearch(string cari, int lengh)
{
  for (int i = 0; i < lengh; i++)
  {
    if (cari == menu[i].label)
    {
      if (!isEmpty(i))
      {
        return i;
      }
    }
  }
  return -1;
}
// inisialisasi
void init()
{
  header();
  cout << "Masukan jumlah Menu (MAX=10) = ";
  cin >> jmlMenu;
  while (jmlMenu > 10)
  {
    cout << "Masukkan jumlah menu (MAX=10) = ";
    cin >> jmlMenu;
  }
  cout << endl;
  for (int i = 0; i < jmlMenu; i++)
  {
    menu[i].awal = -1;
    menu[i].akhir = -1;
    cout << "Masukan Label untuk Menu " << i + 1 << " = ";
    cin >> menu[i].label;
    cout << "Masukan harga beli per item untuk Menu " << i + 1 << " = ";
    cin >> menu[i].harga_beli;
    cout << "masukan harga jual per item untuk menu " << i + 1 << " = ";
    cin >> menu[i].harga_jual;
    menu[i].jml_beli = 0;
    menu[i].jml_jual = 0;
    cout << "\n";
  }
  footer();
}
void masuk()
{
  header();
  string s;
  cout << "Masukkan barang =\n\t";
  cin.ignore();
  getline(cin, s);
  vector<string> tokens;
  stringstream check1(s);
  string intermediate;
  while (getline(check1, intermediate, ' '))
  {
    tokens.push_back(intermediate);
  }
  string barang[tokens.size()];
  int jumlah[tokens.size()];
  cout << endl;
  cout << "Masukkan jumlah barang untuk setiap item:\n";
  for (int i = 0; i < tokens.size(); i++)
  {
    barang[i] = tokens[i];
    cout << "Jumlah " << barang[i] << " = ";
    cin >> jumlah[i];
  }
  cout << endl;
  cout << "Melakukan proses Sorting barang....." << endl;
  selSort(barang, tokens.size());
  cout << "Barang setelah disortir = " << endl;
  cout << "\t";
  tampilSort(barang, tokens.size());
  cout << "\n\nBarang akan dimasukan ke Menu....." << endl;
  for (int i = 0; i < tokens.size(); i++)
  {
    for (int j = 0; j < jmlMenu; j++)
    {
      if (barang[i] == menu[j].label)
      {
        for (int k = 0; k < jumlah[i]; k++)
        {
          inQueue(j, barang[i]);
          menu[j].jml_beli++;
        }
      }
    }
  }
  cout << "Barang telah dimasukan";
  footer();
}
void keluar()
{
  header();
  cout << "Daftar Menu:\n";
  cout << char(220);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "| No. | Menu | Stok | Harga Jual |\n";
  cout << char(220);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  for (int i = 0; i < jmlMenu; i++)
  {
    cout << "| " << setw(4) << i + 1 << " | " << setw(14) << menu[i].label << " | " << setw(5) << menu[i].akhir - menu[i].awal + 1 << " | " << setw(12) << menu[i].harga_jual << " |\n";
  }
  cout << char(220);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << endl;
  string namaKonsumen;
  int nomorMeja;
  cout << "Masukkan nama konsumen: ";
  cin.ignore();
  getline(cin, namaKonsumen);
  cout << "Masukkan nomor meja: ";
  cin >> nomorMeja;
  int numItems;
  cout << "Masukkan jumlah barang yang akan dijual: ";
  cin >> numItems;
  string barang[numItems];
  int jumlah[numItems];
  cout << "Masukkan nomor menu dan jumlah barang yang akan dijual:\n";
  for (int i = 0; i < numItems; i++)
  {
    int menuNum;
    cout << "Menu " << i + 1 << ": ";
    cin >> menuNum;
    cout << "Jumlah " << menu[menuNum - 1].label << ": ";
    cin >> jumlah[i];
    barang[i] = menu[menuNum - 1].label;
  }
  cout << endl;
  cout << "Barang akan dikeluarkan dari Menu....." << endl;
  for (int i = 0; i < numItems; i++)
  {
    bool found = false;
    for (int j = 0; j < jmlMenu; j++)
    {
      if (barang[i] == menu[j].label)
      {
        found = true;
        for (int k = 0; k < jumlah[i]; k++)
        {
          if (!isEmpty(j))
          {
            deQueue(j);
            menu[j].jml_jual++;
          }
          else
          {
            cout << "Menu \"" << menu[j].label << "\" Ko\ song" << endl;
            break;
          }
        }
        break;
      }
    }
    if (!found)
    {
      cout << "Barang \"" << barang[i] << "\" tidak ditemukan di Menu" << endl;
    }
  }
  cout << "Barang telah dijual" << endl;
  // Menyimpan nama konsumen dan nomor meja pada data penjualan
  menu[0].nama_konsumen = namaKonsumen;
  menu[0].nomor_meja = nomorMeja;
  cout << endl;
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "Data Transaksi:\n";
  cout << "Nama Pelanggan: " << menu[0].nama_konsumen << endl;
  cout << "Nomor Meja: " << menu[0].nomor_meja << endl;
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "Rincian Pembelian:\n";
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "| Menu | Jumlah | Harga | Total |\n";
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  int total = 0;
  for (int i = 0; i < numItems; i++)
  {
    for (int j = 0; j < jmlMenu; j++)
    {
      if (barang[i] == menu[j].label)
      {
        int harga = menu[j].harga_jual;
        int subtotal = harga * jumlah[i];
        cout << "| " << setw(16) << left << menu[j].label;
        cout << "| " << setw(10) << right << jumlah[i];
        cout << "| " << setw(10) << right << harga;
        cout << "| " << setw(10) << right << subtotal << " |\n";
        total += subtotal;
        break;
      }
    }
  }
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "| Total Pembayaran | | | " << setw(10) << right << total << " |\n";
  cout << char(220);
  for (int i = 0; i < 56; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  footer();
}
void cekStok()
{
  header();
  for (int i = 0; i < jmlMenu; i++)
  {
    tampilMenu(i);
    cout << endl;
  }
  footer();
}
void cekHasil()
{
  header();
  int modal = 0, jual = 0, untung = 0, bersih = 0;
  cout << "Modal\n";
  cout << "+------------------+------------+------------+------------+\n";
  cout << "| Menu | Jumlah | Harga | Total |\n";
  cout << "+------------------+------------+------------+------------+\n";
  for (int i = 0; i < jmlMenu; i++)
  {
    int m = menu[i].jml_beli * menu[i].harga_beli;
    modal += m;
    cout << "| " << setw(16) << left << menu[i].label;
    cout << "| " << setw(10) << right << menu[i].jml_beli;
    cout << "| " << setw(10) << right << menu[i].harga_beli;
    cout << "| " << setw(10) << right << m << " |\n";
  }
  cout << "+------------------+------------+------------+------------+\n";
  cout << "| Total Modal | " << setw(10) << right << modal << " | | |\n";
  cout << "+------------------+------------+------------+------------+\n";
  cout << endl;
  cout << "Penjualan\n";
  cout << "+------------------+------------+------------+------------+\n";
  cout << "| Menu | Jumlah | Harga | Total |\n";
  cout << "+------------------+------------+------------+------------+\n";
  for (int i = 0; i < jmlMenu; i++)
  {
    int t = menu[i].jml_jual * menu[i].harga_jual;
    int r = menu[i].jml_jual * menu[i].harga_beli;
    jual += t;
    bersih += r;
    cout << "| " << setw(16) << left << menu[i].label;
    cout << "| " << setw(10) << right << menu[i].jml_jual;
    cout << "| " << setw(10) << right << menu[i].harga_jual;
    cout << "| " << setw(10) << right << t << " |\n";
  }
  cout << "+------------------+------------+------------+------------+\n";
  cout << "| Total Penjualan | " << setw(10) << right << jual << " | | |\n";
  cout << "+------------------+------------+------------+------------+\n";
  untung = bersih;
  cout << endl;
  cout << "Total Pendapatan = " << untung;
  footer();
}
void header()
{
  // fungsi header ini digunakan untuk mempercantik tampilan aplikasi
  system("cls");
  cout << char(220);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(220)
       << endl;
  cout << char(219) << " " << char(219) << endl;
  cout << char(219) << " COFFE GUIDE " << char(219) << endl;
  cout << char(219) << " " << char(219) << endl;
  cout << char(219) << " OPEN 8 AM - 10 PM " << char(219) << endl;
  cout << char(219) << " " << char(219) << endl;
  cout << char(219) << " YOGYAKARTA " << char(219) << endl;
  cout << char(219);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(219)
       << endl;
}
void footer()
{
  // fungsi ini merupakan footer
  // yang digunakan untuk kembali ke menu utama
  // setelah melakukan fungsi lainnya
  cout << "\n\n";
  cout << "Tekan Spasi Untuk kembali...";
  getch();
  menuu();
}
void menuu()
{
  // fungsi ini merupakan menu utama dari program
  header();
  cout << "Pilih Menuu\n";
  cout << "\t1. Inisialisasi Menu\n";
  cout << "\t2. Masukkan barang\n";
  cout << "\t3. Pesanan\n";
  cout << "\t4. Cek stok\n";
  cout << "\t5. Cek hasil penjualan\n";
  cout << "\t6. Keluar\n";
  cout << char(220);
  for (int i = 0; i < 45; i++)
  {
    cout << char(220);
  }
  cout << char(220) << endl;
  cout << "Pilih Menuu (1-6) = ";
  int pilihan = 0;
  while ((pilihan < 1) || (pilihan > 6))
  {
    // akan terus meminta input yang diperlukan
    cin >> pilihan;
  }
  switch (pilihan)
  {
  case 1:
    init();
    break;
  case 2:
    masuk();
    break;
  case 3:
    keluar();
    break;
  case 4:
    cekStok();
    break;
  case 5:
    cekHasil();
    break;
  case 6:
    exit;
  }
}
main()
{
  // fungsi main atau fungsi utama program ini
  // hanya digunakan untuk memangkil fungsi menuu()
  menuu();
}
// end of program