#include <stdio.h>

int main() {
  
  // Postfix Expression
  //  A B +
  //  A B * C +
  // dapat diselesaikan dengan stack

  // Cara konversi infix to postfix
  // Apabila ditemukan operand (variable) maka dituliskan pada hasil
  // Apabila ditemukan operator aritmetik atau tanda kurung (maka dimasukkan ke stack (push))
  // Apabila ditemukan tanda kurung ) maka seluruh stack dikeluarkan dengan pop sampai menemukan kurung buka baru

  // Cara konversi infix to prefix
  // tulis terbalik, dan lakukan sama seperti postfix, lalu balikin lagi kembali

  // Infix = a + b * c + (d * e + f) * g (manusia mengerjakan dengan cara ini)
  // Postfix = a b c * + d e * f + g * + (komputer mengerjakan dengan cara ini)
  // Prefix =  + + a * b c * + * d e f g (komputer mengerjakan dengan cara ini)
 
  return 0;
}