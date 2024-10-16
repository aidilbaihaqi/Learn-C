#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
  char kode[10];
  char nama[50];
  int qty;
} Barang;

// Fungsi main menu
void mainMenu()
{
  printf("Menu Gudang\n");
  printf("[1] Catat barang masuk\n");
  printf("[2] Lihat daftar barang masuk\n");
  printf("[3] Hapus barang masuk\n");
  printf("[5] Rekam ke file CSV\n");
  printf("[9] Keluar\n");
  printf("Pilihan anda: ");
}

// Fungsi menampilkan data
void viewData(Barang *barang, int jumlahBarang)
{
  if(jumlahBarang == 0)
  {
    printf("Tidak ada barang yang tercatat");
  }else 
  {
    printf("NoInput\tKodeBarang\tNamaBarang\tQty\n");
    for(int i=0; i<jumlahBarang; i++)
    {
      printf("%d\t%s\t%s\t%d\n", i+1, barang[i].kode, barang[i].nama, barang[i].qty);
    }
  }
}

// Fungsi untuk menambahkan data
void addData(Barang *barang)
{
  printf("Masukkan kode barang: ");
  scanf("%s", barang->kode);
  printf("Masukkan nama barang: ");
  scanf(" %[^\n]", barang->nama);
  printf("Masukkan jumlah barang: ");
  scanf("%d", &barang->qty);
}

// Fungsi untuk menghapus data
void deleteData(Barang *barang, int *jumlahBarang)
{
  int id;
  char yakinHapus;

  printf("Masukkan nomor inputan yang mau dihapus: ");
  scanf("%d", &id);

  printf("Yakin dihapus? [Y/T]");
  scanf(" %c", &yakinHapus);

  if(yakinHapus == 'Y' || yakinHapus == 'y')
  {
    for(int i = id - 1; i < *jumlahBarang - 1; i++)
    {
      barang[i] = barang[i+1];
    }
    (*jumlahBarang)--;
    printf("Barang berhasil dihapus.\n");
  }else {
    printf("Penghapusan dibatalkan!\n");
  }
}

void addCSV(Barang *barang, int jumlahbarang)
{
  FILE *file = fopen("DATAKU.CSV", "w");
  if(file == NULL)
  {
    printf("Gagal buka file. \n");
  }
  fprintf(file, "NoInput,KodeBarang,NamaBarang,Qty\n");
  for(int i=0; i< jumlahbarang; i++)
  {
    fprintf(file, "%d,%s,%s,%d\n", i+1,barang[i].kode, barang[i].nama, barang[i].qty);
  }
  fclose(file);
  printf("Berhasil direkam ke file csv\n");
}

int main()
{
  Barang *barang = NULL; // Pointer untuk menyimpan array dinamis
  char anyData;
  int choice;
  int jumlahBarang = 0;
  int kapasitas = 2; // Kapasitas awal

  barang = (Barang *)malloc(kapasitas * sizeof(Barang)); // Alokasi memori

  // Pengecekan alokasi memori
  if(barang == NULL)
  {
    printf("Alokasi memori gagal!\n");
    return 1;
  }

  while (1)
  {
    mainMenu();
    scanf("%d", &choice);
    switch(choice)
    {
      case 1:
        do
        {
          if(jumlahBarang >= kapasitas)
          {
            kapasitas*=2; // Gandakan kapasitas memori jika penuh
            barang = (Barang *)realloc(barang, kapasitas * sizeof(Barang));
            if(barang == NULL)
            {
              printf("Gagal menambahkan memori!\n");
              return 1;
            }
          }

          addData(&barang[jumlahBarang]);
          jumlahBarang++;

          printf("Masih ada data? [Y/T]: ");
          scanf(" %c", &anyData);
        } while (anyData == 'Y' || anyData == 'y');
        
        break;
      
      case 2:
        if(jumlahBarang > 0)
        {
          viewData(barang, jumlahBarang);
        }else 
        {
          printf("Tidak ada barang tercatat.\n\n");
        }

        break;

      case 3:
        if(jumlahBarang > 0)
        {
          deleteData(barang, &jumlahBarang);
        }else 
        {
          printf("Tidak ada barang tercatat.\n\n");
        }
        break;

      case 5:
        if(jumlahBarang > 0)
        {
          addCSV(barang, jumlahBarang);
        }else {
          printf("Tidak ada barang tercatat.\n\n");
        }
        
        break;
      case 9:
        printf("Terimakasih. Program selesai.\n");
        return 0;
      default:
        printf("Pilihan tidak valid, silahkan coba lagi.\n\n");
    }
  }
}