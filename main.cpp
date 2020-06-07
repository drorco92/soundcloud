//
// Created by user on 03/06/2020.
//




#include "List.h"
#include "AvlTree.h"
#include <stdlib.h>

class TreeInt{
public:
    const int number;
    TreeInt(int num): number(num){};
    ~TreeInt() = default;
    TreeInt* clone() const {
        TreeInt* temp = new TreeInt(number);
        return temp;
    }
};
class compareFunction{
public:
    int operator()(TreeInt a, TreeInt b){
        return a.number - b.number;
    }
};
typedef int *(compareInt)(int a, int b);
int main(){
    /*char i = 'a';
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
    printf(" %d", l1.listGetKey());*/
    AvlTree<TreeInt, compareFunction> tree;
    tree.insertElement(TreeInt(4));
    tree.insertElement(TreeInt(2));
    tree.insertElement(TreeInt(1));
    tree.insertElement(TreeInt(5));
    tree.insertElement(TreeInt(3));
    tree.insertElement(TreeInt(6));
    tree.removeElement(TreeInt(4));
    tree.insertElement(TreeInt(8));
    tree.insertElement(TreeInt(9));
    tree.insertElement(TreeInt(20));
    tree.removeElement(TreeInt(3));
    tree.insertElement(TreeInt(100));
    tree.removeElement(TreeInt(1));
    tree.printTree();
    printf("degree 5: %d  |",tree.getDegree(5));
    printf("degree 2: %d  |",tree.getDegree(2));
    printf("degree 100: %d  |",tree.getDegree(100));
    printf("degree 8: %d  |",tree.getDegree(8));
    printf("degree 6: %d  |",tree.getDegree(6));
    printf("degree 9: %d  |",tree.getDegree(9));
    printf("degree 20: %d  |",tree.getDegree(20));

    return 0;
};