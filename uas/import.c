#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void importData(Masakan daftarMasakan[], int *jumlahMasakan) {
    char filePath[100];
    FILE *file;

    printf("Masukan path dan nama file CSV: ");
    scanf("%s", filePath);

    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("E003. Error Import Data Baru\n");
        return;
    }

    while (fscanf(file, "%[^,],%d,%s\n", daftarMasakan[*jumlahMasakan].nama, &daftarMasakan[*jumlahMasakan].harga, daftarMasakan[*jumlahMasakan].tanggal) != EOF) {
        (*jumlahMasakan)++;
    }

    fclose(file);
    printf("Data berhasil diimpor.\n");
}
