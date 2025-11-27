/*
 * issue4.c
 * 已知两个链表A和B分别表示两个集合，其元素递增排列。
 * 请设计算法求出两个集合A和B的差集（即仅由在A中出现而不在B中出现的元素所构成的集合），
 * 并以同样的形式存储，同时返回该集合的元素个数。
 *
 * LNode node;        // 声明一个节点
 * LinkList head;     // 声明一个链表头指针，等价于 LNode *head;
 */

#include <stdio.h>
#include <stdlib.h>
//---------单链表的存储结构-------------
typedef int ElemType;  // 假设链表存储整型数据

typedef struct LNode {
    ElemType data;     // 数据域
    struct LNode* next;  // 指针域
    // struct LNode *prior; // 前向指针域
} LNode, *LinkList;

// 创建链表节点
LinkList CreateNode(ElemType data) {
    LinkList node = (LinkList)malloc(sizeof(LNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// 打印链表
void PrintList(LinkList head) {
    LinkList p = head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void getDifference(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa = (*La)->next;
    LinkList pb = (*Lb)->next; 

    LinkList pc;
    *Lc = pc = (*La);
    // 当pa和pb都不为空时，进行循环
    while (pa && pb) {
        // 如果在a和b中都存在的相同元素，则都向下移动，删除该元素
        if (pa->data == pb->data) {
            // pc的next指向pa
            pc->next = pa;
            // pc移动到pa
            pc = pa;
            // pa向下移动
            pa = pa->next;
            // pb向下移动
            LinkList u = pb;
            pb = pb->next;
            free(u);
        }
        // 如果pa的值小于pb的值，则pa向下移动
        else if (pa->data < pb->data) {
            LinkList u = pa;
            pa = pa->next;
            free(u);
        }
        // 如果pa的值大于pb的值，则pb向下移动
        else {
            LinkList u = pb;
            pb = pb->next;
            free(u);
        }
    }

    // 释放pa和pb中多余的节点
    while (pa) {
        LinkList u = pa;
        pa = pa->next;
        free(u);
    }

    while (pb) {
        LinkList u = pb;
        pb = pb->next;
        free(u);
    }
    // 置链表尾标记
    pc->next = NULL;

    free(*Lb);
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");

    // 创建链表A {1, 2, 3, 4, 5}
    LinkList La = CreateNode(0); // 头节点
    LinkList nodeA1 = CreateNode(1);
    LinkList nodeA2 = CreateNode(2);
    LinkList nodeA3 = CreateNode(3);
    LinkList nodeA4 = CreateNode(4);
    LinkList nodeA5 = CreateNode(5);
    
    La->next = nodeA1;
    nodeA1->next = nodeA2;
    nodeA2->next = nodeA3;
    nodeA3->next = nodeA4;
    nodeA4->next = nodeA5;

    // 创建链表B {2, 4, 6, 8}
    LinkList Lb = CreateNode(0); // 头节点
    LinkList nodeB1 = CreateNode(2);
    LinkList nodeB2 = CreateNode(4);
    LinkList nodeB3 = CreateNode(6);
    LinkList nodeB4 = CreateNode(8);
    
    Lb->next = nodeB1;
    nodeB1->next = nodeB2;
    nodeB2->next = nodeB3;
    nodeB3->next = nodeB4;

    // 创建空链表Lc用于存储结果
    LinkList Lc = CreateNode(0);

    printf("链表A: ");
    PrintList(La);
    
    printf("链表B: ");
    PrintList(Lb);

    // 调用函数求交集，结果保存在La中
    getDifference(&La, &Lb, &Lc);

    printf("交集结果: ");
    PrintList(Lc);

    return 0;
}