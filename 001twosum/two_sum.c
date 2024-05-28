#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 
 * 
 * @param nums 
 * @param numsSize 
 * @param target 
 * @param returnSize 
 * @return int* 
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j;
    int *result = (int*)malloc(2 * sizeof(int)); /* < 存储一个两个int的指针*/
    *returnSize = 2;
    for(i=0; i < numsSize; i++){
        for(j=i+1; j < numsSize; j++){
            if(nums[i] + nums[j] == target){
                result[0] = i;
                result[1] = j;
            }
        }  
    }
    
    return result;
}

int main(void){
    int nums[] = {3, 2, 3};
    int size = sizeof(nums)/sizeof(*nums);
    //sizeof(*nums) 等效于sizeof(nums[0])
    printf("the size is %d \n", size);
    int target = 6;
    int count = 0;
    int *indexes = twoSum(nums, size, target, &count);
    if(indexes != NULL){
        printf("%d %d\n", indexes[0], indexes[1]);
    }else {
        printf("Not found\n");
    }

    
    return 0;
}