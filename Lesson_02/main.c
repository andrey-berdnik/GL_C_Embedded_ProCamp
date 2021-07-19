#include <stdio.h>

int main ()
{
  printf ("------------------------------------------------------\n");
  printf ("|%-31s|%8s|%11s|\n","CPU","Rate","Price");
  printf ("------------------------------------------------------\n");
  printf ("|%-31s|%8i|%11.2f|\n", "AMD Athlon II N370 Dual-Core", 899, 0.0);
  printf ("|%-31s|%8i|%11.2f|\n", "AMD Athlon II N550", 852, 0.0);
  printf ("|%-31s|%8i|%11.2f|\n", "AMD Athlon II X2 240", 898, 24.5);
  printf ("|%-31s|%8i|%11.2f|\n", "Intel Pentium G620T @ 2.20GHz", 896, 19.99);
  printf ("|%-31s|%8i|%11.2f|\n","Qualcomm MSM8937", 892, 0.0);
  printf ("------------------------------------------------------\n");


  printf ("------------------------------------------------------\n");
  printf ("|%-12s%-12s%-12s%-12s%-12s%-12s\n","%d","%o","%x","%u","%c","%f");
  printf ("|%-12s%-12s%-12s%-12s%-12s%-12s\n","Signed ","Unsigned","Unsigned","Unsigned","Character","Decimal");
  printf ("|%-12s%-12s%-12s%-12s%-12s%-12s\n","decimal ","octal","hexadecimal","decimal","","floating");
  printf ("|%-12s%-12s%-12s%-12s%-12s%-12s\n","integer","","integer","integer","","point");
  printf ("------------------------------------------------------\n");
  
float f=0;
  for (int i=50; i<=60;i++){
      f+=0.5;
    printf("%12d%12o%12x%12u%12c%12f\n",i,i,i,i,i,f);
  }


   printf ("Characters %%c %%c:  %c %c \n", 'a', 65);
   printf ("Decimals %%d %%ld: %d %ld\n", 1977, 650000L);
   printf ("Preceding with blanks %%10d: %10d \n", 1977);
   printf ("Preceding with zeros %%010d: %010d \n", 1977);
   printf ("floats %%4.2f %%+.0e %%E : %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
   printf ("Width trick %%*d: %*d \n", 5, 10);
   printf ("String %%s: %s \n", "A string");
   
   int day, month, year; /* день, месяц, год */
    scanf("%d/%d/%d", &day, &month, &year);
    printf("%d/%d/%d", day, month, year);

   
  return 0;
}