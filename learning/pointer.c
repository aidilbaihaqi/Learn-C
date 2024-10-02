#include <stdio.h>

int main(int argc, char **argv)
{
  printf("C Pointer \n");
  // Pointer adalah sebuah variable yang menyimpan alamat memori dari variable lainnya sebagai sebuah nilai
  // Pointer bertipe data int dan dibuat dengan tanda *
  // There two ways to declare pointer varible
  // 1 => int* number
  // 2 => int *number

  int number = 123;
  int* ptr = &number; // reference pointer variable

  printf("%d\n", number);
  printf("%p\n", &number); // cara langsung memanggil pointer
  printf("%p\n", ptr); // mendeklarasikan reference variable pointer lalu memanggilnya
  printf("%d\n", *ptr); // dereference variable pointer dengan menambahkan *
}