#ifndef _TYPES_LINE_
#define _TYPES_LINE_

typedef enum {
 CATALOG_DATA_TYPE=1,
 ORDER_DATA_TYPE
} DataTypeE;

typedef struct
{ 
    char Name[40];
    int Rate;
    float Price;
} catalog_type_row;

typedef struct  
{
    unsigned int OrderNumber;
    char Name[40];
    unsigned int Number;
    float Price;
 } order_type_row;

 typedef union 
 {
     catalog_type_row catalog;
    order_type_row order;
 } table_row_data_u;
 
 typedef struct {
     DataTypeE DataType;
     table_row_data_u Data;
 } table_row;

#endif
