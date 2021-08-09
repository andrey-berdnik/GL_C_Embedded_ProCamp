#include <stdio.h>
#include "types.h"
#include "input_processor.h"


void readData(INPUT_PROCESSOR_FP callback, unsigned int size)
{

#define TABLE_TYPE 1

#if TABLE_TYPE == 1
    printf("------------------------------------------------------\n");
    printf("Enter CPU title, rate and price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");

    char Name[40];
    int Rate;
    float Price;

    for (int i = 0; i <= size - 1; i++)
    {
        scanf("%s %d %f", Name, &Rate, &Price);
        callback(CATALOG_DATA_TYPE,Name,Rate,Price);
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