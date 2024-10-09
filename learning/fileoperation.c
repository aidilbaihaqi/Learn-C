#include <stdio.h>

// Operasi file ada dua bentuk yaitu : text dan binary
// tiap macam file memiliki mode mode yang berbeda. [nnti search aja: mode text and binary file]s

int main(int argc, char** argv)
{
  printf("Operation File\n");
  
  FILE *fptr;
  fptr = fopen(argv[1], "w"); 

  if(fptr!=NULL) {
    printf("Sukses bikin file %s", argv[1]);
  }else {
    printf("Gagal bikin file %s", argv[1]);
    exit(1);
  }
  fclose(fptr);

  return 0;
}