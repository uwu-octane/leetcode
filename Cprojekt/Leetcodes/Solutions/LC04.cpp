//
// Created by 陶挺 on 02.04.23.

//Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
//The overall run time complexity should be O(log (m+n)).

//
#include <vector>
#include "../solution.h"
#include <iostream>
#include <algorithm>

class LC04: solution {
public:
    //binary search
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2){
        //sort 2 Arrays so that  with smaller size at the first place
        if(nums1.size() > nums2.size()){
            return findMedianSortedArrays(nums2, nums1);
        }

        //get size of the 2 Arrays to calculate the position of partition
        int x = nums1.size();
        int y = nums2.size();

        // to set the range, end will be modified if the partition is not right
        int begin = 0;
        int end = x;

        while(begin <= end){
            //there we make 2 partitions X and Y on nums1,2.
            //partitionX, Y divide nums1 and nums2 into left and right parts respectively
            //Left part of nums1 + left part of nums2 = Left of Partition
            //Right part of nums1 + right part of nums2 = Right of Partition

            int partitionX = (begin + end) / 2;
            //here by adding 1 to (x + y) we ensure that in the case of odd total length (x + y)
            //on the left side of partition we have one more element than on the right side
            //the median will be the maximum element on the left side of the partitions.
            int partitionY = (x + y + 1) / 2 - partitionX;


            int maxLeftX = (partitionX == 0 ) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == x ) ? INT_MAX : nums1[partitionX];

            int maxLeftY = (partitionY == 0 ) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == y ) ? INT_MAX : nums2[partitionY];

            //check if the partition is right to meet the condition
            //total Array = [part of LeftX + LeftY | part of RightX + RightY]
            //LeftX already smaller than RightX and LeftY smaller than RightY
            //so still have to check maxLeftX <= minRightY and maxLeftY <= minRightX
            if(maxLeftX <= minRightY && maxLeftY <= minRightX) {
                //condition met, check total length even or odd
                //even
                if ((x + y) % 2 == 0 ){
                    return (double)(std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2;
                } else {
                    return (double)std::max(maxLeftX, maxLeftY);
                }
            //adjust the partition
            }else if(maxLeftX > minRightY) {
                //adjust end
                end = partitionX - 1;
            }else {
                //adjust begin
                begin = partitionX + 1;
            }
        }
        throw std::runtime_error("Could not find the correct answer.");
    }
};
