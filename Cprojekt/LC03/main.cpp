#include <iostream>
#include <string>

//Given a string s, find the length of the longest substring without repeating characters.

class Solution {
public:
    // using approach of sliding window to get the substr without repeating
    std::string substr = "";
    int max_length = 0;
    int sliding_window_start = 0;
    int sliding_window_end = 0;

    // find the position of a given char in str1, if not found return -1
    int get_index(std::string str1, char ch){
        for(int i = 0; i < str1.size(); i++ ){
            if(str1[i] == ch){
                return i;
            }
        }
        return -1;
    }
    int lengthOfLongestSubstring(std::string s){
        while ( sliding_window_end < s.length()) {
            //if the current char not in substr, add it to the substr, and update size
            std::cout << "------------------------" << std::endl;
            std::cout << "end: " << sliding_window_end << std::endl;
            if(get_index(substr,s[sliding_window_end]) == -1){
                substr += s[sliding_window_end];
                std::cout << "substr: " << substr << std::endl;

                max_length = max_length > substr.size() ? max_length : substr.size();
            } else {
                // if the current char is in substr, we move the start_pointer to the position next to the
                // repeated char as new start position, so we may loop all the substrs without repeating chars

                //NOTICE : Very important that there we have to add the original start position value cause we have
                //updated the substr, the start value gaven from get_index is not the right position in s
                // and we update substr from s not from substr itself
                sliding_window_start += get_index(substr,s[sliding_window_end]) + 1;
                std::cout << "start: " << sliding_window_start << std::endl;

                substr = s.substr(sliding_window_start,sliding_window_end - sliding_window_start + 1);
                std::cout << "substr: " << substr << std::endl;
            }
            sliding_window_end +=1;
        }
        return max_length;
    }
};

int main() {
    std::string s =  "bbtablud";
    Solution solution;
    std::cout << solution.lengthOfLongestSubstring(s) << std::endl;
    return 0;
}
