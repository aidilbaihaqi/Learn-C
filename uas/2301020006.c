#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

// Fungsi prototipe
void inputDataBaru(Masakan[], int*);
void importData(Masakan[], int*);
void browseData(Masakan[], int);
void exportData(Masakan[], int);

int main() {
    Masakan daftarMasakan[100];
    int jumlahMasakan = 0;
    int pilihan;

    do {
        printf("\nMenu Masakan\n");
        printf("[1] Input Data Baru\n[2] Import Data Baru\n[3] Browse Data\n[4] Export ke CSV\n[9] Berhenti Program\n");
        printf("Pilihan anda : ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                inputDataBaru(daftarMasakan, &jumlahMasakan);
                break;
            case 2:
                importData(daftarMasakan, &jumlahMasakan);
                break;
            case 3:
                browseData(daftarMasakan, jumlahMasakan);
                break;
            case 4:
                exportData(daftarMasakan, jumlahMasakan);
                break;
            case 9:
                printf("Terima kasih sudah menggunakan aplikasi keren ini.\n");
                break;
            default:
                printf("E001. Error Pilihan\n");
        }
    } while(pilihan != 9);

    return 0;
}

int isValidDate(const char *date) {
    // Periksa panjang string harus 10 karakter (dd-mm-yyyy)
    if (strlen(date) != 10) return 0;

    // Periksa format: angka-angka-angka
    for (int i = 0; i < 10; i++) {
        if ((i == 2 || i == 5) && date[i] != '-') return 0;  // Cek tanda '-'
        if ((i != 2 && i != 5) && !isdigit(date[i])) return 0;  // Cek angka
    }

    // Validasi selesai, format benar
    return 1;
}

void inputDataBaru(Masakan daftarMasakan[], int *jumlahMasakan) {
    printf("Masukan Nama Masakan: ");
    scanf(" %[^\n]", daftarMasakan[*jumlahMasakan].nama);
    printf("Masukan Harga Jual: Rp. ");
    scanf("%d", &daftarMasakan[*jumlahMasakan].harga);

    int valid = 0;
    while (!valid) {
        printf("Masukan Tanggal Produksi (dd-mm-yyyy): ");
        scanf("%s", daftarMasakan[*jumlahMasakan].tanggal);

        // Gunakan fungsi validasi baru
        if (isValidDate(daftarMasakan[*jumlahMasakan].tanggal)) {
            valid = 1;  // Format benar
        } else {
            printf("E002. Error Tanggal Produksi\n");
        }
    }
    (*jumlahMasakan)++;
    printf("Data berhasil ditambahkan.\n");
}

void browseData(Masakan daftarMasakan[], int jumlahMasakan) {
    if (jumlahMasakan == 0) {
        printf("Tidak ada data untuk ditampilkan.\n");
        return;
    }

    int index = 0;
    char pilihan;

    while (1) {
        printf("\nData ke %d dari %d\n", index + 1, jumlahMasakan);
        printf("Nama Masakan: %s\n", daftarMasakan[index].nama);
        printf("Harga: Rp. %d\n", daftarMasakan[index].harga);
        printf("Tanggal Produksi: %s\n", daftarMasakan[index].tanggal);
        printf("\nPilihan P (sebelumnya), N (selanjutnya), Q (berhenti): ");
        scanf(" %c", &pilihan);

        if (pilihan == 'P' || pilihan == 'p') {
            index = (index == 0) ? jumlahMasakan - 1 : index - 1;
        } else if (pilihan == 'N' || pilihan == 'n') {
            index = (index + 1) % jumlahMasakan;
        } else if (pilihan == 'Q' || pilihan == 'q') {
            break;
        } else {
            printf("E004. Error Pilihan\n");
        }
    }
}

