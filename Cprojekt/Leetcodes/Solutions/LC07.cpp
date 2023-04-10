//
// Created by 陶挺 on 10.04.23.
//

//Given a signed 32-bit integer x, return x with its digits reversed.
//If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

#include "solution.h"
#include <bitset>
#include <string>
int solution::LC07_reverse(int x){
    std::string num = std::to_string(x);
    std::reverse(num.begin(),num.end());
    int result;
    if(x >= 0){
        return result = std::stod(num) <= INT_MAX ?std::stoi(num):0;
    }else{
        return result = -1 * std::stod(num) >= INT_MIN ?-1* std::stoi(num):0;
    }
}

//avoid using std::string to get better runtime performance
int solution::LC07_reverse_modified(int x){
    int result = 0;
    while (x != 0) {
        // using mod 10 to get the least significant digit of x
        int digit = x % 10;
        //intmax = 2147483647
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) {
            return 0;
        //intmin = -2147483648
        } else if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)) {
            return 0;
        }
        result = result * 10 + digit;
        x /= 10;
    }
    return result;
}