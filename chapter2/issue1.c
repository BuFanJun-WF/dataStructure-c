/*
 * issue1.c
 * 将两个递增的有序链表合并为一个递增的有序链表。
 * 要求结果链表仍使用原来两个链表的存储空间,
 * 不另外占用其它的存储空间。表中不允许有重复的数据
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

void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa, pb, pc;
    pa = (*La)->next;
    pb = (*Lb)->next;

    // pa和pb分别是La和Lb的表头结点的下一个结点，初始化相对应的链表的第一个节点
    *Lc = pc = (*La);

    while (pa && pb) {
        if (pa->data < pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else if (pa->data > pb->data) {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        else {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            LinkList q = pb->next;  // 保存下一个节点
            free(pb);               // 释放当前节点
            pb = q;                 // 移动到下一个节点
        }
    }
    // 插入剩余节点
    pc->next = pa ? pa : pb;
    // 释放Lb的头结点
    free(*Lb);
    *Lb = NULL;  // 避免野指针
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");
    
    // 创建第一个链表 La: 1->3->5
    LinkList La = (LinkList)malloc(sizeof(LNode));
    La->next = NULL;
    LinkList node1 = (LinkList)malloc(sizeof(LNode));
    LinkList node2 = (LinkList)malloc(sizeof(LNode));
    LinkList node3 = (LinkList)malloc(sizeof(LNode));
    node1->data = 1;
    node1->next = node2;
    node2->data = 3;
    node2->next = node3;
    node3->data = 5;
    node3->next = NULL;
    La->next = node1;

    // 创建第二个链表 Lb: 2->3->6
    LinkList Lb = (LinkList)malloc(sizeof(LNode));
    Lb->next = NULL;
    LinkList node4 = (LinkList)malloc(sizeof(LNode));
    LinkList node5 = (LinkList)malloc(sizeof(LNode));
    LinkList node6 = (LinkList)malloc(sizeof(LNode));
    node4->data = 2;
    node4->next = node5;
    node5->data = 3;
    node5->next = node6;
    node6->data = 6;
    node6->next = NULL;
    Lb->next = node4;

    // 声明结果链表 Lc
    LinkList Lc;

    // 调用合并函数
    MergeList(&La, &Lb, &Lc);

    // 打印合并后的链表
    printf("合并后的链表: ");
    LinkList current = Lc->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // 释放剩余链表内存
    current = Lc->next;
    while (current != NULL) {
        LinkList temp = current;
        current = current->next;
        free(temp);
    }
    free(Lc); // 释放头节点

    return 0;
}
