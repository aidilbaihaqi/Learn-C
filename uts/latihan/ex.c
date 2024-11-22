#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char kode[10];
  char nama[50];
  int Qty;
} Barang;

void tampilkanMenu() {
  printf("\nMenu Gudang\n");
  printf("[1] Catat barang\n");
  printf("[2] Lihat daftar barang\n");
  printf("[3] Hapus data barang\n");
  printf("[5] Rekam CSV File\n");
  printf("[9] Keluar\n");
}

void tampilkanDaftar(Barang *barang, int jumlahBarang) 
{
  printf("\nData Barang\n");
  if(jumlahBarang == 0)
  {
    printf("Tidak ada data tercatat.");
  }else {
    for(int i=0; i < jumlahBarang; i++) {
      printf("%d  %-10s  %-20s  %d\n", i+1, barang[i].kode, barang[i].nama, barang[i].Qty);
    }
  }
}

void tambahBarang(Barang *barang)
{
  printf("Masukkan kode barang: ");
  scanf("%s",barang->kode);
  printf("Masukkan nama barang: ");
  scanf(" %[^\n]", barang->nama);
  printf("Masukkan jumlah barang: ");
  scanf("%d", &barang->Qty);
}

void hapusBarang(Barang **barang, int *jumlahBarang)
{
  int noHapus;
  char yakinHapus;

  tampilkanDaftar(*barang, *jumlahBarang);
  printf("Masukkan kode barang yang ingin dihapus: ");
  scanf("%d", &noHapus);

  printf("Yakin mau dihapus?: ");
  scanf(" %c", &yakinHapus);

  if(yakinHapus == 'Y' || yakinHapus == 'y'){
    for(int i = noHapus-1; i < *jumlahBarang-1; i++) {
      (*barang)[i] = (*barang)[i+1];
    }
    (*jumlahBarang)--;

    *barang = realloc(*barang, (*jumlahBarang)*sizeof(Barang));
    printf("Data berhasil dihapus!\n");
    tampilkanDaftar(*barang, *jumlahBarang);
  }else {
    pritnf("Penghapusan dibatalkan!");
  }
}

void RekamKeCSV(Barang *barang, int jumlahBarang)
{
  FILE *file = fopen("DATAKU.CSV", "w");
  if(file == NULL){
    printf("Gagal buka file\n");
    return;
  }
  fprintf(file, "NoInput,KodeBarang,NamaBarang,Qty\n");
  for(int i=0; i < jumlahBarang; i++) {
    fprintf(file, "%d,%s,%s,%d",i+1,barang[i].kode,barang[i].nama,barang[i].Qty);
  }
  fclose(file);
  printf("Data berhasil direkam ke file csv\n");
}

int main()
{
  Barang *barang = NULL;
  char masihAdaData;
  int pilihan;
  int jumlahBarang = 0;

  while(1)
  {
    tampilkanMenu();
    scanf("%d", pilihan);
    switch(pilihan)
    {
      case 1:
        do {
          barang = realloc(barang, (jumlahBarang+1) * sizeof(Barang));
          if(barang != NULL) {
            tambahBarang(&barang[jumlahBarang]);
            jumlahBarang++;
          }else {
            printf("Gagal alokasikan memori\n");
            exit(1);
          }
          printf("Masih ada data?[Y/T]: ");
          scanf(" %c", &masihAdaData);
        }while(masihAdaData == 'Y' || masihAdaData == 'y');
        break;
      
      case 2:
        if(jumlahBarang > 0) {
          tampilkanDaftar(barang, jumlahBarang);
        }else {
          printf("Tidak ada data tercatat\n");
        }
        break;
      
      case 3:
        if(jumlahBarang > 0) {
          hapusBarang(&barang, &jumlahBarang);
        }else {
          printf("Tidak ada data tercatat\n");
        }
        break;
      
      case 5:
        if(jumlahBarang > 0) {
          RekamKeCSV(barang, jumlahBarang);
        }else {
          printf("Tidak ada data tercatat\n");
        }
        break;
      
      case 9:
        printf("Terimakasih program selesai\n");
        free(barang);
        return 0;
      
      default:
        printf("Inputan tidak valid\n");
    }
  }
}