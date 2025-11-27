/*
 * issue8.c
 * 设计一个算法，删除递增有序链表中值大于mink且小于maxk的所有元素
 *
 * LNode node;        // 声明一个节点
 * LinkList head;     // 声明一个链表头指针，等价于 LNode *head;
 */

#include <inttypes.h>
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
    if (!node) return NULL;
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
// 将链表中大于mink小于maxk的元素删除
void delete(LinkList La, int mink, int maxk) {
    LinkList p = La->next;
    LinkList pre = La;
    // 查找第一个节点大于mink的节点
    while (p != NULL && p->data <= mink) {
        pre = p;
        p = p->next;
    }
    // 查找到符合的元素
    if (p != NULL) {
        while (p->data < maxk) {
            // 查找第一个大于等于maxk的节点
            p = p->next;
        }
    }
    LinkList q = pre->next;
    // 修改指针
    pre->next = p;
    // 释放链表空间
    while (q != p) {
        LinkList t = q->next;
        free(q);
        q = t;
    }
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");
    
    // 创建一个带头结点的链表
    LinkList head = (LinkList) malloc(sizeof(LNode));
    head->next = NULL;
    head->data = 0; // 头结点的数据域无意义
    
    // 创建测试数据 1 3 5 7 9 11 13
    LinkList current = head;
    for (int i = 1; i <= 13; i += 2) {
        LinkList node = CreateNode(i);
        current->next = node;
        current = node;
    }
    
    printf("原始链表:\n");
    PrintList(head);
    
    // 删除值大于3且小于9的元素 (应该删除5和7)
    delete(head, 3, 9);
    
    printf("删除值大于3且小于9的元素后:\n");
    PrintList(head);
    
    // 继续测试，删除值大于0且小于100的元素 (删除剩余所有元素)
    delete(head, 0, 100);
    
    printf("删除值大于0且小于100的元素后:\n");
    PrintList(head);
    
    // 释放头结点
    free(head);
    
    return 0;
}
