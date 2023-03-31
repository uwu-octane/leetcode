//给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

//你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

//你可以按任意顺序返回答案。
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace  std;

vector<int> twosum01(vector<int> nums, int target){
    int size = nums.size();
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(nums[i]+nums[j]==target) {
                return {i,j};
            }
        }
    }
    return {};
}

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
 }

 int main(){
    vector<int> v = {1,2,3,4};
     vector<int> ans = twoSum(v,3);
     cout << ans[0]<<ans[1]<<ans[2]<<ans[3];
    return 0;
}