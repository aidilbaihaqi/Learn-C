#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100
#define MAX_NAMA 50

typedef struct
{
    char kode[20];
    char nama[MAX_NAMA];
    int kuantiti;
} Barang;

Barang daftarBarang[MAX_BARANG];
int jumlahBarang = 0;

void catatBarangMasuk()
{
    char lagi;
    do
    {
        if (jumlahBarang >= MAX_BARANG)
        {
            printf("\nDaftar barang penuh!\n");
            return;
        }

        Barang barang;
        printf("\nMasukan kode barang: ");
        scanf("%s", barang.kode);
        printf("Masukan nama barang: ");
        scanf(" %[^\n]", barang.nama);
        printf("Masukan jumlah barang: ");
        scanf("%d", &barang.kuantiti);

        daftarBarang[jumlahBarang++] = barang;

        printf("\nMasih ada data? [Y/T]: ");
        scanf(" %c", &lagi);
    } while (lagi == 'Y' || lagi == 'y');
}

void lihatDaftarBarang()
{
    if (jumlahBarang == 0)
    {
        printf("\nTidak ada barang yang dicatat.\n");
        return;
    }

    printf("\nNoInput KodeBarang NamaBarang Qty\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        printf("%d %s %s %d\n", i + 1, daftarBarang[i].kode, daftarBarang[i].nama, daftarBarang[i].kuantiti);
    }
}

void hapusBarangMasuk()
{
    if (jumlahBarang == 0)
    {
        printf("\nTidak ada barang yang dicatat.\n");
        return;
    }

    int index;
    printf("\nMasukan nomor inputan yang mau di hapus: ");
    scanf("%d", &index);

    if (index < 1 || index > jumlahBarang)
    {
        printf("\nNomor Inputan tidak ada.\n");
        return;
    }

    printf("\nNoInput KodeBarang NamaBarang Qty\n");
    printf("%d %s %s %d\n", index, daftarBarang[index - 1].kode, daftarBarang[index - 1].nama, daftarBarang[index - 1].kuantiti);

    char yakin;
    printf("\nYakin di hapus? [Y/T]: ");
    scanf(" %c", &yakin);

    if (yakin == 'Y' || yakin == 'y')
    {
        for (int i = index - 1; i < jumlahBarang - 1; i++)
        {
            daftarBarang[i] = daftarBarang[i + 1];
        }
        jumlahBarang--;
        printf("\nData berhasil dihapus!\n");
    }
    else
    {
        printf("\nPenghapusan dibatalkan.\n");
    }
}

void rekamKeFileCSV()
{
    FILE *file = fopen("DATAKU.CSV", "w");
    if (!file)
    {
        printf("\nGagal rekam.\n");
        return;
    }

    fprintf(file, "Kode,Nama,Kuantiti\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        fprintf(file, "%s,%s,%d\n", daftarBarang[i].kode, daftarBarang[i].nama, daftarBarang[i].kuantiti);
    }

    fclose(file);
    printf("\nData berhasil di rekam ke DATAKU.CSV\n");
}

int main()
{
    int pilihan;

    do
    {
        printf("\nMenu Gudang\n");
        printf("[1] Catat barang masuk\n");
        printf("[2] Lihat daftar barang masuk\n");
        printf("[3] Hapus barang masuk\n");
        printf("[5] Rekam ke file CSV\n");
        printf("[9] Keluar\n");
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            catatBarangMasuk();
            break;
        case 2:
            lihatDaftarBarang();
            break;
        case 3:
            hapusBarangMasuk();
            break;
        case 5:
            rekamKeFileCSV();
            break;
        case 9:
            printf("Terimakasih. Program selesai.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 9);

    return 0;
}
