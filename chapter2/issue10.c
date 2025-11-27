/*
 * issue10.c
 * 已知长度为n的线性表A采用顺序存储结构，请写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，
 * 该算法可删除线性表中所有值为item的数据元素。
 *
 * LNode node;        // 声明一个节点
 * LinkList head;     // 声明一个链表头指针，等价于 LNode *head;
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
//---------单链表的存储结构-------------
typedef int ElemType;  // 假设链表存储整型数据

// 传入顺序表A以及长度n
void delete(ElemType A[], int *n, ElemType item) {
    // A是有n个元素的1维数组，删除所有值为item的元素
    // 设置数组低、高端指针
    int i = 0;
    int j = *n;
    while (i < j) {
        // 如果当前元素不等于item，左移动指针
        while (i<j && A[i] != item) {
            i++;
        }
        if (i<j) {
            // 如果当前元素等于item，右移动指针
            while (i<j && A[j-1]==item) {
                j--;
            }
        }
        if (i<j) {
            // 先复制后一个元素到当前位置，再左移指针
            A[i++] = A[j--];
        }
    }
    *n = i; // 更新数组长度
}

// 打印数组元素
void printArray(ElemType A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");

    // 创建测试数组
    ElemType A[] = {1, 3, 5, 3, 7, 3, 9, 3, 11, 3};
    int n = sizeof(A) / sizeof(A[0]);
    ElemType item = 3;

    printf("原始数组: ");
    printArray(A, n);

    printf("删除元素 %d 后: ", item);
    delete(A, &n, item);
    printArray(A, n);
    
    return 0;
}