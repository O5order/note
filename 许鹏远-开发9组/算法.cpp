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
//ps:���㷨�����ѣ������Ż����������˺ܾ�û��д���������뵽�ö��ַ��͵ݹ麯��ȥ�Ż��㷨����ϧʧ���ˣ�Ŀǰ�һ�û���ҳ����󡣡��� 
