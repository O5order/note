/*���2310����Զ-2023005269*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include <stdio.h>
#include <string.h>

int is_palindrome(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return 0;
        }
         left++;
        right--;
    }
    return 1;
}

int main() {
    char str[100];
    printf("������һ���ַ�����");
    scanf("%s", str);
    if (is_palindrome(str))
	{
        printf("����һ�������ַ�����");
    }
	else
	{
        printf("�ⲻ��һ�������ַ�����");
    }
    return 0;
}

