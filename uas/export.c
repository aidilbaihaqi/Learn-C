#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void exportData(Masakan daftarMasakan[], int jumlahMasakan) {
    char filePath[100];
    FILE *file;

    printf("Masukan path dan nama file untuk di export: ");
    scanf("%s", filePath);

    file = fopen(filePath, "w");
    if (file == NULL) {
        printf("E005. Error Export\n");
        return;
    }

    for (int i = 0; i < jumlahMasakan; i++) {
        fprintf(file, "%s,%d,%s\n", daftarMasakan[i].nama, daftarMasakan[i].harga, daftarMasakan[i].tanggal);
    }

    fclose(file);
    printf("Data berhasil diekspor.\n");
}
