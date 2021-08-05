#include <stdio.h>
#include "types.h"
#include "input_processor.h"

void readData(table_row *rows, unsigned int size)
{

#define TABLE_TYPE 2

#if TABLE_TYPE == 1
    printf("------------------------------------------------------\n");
    printf("Enter CPU title, rate and price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i <= size - 1; i++)
    {
        scanf("%s %d %f", rows[i].Data.catalog.Name, &rows[i].Data.catalog.Rate, &rows[i].Data.catalog.Price);
        rows[i].DataType = CATALOG_DATA_TYPE;
    }
#endif

#if TABLE_TYPE == 2
    printf("------------------------------------------------------\n");
    printf("Enter CPU, Q, Price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");
    for (unsigned  int i = 0; i <= size - 1; i++)
    {
        scanf("%s %i %f", rows[i].Data.order.Name, &rows[i].Data.order.Number, &rows[i].Data.order.Price);
        rows[i].DataType = ORDER_DATA_TYPE;
        rows[i].Data.order.OrderNumber = i;
        
    }
#endif


}