#include "output_processor.h"
#include <stdio.h>

void printData(table_row *rows, unsigned int size)
{

  if (rows[0].DataType == CATALOG_DATA_TYPE) {
      printf("------------------------------------------------------\n");
      printf("|%-31s|%8s|%11s|\n", "CPU", "Rate", "Price");
      printf("------------------------------------------------------\n");
      for (int i = 0; i <= 2; i++)
      {
        printf("|%-31s|%8i|%11.2f|\n", rows[i].Data.catalog.Name, rows[i].Data.catalog.Rate,
              rows[i].Data.catalog.Price);
      }
      printf("------------------------------------------------------\n");
  } else if (rows[0].DataType == ORDER_DATA_TYPE) {
      printf("-------------------------------------------------------------\n");
      printf("%2s|%-31s|%3s|%10s|%10s\n", "#", "CPU", "Q", "Price", "Total Price");
      printf("-------------------------------------------------------------\n");
      for (int i = 0; i <= 2; i++)
      {
        printf("%2i|%-31s|%3i|%10f|%10f|\n", rows[i].Data.order.OrderNumber, rows[i].Data.order.Name, rows[i].Data.order.Number,
              rows[i].Data.order.Price, rows[i].Data.order.Number*rows[i].Data.order.Price);
      }
      printf("-------------------------------------------------------------\n");
  } else {
    printf("unknown type\n");
  }
}
