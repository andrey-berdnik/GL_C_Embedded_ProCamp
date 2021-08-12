#include "types.h"

#ifndef _INPUT_PROCESSOR_
#define _INPUT_PROCESSOR_
typedef void (*INPUT_PROCESSOR_FP) (char * pData, unsigned int size);
//void readData(table_row *rows, unsigned int size);
void readData(INPUT_PROCESSOR_FP callbackk);
#endif
