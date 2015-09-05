#include <tgmath.h> //pow
#include <ctype.h> //isdigit
#include "HexToRGB.h"
#include "../dbg.h"

/**
 * @param hexString
 * @return Hex in Decimal format
 */
int GameEngine_Util_ConvertHexCharToDec(const char *hexString) {
    int total = 0;

    for (int i = strlen(hexString), ex = 0, tmp = 0; i > 0; i--, ex++) {
        tmp = GameEngine_Util_ConvertHexStringToDec(&hexString[i - 1]) * pow(16.0, ex);
        check(tmp >= 0, "Error converting hex");

        total += tmp;
    }

    return total;
    
error:
    return -1;
}

/**
 * @param hexChar
 * @return Decimal value of hex or -1 in case of error
 */
int GameEngine_Util_ConvertHexStringToDec(const char *hexChar) {
    switch (*hexChar) {
        case 'A':
        case 'a':
            return 10;
            break;
        case 'B':
        case 'b':
            return 11;
            break;
        case 'C':
        case 'c':
            return 12;
            break;
        case 'D':
        case 'd':
            return 13;
            break;
        case 'E':
        case 'e':
            return 14;
            break;
        case 'F':
        case 'f':
            return 15;
            break;
        default:
        {
            if (isdigit(*hexChar)) {
                return (*hexChar - '0');
            }
        }
    }

    return -1;
}

