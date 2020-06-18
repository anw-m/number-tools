// Copyright (c) 2020 Anwar Mikati
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char HEX_CHAR_ANALOGS[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70};

/* max positive size for the num input 32 bits = 4294967295
   @return a binary string
*/
char *ToBin(long num)
{

   // fixing shift operations on negative numbers -
   num = num & 0xFFFFFFFF;
   /* 
      Each loop read 1 bit and left-concat the ASCII char analogs in a dynamic char array.
      The looping ends when the 0 value is reached
    */
   int len = 0;
   const size_t SIZE = sizeof(char);
   char *final = NULL;
   do
   {
      char *arr = malloc(SIZE * (len + 1));
      char item[] = {HEX_CHAR_ANALOGS[num & 0x1]};

      memcpy(arr, item, SIZE);

      if (len)
      {
         memcpy(arr + SIZE, final, len * SIZE);
      }
      final = arr;
      len++;

   } while (num = num >> 1);

   return (char *)final;
}

/* max positive size for the num input 32 bits = 4294967295
   @return a headecimal string
*/

char *ToHex(long num)
{

   // fixing shift operations on negative numbers
   num = num & 0xFFFFFFFF;
   /* 
      Each loop read 4 bit and left-concat the ASCII char analogs in a dynamic char array.      
      The loop ends when the 0 value is reached
    */
   int len = 0;
   const size_t SIZE = sizeof(char);
   char *final = NULL;
   do
   {
      char *arr = malloc(SIZE * (len + 1));
      char item[] = {HEX_CHAR_ANALOGS[num & 0xF]};

      memcpy(arr, item, SIZE);

      if (len)
      {
         memcpy(arr + SIZE, final, len * SIZE);
      }
      final = arr;
      len++;

   } while (num = num >> 4);

   return (char *)final;
}

/* max positive size for the num input 32 bits = 4294967295
   @return an octal string
*/
char *ToOct(long num)
{

   // fixing shift operations on negative numbers
   num = num & 0xFFFFFFFF;
   /*       
      Each loop read 3 bit and left-concat the ASCII char analogs in a dynamic char array.
      The loop ends when the 0 value is reached
    */
   int len = 0;
   const size_t SIZE = sizeof(char);
   char *final = NULL;
   do
   {
      char *arr = malloc(SIZE * (len + 1));
      char item[] = {HEX_CHAR_ANALOGS[num & 0x7]};

      memcpy(arr, item, SIZE);

      if (len)
      {
         memcpy(arr + SIZE, final, len * SIZE);
      }
      final = arr;
      len++;

   } while (num = num >> 3);

   return (char *)final;
}

int main()
{

   long a;

   printf("Input any long integer\n");
   scanf("%ld", &a);

   printf("*************************************************\n");

   printf("binary, octals, hex output of %ld are  %s - %s - %s\n", a, ToBin(a), ToOct(a), ToHex(a));

   return 0;
}