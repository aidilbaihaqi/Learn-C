#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
  printf("Hello World\n");

  if(argc == 3){
    // loop untuk baris
    for(int i=1; i<=atoi(argv[1]); i++){
      // loop untuk kolom
      for(int j=1; j<=atoi(argv[2]); j++) {
        printf("o ");
      }
      printf("\n");
    }
  }else {
    printf("mohon masukkan 2 argumen untuk baris dan kolom saja");
  }
  
  return 0;
}