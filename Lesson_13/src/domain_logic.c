#include  <string.h>
#include "domain_logic.h"
#include "input_processor.h"
#include "output_processor.h"

//table_row rows[3];

char buffer[1000];

//typedef void (*INPUT_PROCESSOR_FP)(DataTypeE DataType, char *CpuName, int CpuMark, float Price);
static void writeDataToStore(char * pData, unsigned int size);

void createTable()
{

    //showPrintfHelp();
    //readData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));
    //readData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));

    readData(writeDataToStore);
    printData(buffer);
}

static void writeDataToStore(char * pData, unsigned int size)
{
    static int i = 0;
    memcpy(&buffer[size*i], pData, size);
    i++;
}