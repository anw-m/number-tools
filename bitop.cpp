// Copyright (c) 2020 Anwar Mikati
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <cstdlib>
#include <iostream>
#include <climits>

#define DISPLAY_LINE(line) (std::cout << line << std::endl)
// FORMATS MASK FOR READING THE LEAST BITS
enum FORMAT
{
    BIN = 0x1,
    OCT = 0x7,
    HEX = 0xF
};

// ASCII VALUES FOR 0 TO F
const char HEX_CHAR_ANALOGS[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70};

/* Read any C integer type (from char to long) to a BINARY, OCTAL, HEX String
No conversion calculus - Just read the numbers as they are on the user machine
Warning : No type error checking if you use a too small T type for your number. Will 
always return what you get.
*/
template <typename T>
char *ToBinFormat(T num, FORMAT format)
{
    // Size of the type
    int bits = sizeof(T) * __CHAR_BIT__;
    // Reading step a each iteration : 1 Binary - 3 Octal - 4 Hexadecimal
    int step = 1;
    if (format == FORMAT::OCT)
    {
        step = 3;
    }
    else if (format == FORMAT::HEX)
    {
        step = 4;
    }
    // Number of iterations : bits/step + 1 in case of Octal
    int i = bits / step;
    int remain = bits % step;
    int j = remain ? 1 : 0;
    const int max_len = i + j;

    char *ptr_arr;
    // max_len + 1 string with 0 char at the end
    ptr_arr = (char *)calloc(max_len + 1, sizeof(char));

    // Reading the bits step by step and pushing their ASCII analogs in the result string
    int l = i;
    while (l--)
    {
        ptr_arr[j + l] = HEX_CHAR_ANALOGS[num & format];

        num = num >> step;
    }
    // Program ends here for BIN + HEX cases
    if (!remain)
    {
        return (char *)ptr_arr;
    }

    //Last read on remain bits for Octal

    ptr_arr[0] = HEX_CHAR_ANALOGS[num & (format >> (step - remain))];

    return (char *)ptr_arr;
}

int main()
{
    char *result;
    long a;
    DISPLAY_LINE("Input any integer");
    std::cin >> a;

    DISPLAY_LINE("***********************CASTED TO char**************************");

    result = ToBinFormat<char>(a, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);

    result = ToBinFormat<char>(a, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);

    result = ToBinFormat<char>(a, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);
    DISPLAY_LINE("***********************CASTED TO int**************************");

    result = ToBinFormat<int>(a, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);
    result = ToBinFormat<int>(a, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);
    result = ToBinFormat<int>(a, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);
    DISPLAY_LINE("***********************CASTED TO long**************************");

    result = ToBinFormat<long>(a, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);
    result = ToBinFormat<long>(a, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);
    result = ToBinFormat<long>(a, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);

    DISPLAY_LINE("***********************ON SOME LIMIT VALUES (NO CAST) **************************");
    DISPLAY_LINE("LONG_MAX    :   " << (long)LONG_MAX);
    result = ToBinFormat(LONG_MAX, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);
    result = ToBinFormat(LONG_MAX, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);
    result = ToBinFormat(LONG_MAX, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);

    DISPLAY_LINE("LONG_MIN    :   " << (long)LONG_MIN);
    result = ToBinFormat(LONG_MIN, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);

    result = ToBinFormat(LONG_MIN, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);

    result = ToBinFormat(LONG_MIN, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);

    DISPLAY_LINE("ULONG_MAX   :   " << (unsigned long)ULONG_MAX);
    result = ToBinFormat(ULONG_MAX, BIN);
    DISPLAY_LINE("BIN " << result);
    free(result);
    result = ToBinFormat(ULONG_MAX, OCT);
    DISPLAY_LINE("OCT " << result);
    free(result);
    result = ToBinFormat(ULONG_MAX, HEX);
    DISPLAY_LINE("HEX " << result);
    free(result);

    return 0;
}
/* OUTPUT SAMPLE

Input any integer
250
***********************CASTED TO char**************************
BIN 11111010
OCT 372
HEX FA
***********************CASTED TO int**************************
BIN 00000000000000000000000011111010
OCT 00000000372
HEX 000000FA
***********************CASTED TO long**************************
BIN 0000000000000000000000000000000000000000000000000000000011111010
OCT 0000000000000000000372
HEX 00000000000000FA
***********************ON SOME LIMIT VALUES (NO CAST) **************************
LONG_MAX    :   9223372036854775807
BIN 0111111111111111111111111111111111111111111111111111111111111111
OCT 0777777777777777777777
HEX 7FFFFFFFFFFFFFFF
LONG_MIN    :   -9223372036854775808
BIN 1000000000000000000000000000000000000000000000000000000000000000
OCT 1000000000000000000000
HEX 8000000000000000
ULONG_MAX   :   18446744073709551615
BIN 1111111111111111111111111111111111111111111111111111111111111111
OCT 1777777777777777777777
HEX FFFFFFFFFFFFFFFF

 */