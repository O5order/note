#include <stdio.h>
int main(){
	int nums[20];
	int target, i, j;
	printf("enter '0' to break ");
	for(i=0;i<20;i++){
		scanf("%d", &nums[i]);
		if(nums[i]==0)
			break;
	}
	scanf("%d", &target);
	for(i=0;i<19;i++){
		for(j=i+1;j<20;j++){
			if(nums[i]+nums[j]==target){
				printf("%d %d", i, j);
				break;	
			}
		}
	}
	return 0;
}
//ps:该算法本身不难，但是优化过程我想了很久没有写出来，我想到用二分法和递归函数去优化算法，可惜失败了，目前我还没有找出错误。。。 
