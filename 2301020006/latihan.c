#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int jam;
    int menit;
    float kecepatan;
    float arah;
} DataCuaca;

DataCuaca *dataCuaca = NULL;
int jumlahData = 0;
int kapasitas = 0;

void tambahKapasitas() {
    if (jumlahData == kapasitas) {
        kapasitas = kapasitas == 0 ? 2 : kapasitas * 2;
        dataCuaca = realloc(dataCuaca, kapasitas * sizeof(DataCuaca));
        if (dataCuaca == NULL) {
            printf("Gagal mengalokasikan memori\n");
            exit(1);
        }
    }
}

void inputDataCuaca(int *jam, int *menit, float *kecepatan, float *arah) {
    printf("Masukan waktu pencatatan([0-24] [0-59]): ");
    scanf("%d %d", jam, menit);
    printf("Masukan kecepatan angin(km/h): ");
    scanf("%f", kecepatan);
    printf("Masukan arah angin(0.0-359.0): ");
    scanf("%f", arah);
}

void catatArusAngin() {
    char lagi;
    do {
        tambahKapasitas();
        inputDataCuaca(&dataCuaca[jumlahData].jam, &dataCuaca[jumlahData].menit,
                       &dataCuaca[jumlahData].kecepatan, &dataCuaca[jumlahData].arah);
        jumlahData++;
        printf("Masih ada data? [Y/T]: ");
        scanf(" %c", &lagi);
    } while (lagi == 'Y' || lagi == 'y');
}

void lihatDaftarArusAngin() {
    printf("Waktu\tKecepatan\tArah\n");
    for (int i = 0; i < jumlahData; i++) {
        printf("%02d:%02d\t%.2f\t\t%.2f\n", dataCuaca[i].jam, dataCuaca[i].menit,
               dataCuaca[i].kecepatan, dataCuaca[i].arah);
    }
}

int cariDataCuaca(int jam, int menit) {
    for (int i = 0; i < jumlahData; i++) {
        if (dataCuaca[i].jam == jam && dataCuaca[i].menit == menit) {
            return i;
        }
    }
    return -1;
}

void editDataArusAngin() {
    int jam, menit, index;
    printf("Masukan waktu yang mau di edit([0-24] [0-59]): ");
    scanf("%d %d", &jam, &menit);

    index = cariDataCuaca(jam, menit);
    if (index == -1) {
        printf("Waktu Inputan tidak ditemukan.\n");
    } else {
        inputDataCuaca(&dataCuaca[index].jam, &dataCuaca[index].menit,
                       &dataCuaca[index].kecepatan, &dataCuaca[index].arah);
        printf("Data berhasil diubah!\n");
    }
}

void simpanKeFile() {
    FILE *file = fopen("ANGIN.DAT", "wb");
    if (file == NULL) {
        printf("Gagal merekam data\n");
        return;
    }
    fwrite(dataCuaca, sizeof(DataCuaca), jumlahData, file);
    printf("Data berhasil direkam ke ANGIN.DAT\n");
    fclose(file);
}

void tampilkanDariFile() {
    FILE *file = fopen("ANGIN.DAT", "rb");
    if (file == NULL) {
        printf("Gagal membuka file ANGIN.DAT\n");
        return;
    }
    DataCuaca data;
    printf("Waktu\tKecepatan\tArah\n");
    while (fread(&data, sizeof(DataCuaca), 1, file)) {
        printf("%02d : %02d\t%.2f\t\t%.2f\n", data.jam, data.menit, data.kecepatan, data.arah);
    }
    fclose(file);
}

void menu() {
    int pilihan;
    do {
        printf("\nMenu Riset Cuaca\n");
        printf("[1] Catat arus angin\n");
        printf("[2] Lihat daftar arus angin\n");
        printf("[3] Edit data arus angin\n");
        printf("[5] Rekam data harian\n");
        printf("[6] Lihat keseluruhan rekaman\n");
        printf("[9] Keluar\n");
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: catatArusAngin(); break;
            case 2: lihatDaftarArusAngin(); break;
            case 3: editDataArusAngin(); break;
            case 5: simpanKeFile(); break;
            case 6: tampilkanDariFile(); break;
            case 9: printf("Terima kasih. Program selesai.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 9);
}

int main() {
    menu();
    free(dataCuaca);  // Bersihkan memori yang dialokasikan
    return 0;
}