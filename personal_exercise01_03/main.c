/**
 ** Beispielprogram (c) 2011 Steffen Kaiser
 **
 **/

/* Headerdatei für printf() notwendig */
#include <stdio.h>

/* Programmstart: keine Kommandozeilenargumente */
int main(void) {
  int a;      /* Variable */
  int b = 1;  /* Variable #2 mit Initialwert */

  a = 2;      /* Zuweisung */
  b += a;     /* kurz für b = b + a */

  printf("Ergebnis von a + b = %u, mit a = %u und b = %u\n", a+b, a, b);

  return 0;   /* signalisiert dem Betriebssystem: alles in Ordnung */
}