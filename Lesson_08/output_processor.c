#include "output_processor.h"
#include <stdio.h>

void printData(char * pData)
{
  table_row * row = (table_row  *)pData;
  
  if (row->DataType == CATALOG_DATA_TYPE) {
      printf("------------------------------------------------------\n");
      printf("|%-31s|%8s|%11s|\n", "CPU", "Rate", "Price");
      printf("------------------------------------------------------\n");
      for (int i = 1; i <= 3; i++)
      {
        printf("|%-31s|%8i|%11.2f|\n", row->Data.catalog.Name, row->Data.catalog.Rate,
              row->Data.catalog.Price);
        row = (table_row *)pData + i;
      }
      printf("------------------------------------------------------\n");
  } else if (row->DataType == ORDER_DATA_TYPE) {
      printf("-------------------------------------------------------------\n");
      printf("%2s|%-31s|%3s|%10s|%10s\n", "#", "CPU", "Q", "Price", "Total Price");
      printf("-------------------------------------------------------------\n");
      for (int i = 1; i <= 3; i++)
      {
        printf("%2i|%-31s|%3i|%10f|%10f|\n", row->Data.order.OrderNumber, row->Data.order.Name, row->Data.order.Number,
              row->Data.order.Price, row->Data.order.Number*row->Data.order.Price);
        row = (table_row *)pData + i;      
      }
      printf("-------------------------------------------------------------\n");
  } else {
    printf("unknown type\n");
  }
}
