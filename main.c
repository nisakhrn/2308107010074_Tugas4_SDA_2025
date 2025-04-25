#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h"

// Fungsi untuk memuat data integer dari file
void load_data_int(const char *filename, int *arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file angka");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Data tidak valid di baris %d\n", i + 1);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

// Fungsi untuk memuat data string dari file
void load_data_str(const char *filename, char **arr, int n, int max_len) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file kata");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fgets(arr[i], max_len, fp) == NULL) {
            fprintf(stderr, "Data string tidak valid di baris %d\n", i + 1);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        arr[i][strcspn(arr[i], "\n")] = '\0'; // hapus newline
    }
    fclose(fp);
}

// Wrapper untuk algoritma sorting integer
void mergeSortWrapper(int *arr, int n) { mergeSort(arr, 0, n - 1); }
void quickSortWrapper(int *arr, int n) { quickSort(arr, 0, n - 1); }

// Algoritma sorting untuk string
void bubbleSortStr(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSortStr(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            char *temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void insertionSortStr(char **arr, int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Shell Sort untuk string
void shellSortStr(char **arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Merge Sort untuk string
void mergeStr(char **arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Alokasi dinamis untuk array sementara
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));
    
    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        fprintf(stderr, "Gagal mengalokasikan memori untuk merge\n");
        return;
    }
    
    // Salin data ke array sementara L[] dan R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    
    // Gabungkan array sementara kembali ke arr[l..r]
    i = 0;    // Index awal subarray pertama
    j = 0;    // Index awal subarray kedua
    k = l;    // Index awal subarray gabungan
    
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Salin elemen tersisa dari L[], jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Salin elemen tersisa dari R[], jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Bebaskan array sementara
    free(L);
    free(R);
}

void mergeSortStr(char **arr, int l, int r) {
    if (l < r) {
        // Hindari overflow untuk array besar
        int m = l + (r - l) / 2;
        
        // Urutkan setengah pertama dan kedua
        mergeSortStr(arr, l, m);
        mergeSortStr(arr, m + 1, r);
        
        // Gabungkan setengah yang sudah diurutkan
        mergeStr(arr, l, m, r);
    }
}

// Quick Sort untuk string
int partitionStr(char **arr, int low, int high) {
    // Pilih pivot
    int mid = low + (high - low) / 2;
    
    // Urutkan tiga nilai: low, mid, high
    if (strcmp(arr[mid], arr[low]) < 0) {
        char *tmp = arr[mid]; arr[mid] = arr[low]; arr[low] = tmp;
    }
    if (strcmp(arr[high], arr[low]) < 0) {
        char *tmp = arr[high]; arr[high] = arr[low]; arr[low] = tmp;
    }
    if (strcmp(arr[high], arr[mid]) < 0) {
        char *tmp = arr[high]; arr[high] = arr[mid]; arr[mid] = tmp;
    }
    
    // Sekarang arr[mid] adalah median, tukar dengan arr[high-1]
    char *tmp = arr[mid]; arr[mid] = arr[high-1]; arr[high-1] = tmp;
    
    char *pivot = arr[high-1];
    int i = low - 1;
    
    // Partisi berjalan dari low hingga high-2 karena pivot berada di high-1
    for (int j = low; j < high-1; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            i++;
            tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    
    // Kembalikan pivot ke posisi yang benar
    tmp = arr[i+1]; arr[i+1] = arr[high-1]; arr[high-1] = tmp;
    return i + 1;
}

void quickSortStr(char **arr, int low, int high) {
    if (low < high) {
        int pi = partitionStr(arr, low, high);
        
        // Rekursif untuk bagian yang lebih kecil
        if (pi - low < high - pi) {
            quickSortStr(arr, low, pi - 1);
            low = pi + 1;  // Tail recursion untuk bagian yang lebih besar
        } else {
            quickSortStr(arr, pi + 1, high);
            high = pi - 1;  // Tail recursion untuk bagian yang lebih besar
        }
    }
}

// Wrapper untuk quick sort dan merge sort string
void mergeSortStrWrapper(char **arr, int n) { mergeSortStr(arr, 0, n - 1); }
void quickSortStrWrapper(char **arr, int n) { quickSortStr(arr, 0, n - 1); }

int cmpstr(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Fungsi untuk benchmarking algoritma sorting integer
void benchmark_sort_int(void (*sort_func)(int *, int), const char *label, int *data, int n) {
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        perror("Gagal alokasi");
        exit(EXIT_FAILURE);
    }
    memcpy(arr, data, n * sizeof(int));
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    double memory_mb = (double)(n * sizeof(int)) / (1024 * 1024);
    printf("| %-13s | %12d | %14.3f detik | %10.2f MB |\n", label, n, elapsed_time, memory_mb);
    free(arr);
}

// Fungsi untuk benchmarking algoritma sorting string
void benchmark_sort_str(void (*sort_func)(char **, int), const char *label, char **data, int n, int str_len) {
    char **arr = malloc(n * sizeof(char *));
    if (!arr) {
        perror("Gagal alokasi");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(str_len);
        if (!arr[i]) {
            perror("Gagal alokasi");
            for (int j = 0; j < i; j++) free(arr[j]);
            free(arr);
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i], data[i]);
    }
    
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    double memory_mb = (double)(n * str_len) / (1024 * 1024);
    printf("| %-13s | %12d | %14.3f detik | %10.2f MB |\n", label, n, elapsed_time, memory_mb);
    
    // Free memory
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

// Fungsi untuk benchmarking semua algoritma sorting string
void benchmark_sort_all_str(char **data, int n, int str_len) {
    benchmark_sort_str(bubbleSortStr, "BubbleSort", data, n, str_len);
    benchmark_sort_str(selectionSortStr, "SelectionSort", data, n, str_len);
    benchmark_sort_str(insertionSortStr, "InsertionSort", data, n, str_len);
    benchmark_sort_str(shellSortStr, "ShellSort", data, n, str_len);
    benchmark_sort_str(mergeSortStrWrapper, "MergeSort", data, n, str_len);
    benchmark_sort_str(quickSortStrWrapper, "QuickSort", data, n, str_len);
}

// Menu pilihan untuk ukuran data angka
int show_int_data_menu() {
    int sizes_int[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    const int num_sizes_int = sizeof(sizes_int) / sizeof(sizes_int[0]);
    int choice;
    
    printf("\n========= PILIHAN UKURAN DATA ANGKA =========\n\n");
    for (int i = 0; i < num_sizes_int; i++) {
        printf("%d. %d data\n", i+1, sizes_int[i]);
    }
    printf("0. Kembali ke menu utama\n\n");
    
    do {
        printf("Pilihan Anda [0-%d]: ", num_sizes_int);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Input tidak valid! Silakan masukkan angka.\n");
            choice = -1;
        }
    } while (choice < 0 || choice > num_sizes_int);
    
    if (choice == 0) return 0;
    return sizes_int[choice-1];
}

// Menu pilihan untuk ukuran data kata
int show_str_data_menu() {
    // Menambahkan ukuran data 250.000, 500.000, 1.000.000, 1.500.000, 2.000.000
    // Menghapus ukuran data 150.000, 200.000
    int sizes_str[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    const int num_sizes_str = sizeof(sizes_str) / sizeof(sizes_str[0]);
    int choice;
    
    printf("\n========= PILIHAN UKURAN DATA KATA =========\n\n");
    for (int i = 0; i < num_sizes_str; i++) {
        printf("%d. %d data\n", i+1, sizes_str[i]);
    }
    printf("0. Kembali ke menu utama\n\n");
    
    do {
        printf("Pilihan Anda [0-%d]: ", num_sizes_str);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Input tidak valid! Silakan masukkan angka.\n");
            choice = -1;
        }
    } while (choice < 0 || choice > num_sizes_str);
    
    if (choice == 0) return 0;
    return sizes_str[choice-1];
}

// Menu utama
int show_main_menu() {
    int choice;
    
    printf("\n========= PROGRAM BENCHMARK SORTING =========\n\n");
    printf("1. Benchmark Sorting Angka\n");
    printf("2. Benchmark Sorting Kata\n");
    printf("0. Keluar\n\n");
    
    do {
        printf("Pilihan Anda [0-2]: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Input tidak valid! Silakan masukkan angka.\n");
            choice = -1;
        }
    } while (choice < 0 || choice > 2);
    
    return choice;
}

int main() {
    // Meningkatkan total data untuk kata menjadi 2.000.000 untuk mendukung opsi baru
    const int total_data_int = 2000000;
    const int total_data_str = 2000000;
    const int max_str_len = 100;
    
    // Alokasi memori untuk data
    int *full_data_int = malloc(total_data_int * sizeof(int));
    if (!full_data_int) {
        perror("Gagal alokasi memori untuk data angka");
        exit(EXIT_FAILURE);
    }
    
    char **full_data_str = malloc(total_data_str * sizeof(char *));
    if (!full_data_str) {
        perror("Gagal alokasi memori untuk data kata");
        free(full_data_int);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < total_data_str; i++) {
        full_data_str[i] = malloc(max_str_len);
        if (!full_data_str[i]) {
            perror("Gagal alokasi memori untuk string");
            for (int j = 0; j < i; j++) free(full_data_str[j]);
            free(full_data_str);
            free(full_data_int);
            exit(EXIT_FAILURE);
        }
    }
    
    // Muat data
    printf("Memuat data dari file... Mohon tunggu...\n");
    load_data_int("data_angka.txt", full_data_int, total_data_int);
    load_data_str("data_kata.txt", full_data_str, total_data_str, max_str_len);
    printf("Data berhasil dimuat!\n");
    
    int choice, data_size;
    
    // Loop menu utama
    while ((choice = show_main_menu()) != 0) {
        switch (choice) {
            case 1: // Benchmark sorting angka
                data_size = show_int_data_menu();
                if (data_size > 0) {
                    printf("\n=======================================================================\n");
                    printf("                BENCHMARK SORTING ANGKA (%d DATA)                     \n", data_size);
                    printf("=======================================================================\n\n");
                    printf("+---------------+--------------+----------------------+-------------+\n");
                    printf("| Algoritma     | Jumlah Data  | Waktu Eksekusi       | Memori (MB) |\n");
                    printf("+---------------+--------------+----------------------+-------------+\n");
                    benchmark_sort_int(bubbleSort,       "BubbleSort",    full_data_int, data_size);
                    benchmark_sort_int(selectionSort,    "SelectionSort", full_data_int, data_size);
                    benchmark_sort_int(insertionSort,    "InsertionSort", full_data_int, data_size);
                    benchmark_sort_int(mergeSortWrapper, "MergeSort",     full_data_int, data_size);
                    benchmark_sort_int(quickSortWrapper, "QuickSort",     full_data_int, data_size);
                    benchmark_sort_int(shellSort,        "ShellSort",     full_data_int, data_size);
                    printf("+---------------+--------------+----------------------+-------------+\n\n");
                    
                    // Tunggu user menekan Enter sebelum kembali ke menu
                    printf("Tekan Enter untuk melanjutkan...");
                    while (getchar() != '\n'); // Clear input buffer
                    getchar();
                }
                break;
                
            case 2: // Benchmark sorting kata
                data_size = show_str_data_menu();
                if (data_size > 0) {
                    printf("\n=======================================================================\n");
                    printf("                BENCHMARK SORTING KATA (%d DATA)                      \n", data_size);
                    printf("=======================================================================\n\n");
                    printf("+---------------+--------------+----------------------+-------------+\n");
                    printf("| Algoritma     | Jumlah Data  | Waktu Eksekusi       | Memori (MB) |\n");
                    printf("+---------------+--------------+----------------------+-------------+\n");
                    benchmark_sort_all_str(full_data_str, data_size, max_str_len);
                    printf("+---------------+--------------+----------------------+-------------+\n\n");
                    
                    // Tunggu user menekan Enter sebelum kembali ke menu
                    printf("Tekan Enter untuk melanjutkan...");
                    while (getchar() != '\n'); // Clear input buffer
                    getchar();
                }
                break;
        }
    }
    
    // Pembersihan memori
    free(full_data_int);
    for (int i = 0; i < total_data_str; i++) free(full_data_str[i]);
    free(full_data_str);
    
    printf("Terima kasih telah menggunakan program ini!\n");
    return 0;
}