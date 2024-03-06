#include <stdio.h>
int main(){
	int nums[20];
	int target, i, j;
	printf("enter '0' to break ");
	for(i=0;i<20;i++){
		scanf("%d", &nums[i]);
		if(nums[i]==0)
			break;        //数据输入 
	}
	scanf("%d", &target);
	erfen(nums,0,i,target);      //二分法函数调用 
	return 0;
}

	
int erfen(int *nums, int left, int right, int target){
	int medium=(left + right)/2;
	if (nums[medium]+nums[medium+1]>target){
		right=medium+1;
		erfen(nums,left,right,target);
	}                                                     //函数递归实现不断二分 
	if (nums[medium]+nums[medium+1]<target){
		left=medium;
		erfen(nums,left,right,target);
	}
	if (nums[medium]+nums[medium+1]==target){
		printf("%d %d", medium, medium+1);
	}
}
