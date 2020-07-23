// Copyright (c) 2020 Anwar Mikati
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// CONVERSION TABLE BASED ON ASCII CHAR VALUE. THE INDEX IS THE INTEGER TO CONVERT.
// GOES FROM 0 TO 85 - CASE SENSITIVE (a!=A)
const char ASCII_CHAR_ANALOGS[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69,
                                   70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
                                   85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101, 102, 103, 104,
                                   105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118,
                                   119, 120, 121, 122, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61,
                                   62, 63, 64, 91, 92, 93, 94, 95, 96, 123, 124, 125, 126};
const size_t SIZE = sizeof(char);
// CONVERTS ANY BASE 10 NUMBER TO (ALMOST) ANY ARBITRARY base STRING AND RETURN IT
// MAX BASE LIMITED BY THE CONVERSION TABLE SIZE
// See https://github.com/anw-m/number-tools/wiki/ToAnyBase for more details
char *ToAnyBase(unsigned long num, unsigned long base)
{
    int len = 0;

    char *final = NULL;

    do
    {

        char *arr = malloc(SIZE * (len + 1));

        memcpy(arr, (char[]){ASCII_CHAR_ANALOGS[num % base]}, SIZE);
        if (len)
        {
            // CONCATENATION OF THE NEW CHAR arr WITH THE final ARRAY
            memcpy(arr + SIZE, final, len * SIZE);
        }
        final = arr;

        len++;

    } while (num = num / base);
    return (char *) final;
}

int main()
{
    int count = sizeof(ASCII_CHAR_ANALOGS) / SIZE;
    printf("CURRENT CONVERSION TABLE - BASE CAN GO TO %d\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%d : %s\n", i, (char[]){ASCII_CHAR_ANALOGS[i]});
    }

    unsigned long num;
    unsigned long base;
    printf("INPUT ANY POSITIVE NUMBER FOR CONVERSION\n");
    scanf("%ld", &num);

    printf("INPUT ANY BASE > 1 or <= %d FOR CONVERSION\n", count);
    scanf("%ld", &base);
    if (base < 2 || base > count)
    {
        printf("INVALID INPUT");
        return 1;
    }
    char *result;

    result = ToAnyBase(num, base);
    printf("%s\n", result);
    free(result);

    return 0;
}
