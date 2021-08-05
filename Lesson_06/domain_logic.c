#include "domain_logic.h"
#include "input_processor.h"
#include "output_processor.h"

void createTable()
{
    table_row rows[3];
    //showPrintfHelp();
    readData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));
    printData(rows, (unsigned int)(sizeof(rows) / sizeof(table_row)));
    
}
