#include <stdio.h>
#include "types.h"
#include "input_processor.h"


void readData(INPUT_PROCESSOR_FP callback)
{

#define TABLE_TYPE 1

#if TABLE_TYPE == 1
    printf("------------------------------------------------------\n");
    printf("Enter CPU title, rate and price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");

    table_row row_tmp;

    row_tmp.DataType = CATALOG_DATA_TYPE;

    for (int i = 0; i <= 2 ; i++)
    {
        scanf("%s %d %f", row_tmp.Data.catalog.Name, &row_tmp.Data.catalog.Rate, &row_tmp.Data.catalog.Price);
        callback((char *)&row_tmp, sizeof(table_row));
        //rows[i].DataType = CATALOG_DATA_TYPE;
    }
#endif

#if TABLE_TYPE == 2
    printf("------------------------------------------------------\n");
    printf("Enter CPU, Q, Price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");
    for (unsigned int i = 0; i <= size - 1; i++)
    {
        scanf("%s %i %f", rows[i].Data.order.Name, &rows[i].Data.order.Number, &rows[i].Data.order.Price);
        rows[i].DataType = ORDER_DATA_TYPE;
        rows[i].Data.order.OrderNumber = i;
    }
#endif
}