#ifndef SORTS_H
#define SORTS_H

#include <stdlib.h>
#include <stdio.h>

// Bubble Sort: Membandingkan elemen bersebelahan dan menukar jika urutan salah
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

// Insertion Sort: Menyisipkan elemen ke posisi yang benar dalam bagian array yang telah diurutkan
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort: Mencari nilai terkecil dan menukarnya ke posisi paling awal
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
}

// Shell Sort: Versi cepat dari insertion sort dengan membandingkan elemen berjarak tertentu
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

// Merge Sort: Membagi array lalu menggabungkannya kembali secara terurut
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Alokasi dinamis untuk menghindari VLA
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        fprintf(stderr, "Gagal mengalokasikan memori untuk merge\n");
        return;
    }
    
    // Salin data ke array sementara
    for (int i = 0; i < n1; i++) 
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j];

    // Gabungkan array kembali
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Salin sisa elemen dari L[] jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Salin sisa elemen dari R[] jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Bebaskan memori
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Hindari overflow untuk array besar
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort: Memilih pivot lalu partisi array ke kiri-kanan lalu rekursif
int partition(int arr[], int low, int high) {
    // Pilih pivot sebagai median dari tiga nilai untuk mengurangi kemungkinan kasus terburuk
    int mid = low + (high - low) / 2;
    
    // Urutkan tiga nilai: low, mid, high
    if (arr[mid] < arr[low])
        { int tmp = arr[mid]; arr[mid] = arr[low]; arr[low] = tmp; }
    if (arr[high] < arr[low])
        { int tmp = arr[high]; arr[high] = arr[low]; arr[low] = tmp; }
    if (arr[high] < arr[mid])
        { int tmp = arr[high]; arr[high] = arr[mid]; arr[mid] = tmp; }
        
    // Sekarang arr[mid] adalah median, tukar dengan arr[high-1]
    { int tmp = arr[mid]; arr[mid] = arr[high-1]; arr[high-1] = tmp; }
    
    int pivot = arr[high-1];
    int i = low - 1;
    
    // Partisi berjalan dari low hingga high-2 karena pivot berada di high-1
    for (int j = low; j < high-1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    
    // Kembalikan pivot ke posisi yang benar
    int tmp = arr[i+1]; arr[i+1] = arr[high-1]; arr[high-1] = tmp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    // Tambahkan perlindungan stack untuk array besar
    while (low < high) {
        int pi = partition(arr, low, high);
        
        // Rekursif untuk bagian yang lebih kecil
        if (pi - low < high - pi) {
            quickSort(arr, low, pi - 1);
            low = pi + 1;  // Tail recursion untuk bagian yang lebih besar
        } else {
            quickSort(arr, pi + 1, high);
            high = pi - 1;  // Tail recursion untuk bagian yang lebih besar
        }
    }
}

#endif