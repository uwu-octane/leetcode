//
// Created by 陶挺 on 11.04.23.
//

/*mplement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

Read in and ignore any leading whitespace.
Check if the next character (if not already at the end of the string) is '-' or '+'.
Read this character in if it is either. This determines if the final result is negative or positive respectively.
Assume the result is positive if neither is present.
Read in next the characters until the next non-digit character or the end of the input is reached.
The rest of the string is ignored.
Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32).
If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
If the integer is out of the 32-bit signed integer range [-231, 231 - 1],
then clamp the integer so that it remains in the range.
Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1 should be clamped to 231 - 1.
Return the integer as the final result.
Note:

Only the space character ' ' is considered a whitespace character.
Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.*/


#include "solution.h"
#include <iostream>
int solution::LC08_myAtoi(std::string s) {
    int sign = 1;
    int result = 0;
    bool isSigned = false;
    for(char c: s){
        //std::cout<<c<<std::endl;
        if(c == ' ' && result == 0){
            if(isSigned){
                return 0;
            }
            continue;
        }else if (c == ' ' && result > 0){
            break;
        }

        if(c == 45 && result == 0){
            if(isSigned){
                return 0;
            }
            sign = -1;
            isSigned = true;
            continue;
        }
        if(c == 43 && result == 0){
            if(isSigned){
                return 0;
            }
            sign = 1;
            isSigned = true;
            continue;
        }
        if( 48<= c && c <= 57){
            // for case like 77+....
            if(!isSigned){
                isSigned = true;
            }
            if (sign == 1 && (result > INT_MAX / 10 || (result == INT_MAX / 10 && c >= 55))){
                return INT_MAX;
            } else if (sign == -1 && ( result > INT_MAX / 10 || ( result == INT_MAX / 10 &&  c >= 56))){
                return  INT_MIN;
            }
            result = result * 10 + (c - 48);
        }else {
            break;
        }
    }
    return result * sign;
}