#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
// import 
// export

void formatHarga(int harga) {
  char str[20];
  sprintf(str, "%d", harga);
  int len = strlen(str);
  int count = 0;
  char result[30];
  int j = 0;

  for (int i = len - 1; i>=0 ; i--) {
    result[j++] = str[i];
    count++;
    if(count == 3 && i!=0) {
      result[j++] = '.';
      count = 0;
    }
  }

  result[j] = '\0';

  for(int i=0; i < j / 2; i++) {
    char temp = result[i];
    result[i] = result[j - i - 1];
    result[j - i - 1] = temp;
  }

  printf("Rp. %s\n", result);
}

void menu() {
  printf("\nMenu Masakan\n");
  printf("[\033[34m1\033[0m] Input Data Baru\n");
  printf("[\033[34m2\033[0m] Import Data Baru\n");
  printf("[\033[34m3\033[0m] Browse Data\n");
  printf("[\033[34m4\033[0m] Export ke CSV\n");
  printf("[\033[34m9\033[0m] Berhenti Program\n");
  printf("Pilihan anda: ");
}

int validasiTgl(const char *tgl){
  if(strlen(tgl) != 8 || tgl[2] != '-' || tgl[5] != '-')
    return 0;
  
  int hari = atoi(tgl);
  int bulan = atoi(&tgl[3]);
  int tahun = atoi(&tgl[6]);
  int hariDalamBulan[] = {31,28,31,30,31,30,31,31,30,31,30,31};

  if(tahun % 4 == 0 && (tahun % 100 != 0 || tahun % 400 == 0 )) {
    hariDalamBulan[1] = 29;
  }
  if(bulan<1 || bulan>12 || hari<1 || hari>hariDalamBulan[bulan - 1]) {
    return 0;
  }

  return 1;
}

void tambahData(Node **head) {
  char lanjut;
  do{
    Makanan masakan;
    printf("\nMasukan Nama Masakan: ");
    scanf("%[^\n]", masakan.nama);
    printf("Masukan Harga Jual: Rp. ");
    scanf("%d", &masakan.harga);

    do{
      printf("Masukan Tanggal Produksi hari-bulan-tahun (00-00-00): ");
      scanf(" %s", masakan.tglProduksi);
      if(!validasiTgl(masakan.tglProduksi)) {
        printf("Maaf, tanggal salah. Format yang diperbolehkan 00-00-00\n dimana hari-bulan-tahun\n");
        printf("Silahkan ulangin penginputan tanggal produksi");
      }
    }while(!validasiTgl(masakan.tglProduksi));

    Node *new = (Node* )malloc(sizeof(Node));
    new->makanan = masakan;
    new->prev = NULL;
    new->next = NULL;

    if(*head == NULL) {
      *head = new;
    }else {
      Node *temp = *head;
      while(temp->next) 
        temp = temp->next;
      temp->next = new;
      temp->prev = temp;
    }

    printf("Masih ada data?[Y/T]: ");
    scanf(" %c", &lanjut);
  }while(lanjut == 'Y' || lanjut == 'y');
}

int main() {
  Node *head = NULL;
  int choice;

  do{
    menu();
    scanf("%d", &choice);

    switch(choice) {
      case 1:
        tambahData(&head);
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 9:
        printf("Terimakasih telah menggunakan program keren ini!\n");
        break;
      default: 
        printf("Maaf, pilihan salah. Hanya boleh 1,2,3,4 atau 9\nSilahkan ulangi pilihan mu\n");
    }
  }while(choice!=9);

  Node *now = head;
  while(now) {
    Node *del = now;
    now = now->next;
    free(del);
  }

  return 0;
}