#include "domain_logic.h"
#include "input_processor.h"
#include "output_processor.h"

void createTable()
{
    line rows[3];
    //showPrintfHelp();
    readData(rows, (unsigned int)(sizeof(rows) / sizeof(line)));
    printData(rows, (unsigned int)(sizeof(rows) / sizeof(line)));
}
