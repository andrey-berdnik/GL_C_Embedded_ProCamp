#include <stdio.h>

int main ()
{

struct line {
  char Name[40];
  int Mark;
  float Price;
} lines[3];
  
   printf ("Characters %%c %%c:  %c %c \n", 'a', 65);
   printf ("Decimals %%d %%ld: %d %ld\n", 1977, 650000L);
   printf ("Preceding with blanks %%10d: %10d \n", 1977);
   printf ("Preceding with zeros %%010d: %010d \n", 1977);
   printf ("floats %%4.2f %%+.0e %%E : %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
   printf ("Width trick %%*d: %*d \n", 5, 10);
   printf ("String %%s: %s \n", "A string");
   
   /*
   int day, month, year; 
    scanf("%d/%d/%d", &day, &month, &year);
    printf("%d/%d/%d", day, month, year);
    */
   
  for (int i=0; i<=2; i++) {
    scanf("%s %d %f", lines[i].Name, &lines[i].Mark, &lines[i].Price);
  }

  printf ("------------------------------------------------------\n");
  printf ("|%-31s|%8s|%11s|\n","CPU","Rate","Price");
  printf ("------------------------------------------------------\n");
  for (int i=0; i<=2; i++) {
    printf ("|%-31s|%8i|%11.2f|\n", lines[i].Name, lines[i].Mark, lines[i].Price);
  }
  printf ("------------------------------------------------------\n");

  return 0;
}

