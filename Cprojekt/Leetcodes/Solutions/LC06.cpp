//
// Created by 陶挺 on 07.04.23.
//

#include "LC06.h"
#include <vector>

std::string LC06::convert(std::string s, int numRows) {
    if(s.size() == 0){
        return "invalid input";
    } else if (numRows == 1 || numRows >= s.size()){
        return s;
    }

    //by using 2 dimensions matrix we have to use resize avoid segmentation fault
    std::vector<std::vector<std::string>> matrix(numRows);
    for(int i = 0; i < numRows; i++){
        matrix[i].resize(s.size());
    }

    int row = 0;
    int column = 0;
    bool goback = false;

    for(auto character:s){
        matrix[row][column]=character;
        if(row == 0){
            goback = false;
        }else if (row == numRows -1){
            goback = true;
        }

        if(goback){
            row--;
            column++;
        }else {
            row++;
        }

    }
    std::string result;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j< matrix[i].size(); j++){
            result += matrix[i][j];
        }
    }
    return result;
}
