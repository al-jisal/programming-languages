/**
 * File: memory.c -- Analyzes how the basic types are stored in memory
 *                   and how much space they take
 * Author: Desmond Frimpong
 * Project: 01
 * Date: February 19, 2026
*/

#include <stdio.h>
#include <stdlib.h>

int main(int args, char *argv[]){
  unsigned char *ptr;

  printf("char data type\n");
  char character_type = 'u';
  ptr = (unsigned char *)&character_type;
  for (int i = 0; i < sizeof(char); i++){
    printf("%c:\t%02X\n", character_type, ptr[i]);
  }

  printf("\n");
  printf("int data type\n");
  int integer_type = 25;
  ptr = (unsigned char *)&integer_type;
  for (int i = 0; i < sizeof(int); i++){
    printf("%d:\t%02X\n", integer_type, ptr[i]);
  }

  printf("\n");
  printf("short data type\n");
  short short_type = 11;
  ptr = (unsigned char *)&short_type;
  for (int i = 0; i < sizeof(short); i++){
    printf("%hd:\t%02X\n", short_type, ptr[i]);
  }

  printf("\n");
  printf("long data type\n");
  long long_type = 47;
  ptr = (unsigned char *)&long_type;
  for (int i = 0; i < sizeof(long); i++){
    printf("%ld:\t%02X\n", long_type, ptr[i]);
  }

  printf("\n");
  printf("double data type\n");
  double double_type = 9.0;
  ptr = (unsigned char *)&double_type;
  for (int i = 0; i < sizeof(double); i++){
    printf("%lf:\t%02X\n", double_type, ptr[i]);
  }

  printf("\n");
  printf("float data type\n");
  float float_type = 4.0;
  ptr = (unsigned char *)&float_type;
  for (int i = 0; i < sizeof(float); i++){
    printf("%f:\t%02X\n", float_type, ptr[i]);
  }

  return 0;
}