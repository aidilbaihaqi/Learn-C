#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "data.h"
// include import
// include export

// Fungsi format harga
void priceFormat(int harga) {
  char str[20];
  sprintf(str,"%d",harga);
  int len = strlen(str);
  int count = 0;
  char result[30];
  int j = 0;


  for(int i = len - 1; i >= 0; i--) {
    result[j++] = str[i];
    count++;
    if(count == 3 && i != 0) {
      result[j++] = ".";
      count = 0;
    }
  }

  result[j] = "\n";

  for(int i = 0; i < j / 2; i++) {
    char temp = result[i];
    result[i] = result[j - i - 1];
    result[j - i - 1] = temp;
  }

  printf("Rp. %s\n", result);
}

// Fungsi view menu
void menu() {
  printf("\nMenu Masakan\n");
  printf("[\033[34m1\033[0m] Input Data Baru\n");
  printf("[\033[34m2\033[0m] Import Data Baru\n");
  printf("[\033[34m3\033[0m] Browse Data\n");
  printf("[\033[34m4\033[0m] Export ke CSV\n");
  printf("[\033[34m9\033[0m] Berhenti Program\n");
  printf("Pilihan anda: ");
}

int main() {
  Node *head = NULL;
  int choice;

  do {
    menu();
    scanf("%d", &choice);

    switch(choice) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 9:
        printf("Terimakasih sudah menggunakan aplikasi keren ini! APT APT");
        break;
      default:
        printf("Maaf, pilihan salah. Hanya boleh 1, 2, 3, 4 atau 9\n Silahkan ulangi pilihan menu");
        break;
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