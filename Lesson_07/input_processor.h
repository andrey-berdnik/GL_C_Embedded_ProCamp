#include "types.h"

#ifndef _INPUT_PROCESSOR_
#define _INPUT_PROCESSOR_
typedef void (*INPUT_PROCESSOR_FP)(DataTypeE DataType, char *CpuName, int CpuMark, float Price);
//void readData(table_row *rows, unsigned int size);
void readData(INPUT_PROCESSOR_FP callbackk, unsigned int size);
#endif
