/*
 * issue2.c
 * 将两个非递减的有序链表合并为一个非递增的有序链表。
 * 要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。
 * 表中允许有重复的数据。
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

void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa, pb, pc;

    pa = (*La)->next;
    pb = (*Lb)->next;
    // 使用La的头节点作为Lc的头节点
    *Lc = pc = (*La);
    (*Lc)->next = NULL;
    // 只要存在一个非空表，用q指向待摘取的元素
    while (pa || pb) {
        LinkList q;
        // La表为空，用q指向pb，pb指针后移
        if (!pa) {
            q = pb;
            pb = pb->next;
        }
        // Lb表为空，用q指向pa，pa指针后移
        else if (!pb) {
            q = pa;
            pa = pa->next;
        }
        // La和Lb不为空，取较小者中的元素，用q指向该元素，指针后移
        else if (pa->data <= pb->data) {
            q = pa;
            pa = pa->next;
        }
        else {
            q = pb;
            pb = pb->next;
        }
        // 将获取到的元素插入到Lc表的表头节点之后
        q->next = pc->next;
        pc->next = q;
    }
    free(*Lb);
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");
    // 创建第一个非递减有序链表: 1->3->5->7
    LinkList La = CreateNode(0); // 头节点
    LinkList node1 = CreateNode(1);
    LinkList node2 = CreateNode(3);
    LinkList node3 = CreateNode(5);
    LinkList node4 = CreateNode(7);
    
    La->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    // 创建第二个非递减有序链表: 2->4->6->8
    LinkList Lb = CreateNode(0); // 头节点
    LinkList node5 = CreateNode(2);
    LinkList node6 = CreateNode(4);
    LinkList node7 = CreateNode(6);
    LinkList node8 = CreateNode(8);
    
    Lb->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node8;
    
    printf("链表A: ");
    PrintList(La);
    printf("链表B: ");
    PrintList(Lb);
    
    // 合并链表
    LinkList Lc;
    MergeList(&La, &Lb, &Lc);
    
    printf("合并后的非递增链表: ");
    PrintList(Lc);
    
    return 0;
}