//
// Created by 陶挺 on 04.04.23.
//
//Given a string s, return the longest palindromic substring in s.
/*A palindromic substring is a contiguous subsequence of characters within a string
 * *that reads the same forward and backward. In other words, a substring is palindromic
 * *if it remains unchanged when its characters are reversed.
 * * For example, consider the string "babad".
 * Some palindromic substrings of this string are "b", "a", "d", "aba", and "bab".
 * Note that single characters are also considered palindromic substrings
 * since they read the same forward and backward.*/

#include "LC05.h"

std::string LC05::longestPalindrome(std::string s) {
        //int substr_size = s.size();
        std::string substr = "";
        for(int substr_size = s.size(); substr_size > 0; substr_size--){
            for (int i = 0; (substr_size - 1 + i) <= s.size() - 1; i++){
                substr = s.substr(i, substr_size);
                std::string temp = substr;
                std::reverse(temp.begin(), temp.end());

                if (std::equal(substr.begin(), substr.end(), temp.begin(), temp.end())){
                    //std::reverse(substr.begin(), substr.end());
                    return substr;
                }
            }
        }
        return substr;
}
