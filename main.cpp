//
// Created by user on 03/06/2020.
//




#include "List.h"
int main(){
    char i = 'a';
    int a = 1;
    int b = 9;
    int c = 3;
    int d = 7;
    int e = 5;
    List<int>  l1;
    l1.listInsert(1,&a);
    l1.listInsert(3,&c);
    l1.listInsert(5,&e);
    l1.listInsert(9,&b);
    l1.listInsert(7,&d);
    l1.listGetStart();
    while(l1.listGetCurrent() != nullptr){
        printf("%c . : %d |        ",i, l1.listGetKey());
        l1.listGetNext();
        i++;
    }
    printf(" %d", l1.listGetKey());


    return 0;
};