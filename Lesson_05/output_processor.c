#include "output_processor.h"
#include <stdio.h>

void printData(line *rows, unsigned int size)
{

  printf("------------------------------------------------------\n");
  printf("|%-31s|%8s|%11s|\n", "CPU", "Rate", "Price");
  printf("------------------------------------------------------\n");
  for (int i = 0; i <= 2; i++)
  {
    printf("|%-31s|%8i|%11.2f|\n", rows[i].Name, rows[i].Mark,
           rows[i].Price);
  }
  printf("------------------------------------------------------\n");
}
