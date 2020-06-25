// Copyright (c) 2020 Anwar Mikati
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// FORMATS MASKS FOR READING THE BITS
typedef enum format
{
   BIN = 0x1,
   OCT = 0x7,
   HEX = 0xF
} FORMAT;
// ASCII VALUES FROM 0 TO F
const char HEX_CHAR_ANALOGS[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70};

/* Read  C long casted numbers to  BINARY, OCTAL, HEX String
No conversion calculus - Just read the numbers as they are on the user machine
Warning : No type error checking if an input is a too large value for long type. Will 
always return what you get. On negatives return the 2 complement as it is
*/
char *ToBinFormat(long num, FORMAT format)
{
   // Size of the long type
   int bits = sizeof(long) * __CHAR_BIT__;
   // Step reading value - inited @ 1 for BIN format
   int step = 1;
   if (format == OCT)
   {
      step = 3;
   }
   else if (format == HEX)
   {
      step = 4;
   }

   // Length of the result string
   const int max_len = bits / step + bits % step;

   char *ptr_arr;
   // max_len + 1 string with 0 char at the end
   ptr_arr = (char *)calloc(max_len + 1, sizeof(char));
   int i = max_len;
   // Reading the bits step by step and pushing their ASCII symbols in the char array
   while (i--)
   {
      ptr_arr[i] = HEX_CHAR_ANALOGS[num & format];
      num = num >> step;
   }

   return (char *)ptr_arr;
}

int main()
{

   long a;
   char *result;

   printf("Input any long integer\n");
   scanf("%ld", &a);

   result = ToBinFormat(a, BIN);
   printf("BIN %s\n", result);
   free(result);

   result = ToBinFormat(a, OCT);
   printf("OCT %s\n", result);
   free(result);

   result = ToBinFormat(a, HEX);
   printf("HEX %s\n", result);
   free(result);

   printf("***********************ON SOME LIMIT VALUES**************************\n");
   printf("LONG_MAX    :   %ld\n", (long)LONG_MAX);
   result = ToBinFormat(LONG_MAX, BIN);
   printf("BIN %s\n", result);
   free(result);
   result = ToBinFormat(LONG_MAX, OCT);
   printf("OCT %s\n", result);
   free(result);
   result = ToBinFormat(LONG_MAX, HEX);
   printf("HEX %s\n", result);
   free(result);

   printf("LONG_MAX    :   %ld\n", (long)LONG_MIN);
   result = ToBinFormat(LONG_MIN, BIN);
   printf("BIN %s\n", result);
   free(result);
   result = ToBinFormat(LONG_MIN, OCT);
   printf("OCT %s\n", result);
   free(result);
   result = ToBinFormat(LONG_MIN, HEX);
   printf("HEX %s\n", result);
   free(result);

   printf("ULONG_MAX   :   %lu\n", (long)ULONG_MAX);
   result = ToBinFormat(ULONG_MAX, BIN);
   printf("BIN %s\n", result);
   free(result);
   result = ToBinFormat(ULONG_MAX, OCT);
   printf("OCT %s\n", result);
   free(result);
   result = ToBinFormat(ULONG_MAX, HEX);
   printf("HEX %s\n", result);
   free(result);

   return 0;
}