#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int jam;
    int menit;
    float kecepatanAngin;
    float arahAngin;
} ArusAngin;

// Prototipe fungsi
void mainMenu();
void catatArusAngin(ArusAngin **data, int *jumlah, int *kapasitas);
void tampilkanDaftar(ArusAngin *data, int jumlah);
void editDataArusAngin(ArusAngin *data, int jumlah);
void rekamDataHarian(ArusAngin *data, int jumlah);
void lihatRekamanKeseluruhan();

// Fungsi utama
int main() {
    ArusAngin *dataArusAngin = NULL;
    int jumlahData = 0;
    int kapasitas = 2;  // Kapasitas awal
    int pilihan;

    // Alokasi awal untuk array dinamis
    dataArusAngin = (ArusAngin *)malloc(kapasitas * sizeof(ArusAngin));
    if (dataArusAngin == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return 1;
    }

    while (1) {
        mainMenu();
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                catatArusAngin(&dataArusAngin, &jumlahData, &kapasitas);
                break;
            case 2:
                tampilkanDaftar(dataArusAngin, jumlahData);
                break;
            case 3:
                editDataArusAngin(dataArusAngin, jumlahData);
                break;
            case 5:
                rekamDataHarian(dataArusAngin, jumlahData);
                break;
            case 6:
                lihatRekamanKeseluruhan();
                break;
            case 9:
                printf("Terimakasih. Program selesai.\n\n");
                free(dataArusAngin);  // Membebaskan memori sebelum keluar
                return 0;
            default:
                printf("Pilihan tidak valid!\n\n");
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu
void mainMenu() {
    printf("\nMenu Riset Cuaca\n");
    printf("[1] Catat arus angin\n");
    printf("[2] Lihat daftar arus angin\n");
    printf("[3] Edit data arus angin\n");
    printf("[5] Rekam data harian\n");
    printf("[6] Lihat keseluruhan rekaman\n");
    printf("[9] Keluar\n");
}

// Fungsi untuk menambah data arus angin ke dalam array dinamis
void catatArusAngin(ArusAngin **data, int *jumlah, int *kapasitas) {
    if (*jumlah >= *kapasitas) {
        *kapasitas *= 2;
        *data = (ArusAngin *)realloc(*data, (*kapasitas) * sizeof(ArusAngin));
        if (*data == NULL) {
            printf("Gagal memperbesar memori.\n");
            return;
        }
    }

    // Input waktu pencatatan (jam dan menit)
    printf("Masukkan waktu pencatatan (jam [0-24] menit [0-59]): ");
    scanf("%d %d", &(*data)[*jumlah].jam, &(*data)[*jumlah].menit);
    
    // Validasi input waktu
    if ((*data)[*jumlah].jam < 0 || (*data)[*jumlah].jam > 24 || (*data)[*jumlah].menit < 0 || (*data)[*jumlah].menit > 59) {
        printf("Waktu tidak valid! Harap masukkan rentang yang benar.\n");
        return;
    }

    // Input kecepatan angin
    printf("Masukkan kecepatan angin (km/h): ");
    scanf(" %f", &(*data)[*jumlah].kecepatanAngin);

    // Input arah angin dalam derajat (0.0 - 359.0)
    printf("Masukkan arah angin (0.0 - 359.0): ");
    scanf("%f", &(*data)[*jumlah].arahAngin);

    if ((*data)[*jumlah].arahAngin < 0.0 || (*data)[*jumlah].arahAngin > 359.0) {
        printf("Arah angin tidak valid! Harap masukkan rentang yang benar.\n");
        return;
    }

    (*jumlah)++;
    printf("Data arus angin berhasil dicatat!\n");
}

// Fungsi untuk menampilkan daftar arus angin
void tampilkanDaftar(ArusAngin *data, int jumlah) {
    if (jumlah == 0) {
        printf("Tidak ada data arus angin tercatat.\n");
        return;
    }
    printf("\nDaftar Arus Angin:\n");
    printf("No   Jam:Menit     Kecepatan (km/h)  Arah Angin (derajat)\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d    %02d:%02d        %-15.2f  %-10.2f\n", i + 1, data[i].jam, data[i].menit, data[i].kecepatanAngin, data[i].arahAngin);
    }
}

// Fungsi untuk mengedit data arus angin yang sudah ada
void editDataArusAngin(ArusAngin *data, int jumlah) {
    int noEdit;
    tampilkanDaftar(data, jumlah);

    if (jumlah == 0) return;

    printf("Masukkan nomor data yang ingin diubah: ");
    scanf("%d", &noEdit);

    if (noEdit < 1 || noEdit > jumlah) {
        printf("Nomor tidak valid.\n");
        return;
    }

    noEdit--;  // Indeks array mulai dari 0
    printf("Masukkan waktu pencatatan baru (jam [0-24] menit [0-59]): ");
    scanf("%d %d", &data[noEdit].jam, &data[noEdit].menit);

    printf("Masukkan kecepatan angin baru (km/h): ");
    scanf(" %f", &data[noEdit].kecepatanAngin);

    printf("Masukkan arah angin baru (0.0 - 359.0): ");
    scanf("%f", &data[noEdit].arahAngin);

    printf("Data berhasil diubah.\n");
}

// Fungsi untuk merekam data harian ke file CSV
void rekamDataHarian(ArusAngin *data, int jumlah) {
    if (jumlah == 0) {
        printf("Tidak ada data untuk direkam.\n");
        return;
    }

    FILE *file = fopen("rekaman_cuaca.csv", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "Waktu Pencatatan,Kecepatan Angin (km/h),Arah Angin (derajat)\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%02d:%02d,%.2f,%.2f\n", data[i].jam, data[i].menit, data[i].kecepatanAngin, data[i].arahAngin);
    }

    fclose(file);
    printf("Data harian berhasil direkam ke file 'rekaman_cuaca.csv'.\n");
}

// Fungsi untuk melihat keseluruhan rekaman data dari file CSV
void lihatRekamanKeseluruhan() {
    char buffer[256];
    FILE *file = fopen("rekaman_cuaca.csv", "r");

    if (file == NULL) {
        printf("Belum ada rekaman cuaca tersimpan.\n");
        return;
    }

    printf("\nRekaman Cuaca:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}
