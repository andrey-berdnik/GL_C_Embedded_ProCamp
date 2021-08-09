#include  <string.h>
#include "domain_logic.h"
#include "input_processor.h"
#include "output_processor.h"

table_row rows[3];

typedef void (*INPUT_PROCESSOR_FP)(DataTypeE DataType, char *CpuName, int CpuMark, float Price);
static void writeData(DataTypeE DataType, char *CpuName, int CpuMark, float Price);

void createTable()
{

    //showPrintfHelp();
    //readData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));
    //readData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));

    readData(writeData, (unsigned int)(sizeof(rows) / sizeof(table_row)));
    printData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));
}

static void writeData(DataTypeE DataType, char *CpuName, int CpuMark, float Price)
{
    static int i = 0;
    switch (DataType)
    {
    case CATALOG_DATA_TYPE:
        rows[i].Data.catalog.Price = Price;
        rows[i].Data.catalog.Rate = CpuMark;
        rows[i].DataType = CATALOG_DATA_TYPE;
        memcpy( &rows[i].Data.catalog.Name, CpuName, 40);
        break;

    default:
        break;
    }
    i++;
}