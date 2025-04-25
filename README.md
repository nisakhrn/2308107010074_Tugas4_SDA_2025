Khairun Nisa
2308107010074

# Dokumentasi Program Benchmark Algoritma Sorting
Kode ini merupakan program benchmark untuk berbagai algoritma sorting yang menguji efisiensi dalam hal waktu eksekusi dan penggunaan memori. Program ini mampu melakukan benchmark pada data angka (integer) dan kata (string) dengan berbagai ukuran data.

## Struktur Program
Program terdiri dari dua file utama:

1. **sorts.h**: Berisi implementasi berbagai algoritma sorting untuk data integer, termasuk:
   - Bubble Sort
   - Insertion Sort
   - Selection Sort
   - Shell Sort
   - Merge Sort
   - Quick Sort

2. **main.c**: Berisi program utama yang menjalankan benchmark, termasuk:
   - Implementasi algoritma sorting untuk string
   - Fungsi untuk memuat data dari file
   - Fungsi benchmark untuk mengukur performa
   - Sistem menu interaktif

## Fitur Program
- Benchmark algoritma sorting pada dua jenis data:
  - Data angka (integer)
  - Data kata (string)
- Dukungan berbagai ukuran data: 10.000, 50.000, 100.000, 250.000, 500.000, 1.000.000, 1.500.000, dan 2.000.000 elemen
- Pengukuran waktu eksekusi dan penggunaan memori
- Tampilan hasil dalam bentuk tabel
- Sistem menu yang user-friendly

## Algoritma Sorting yang Diimplementasi
1. **Bubble Sort**: Membandingkan elemen bersebelahan dan menukar jika urutan salah
2. **Insertion Sort**: Menyisipkan elemen ke posisi yang benar dalam bagian array yang telah diurutkan
3. **Selection Sort**: Mencari nilai terkecil dan menukarnya ke posisi paling awal
4. **Shell Sort**: Versi yang lebih efisien dari insertion sort dengan membandingkan elemen berjarak tertentu
5. **Merge Sort**: Algoritma divide-and-conquer yang membagi array lalu menggabungkannya kembali secara terurut
6. **Quick Sort**: Algoritma divide-and-conquer yang memilih pivot dan melakukan partisi array

## Cara Penggunaan
1. Pastikan file data `data_angka.txt` dan `data_kata.txt` sudah disiapkan
2. Kompilasi program: `gcc main.c -o benchmark`
3. Jalankan program: `./benchmark`
4. Pilih jenis data yang ingin di-benchmark (angka atau kata)
5. Pilih ukuran data
6. Hasil benchmark akan ditampilkan dalam bentuk tabel

## Catatan Teknis
- Program menggunakan alokasi memori dinamis untuk efisiensi
- Implementasi Quick Sort menggunakan metode "median of three" untuk pemilihan pivot
- Implementasi merge sort menggunakan array tambahan untuk menghindari overhead rekursi
- Program menerapkan optimasi tail recursion pada algoritma Quick Sort
