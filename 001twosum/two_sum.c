#include <stdio.h>
#include <stdlib.h>

int main(void){
    int nums[] = {3, 2, 3};
    int size = sizeof(nums)/sizeof(*nums);
    //sizeof(*nums) 等效于sizeof(nums[0])
    printf("the size is %d \n", size);
    return 0;
}