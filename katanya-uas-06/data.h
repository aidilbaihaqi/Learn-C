#ifndef DATA_H
#define DATA_H

typedef struct {
  char nama[50];
  int harga;
  char tglProduksi[11];
} Makanan;

typedef struct Node {
  Makanan makanan;
  struct Node* prev;
  struct Node* next;
} Node;

#endif