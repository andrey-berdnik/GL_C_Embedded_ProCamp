#include <stdio.h>
/* печать таблицы температур по Фаренгейту и Цельсию для
fahr = 0, 20 ... 300; вариант с плавающей точкой */
int main()
{
 float fahr, celsius;
 int lower, upper, step;
 lower = 0; /* нижняя граница таблицы температур */
 upper = 300; /* верхняя граница */
 step = 20; /* шаг */
 celsius = lower;
 
 printf ("Far\tCel\n");

 while (celsius <= upper) {
 	fahr = (celsius * 9.0/5.0) + 32.0;


 	printf ("%3.0f %6.1f\n", celsius , fahr);
 	celsius = celsius + step;
 }
}