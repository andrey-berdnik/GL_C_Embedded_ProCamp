/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int
main ()
{
  printf ("--------------------------------------------------------\n");
  printf ("|%-31s|%10s|%11s|\n","CPU","Rate","Price");
  printf ("--------------------------------------------------------\n");
  printf ("|%-31s| %8i |%11.2f|  \n", "AMD Athlon II N370 Dual-Core", 899, 0);
  printf ("|%-31s| %8i |%11.2f|  \n","AMD Athlon II N370 Dual-Core", 899, 0);
  printf ("|%-31s| %8i |%11.2f|  \n","AMD Athlon II X2 240", 898, 24.5);
  printf ("|%-31s| %8i |%11.2f|  \n","Intel Pentium G620T @ 2.20GHz", 896, 19.99);
  printf ("|%-31s| %8i |%11.2f|  \n","Qualcomm MSM8937", 892, 0);
  printf ("--------------------------------------------------------\n");

  return 0;
}
