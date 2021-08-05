#include <stdio.h>
#include "types.h"
#include "input_processor.h"

void readData(line *rows, unsigned int size)
{

    printf("------------------------------------------------------\n");
    printf("Enter CPU title, rate and price using spaces as a delimiter\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i <= size - 1; i++)
    {
        scanf("%s %d %f", rows[i].Name, &rows[i].Mark, &rows[i].Price);
    }
}