#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char kode[10];
    char nama[50];
    int Qty;
} Barang;

void tampilkanMenu()
{
    printf("Menu Gudang\n");
    printf("[1] Catat barang masuk\n");
    printf("[2] Lihat daftar barang masuk\n");
    printf("[3] Hapus data barang masuk\n");
    printf("[5] Rekam ke file CSV\n");
    printf("[9] Keluar\n");
    printf("Pilihan Anda:");
}
void tampilkanDaftar(Barang *barang, int jumlahBarang)
{
    printf("\nNoInputan  KodeBarang NamaBarang                   Qty\n");
    if (jumlahBarang == 0)
    {
        printf("Tidak ada data tercatat");
        return;
    }
    else
    {
        for (int i = 0; i < jumlahBarang; i++)
        {
            printf("%d          %-10s   %-20s   %d\n", i + 1, barang[i].kode, barang[i].nama, barang[i].Qty);
        }
    }
}
void tambahBarang(Barang *barang)
{
    printf("Masukan kode barang:");
    scanf("%s", barang->kode);
    printf("Masukan nama barang:");
    scanf(" %[^\n]", barang->nama);
    printf("Masukan jumlah barang:");
    scanf("%d", &barang->Qty);
}
void hapusBarang(Barang *barang, int *jumlahBarang)
{
    int noHapus;
    char YakinHapus;

    tampilkanDaftar(barang, *jumlahBarang);
    printf("Masukan nomor inputan yang mau dihapus:");
    scanf("%s", &noHapus);

    printf("Yakin dihapus?[Y/T]");
    scanf(" %c", &YakinHapus);
    if (YakinHapus == 'Y' || YakinHapus == 'y')
    {
        for (int i = noHapus - 1; i < *jumlahBarang; i++)
        {
            barang[i] = barang[i + 1];
        }
        (*jumlahBarang)--;
        printf("Barang berhasil dihapus.\n");

        tampilkanDaftar(barang, *jumlahBarang);
    }
    else
    {
        printf("Penghapusan dibatalkan");
    }
}
void RekamkeCSV(Barang *barang, int jumlahBarang)
{
    FILE *file = fopen("DATAKU.CSV", "w");
    if (file == NULL)
    {
        printf("Gagal buka file.\n");
        return;
    }
    fprintf(file, "NoInput,KodeBarang,NamaBarang,Qty\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        fprintf(file, "%d,%s,%s,%d\n", i + 1, barang[i].kode, barang[i].nama, barang[i].Qty);
    }
    fclose(file);
    printf("Berhasil direkam ke file csv\n");
}
int main()
{
    Barang barang[100];
    char MasihAdaData;
    int pilihan;
    int jumlahBarang = 0;

    while (1)
    {
        tampilkanMenu();
        scanf("%d", &pilihan);
        switch (pilihan)
        {
        case 1:
            do
            {
                if (jumlahBarang < 100)
                {
                    tambahBarang(&barang[jumlahBarang]);
                    jumlahBarang++;
                }
                else
                {
                    printf("Data gudang penuh");
                }
                printf("Masih ada data?[Y/T]");
                scanf(" %c", &MasihAdaData);
            } while (MasihAdaData == 'Y' || MasihAdaData == 'y');
            break;
        case 2:
            if (jumlahBarang > 0)
            {
                tampilkanDaftar(barang, jumlahBarang);
            }
            else
            {
                printf("Tidak ada data tercatat.\n");
            }
            break;
        case 3:
            if (jumlahBarang > 0)
            {
                hapusBarang(barang, &jumlahBarang);
            }
            else
            {
                printf("Tidak ada data tercatat.\n");
            }
            break;
        case 5:
            if (jumlahBarang > 0)
            {
                RekamkeCSV(barang, jumlahBarang);
            }
            else
            {
                printf("Tidak ada data tercatat.\n");
            }
            break;
        case 9:
            printf("Terimakasih,Program telah selesai");
            return 0;
        default:
            printf("Pilihan tidak valid,silahkan coba lagi.\n");
        }
    }
}