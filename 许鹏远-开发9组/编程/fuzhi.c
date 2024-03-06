#include<stdio.h>
int main(){
    int id, amount = 0;
    do {
        scanf("%d", &id);
        switch (id) {
            case 1: amount = amount + 60; break;
            case 2: amount = amount + 70; break;
            case 3: amount = amount + 90; break;
            case 4: amount = amount + 80; break;
        }
    }while (id != 0);
    printf("total is %d", amount);
    return 0;
}
