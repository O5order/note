/*软件2310许鹏远-2023005269*/

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
    printf("请输入一个字符串：");
    scanf("%s", str);
    if (is_palindrome(str))
	{
        printf("这是一个回文字符串。");
    }
	else
	{
        printf("这不是一个回文字符串。");
    }
    return 0;
}

