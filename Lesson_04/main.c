#include <stdio.h>

typedef struct
{
  char Name[40];
  int Mark;
  float Price;
} line;

void readData (line *rows, unsigned int size);
void printData (line *rows, unsigned int size);
void showPrintfHelp();

int main ()
{
  line rows[3];
  //showPrintfHelp();
  readData (rows, (unsigned int)(sizeof(rows) / sizeof(line)));
  printData (rows, (unsigned int)(sizeof(rows) / sizeof(line)));

  return 0;
}

void readData (line *rows, unsigned int size)
{ 
  if (rows == NULL || size==0 )
  {return;}

  printf ("------------------------------------------------------\n");
  printf ("Enter CPU title, rate and price using spaces as a delimiter\n");
  printf ("------------------------------------------------------\n");
  for (int i = 0; i <= size - 1; i++)
    { 
      scanf ("%s %d %f", rows[i].Name, &rows[i].Mark, &rows[i].Price);
    }
}

void printData (line *rows, unsigned int size)
{
  if (rows == NULL || size==0 )
  {return;}

  printf ("------------------------------------------------------\n");
  printf ("|%-31s|%8s|%11s|\n", "CPU", "Rate", "Price");
  printf ("------------------------------------------------------\n");
  for (int i = 0; i <= 2; i++)
    {
      printf ("|%-31s|%8i|%11.2f|\n", rows[i].Name, rows[i].Mark,
	      rows[i].Price);
    }
  printf ("------------------------------------------------------\n");
}

void showPrintfHelp() {
  printf ("Characters %%c %%c:  %c %c \n", 'a', 65);
  printf ("Decimals %%d %%ld: %d %ld\n", 1977, 650000L);
  printf ("Preceding with blanks %%10d: %10d \n", 1977);
  printf ("Preceding with zeros %%010d: %010d \n", 1977);
  printf ("floats %%4.2f %%+.0e %%E : %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
  printf ("Width trick %%*d: %*d \n", 5, 10);
  printf ("String %%s: %s \n", "A string");
}
