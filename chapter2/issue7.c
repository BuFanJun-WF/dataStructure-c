/*
 * issue7.c
 * 设计一个算法，将链表中所有结点的链接方向“原地”逆转，
 * 即要求仅利用原表的存储空间，换句话说，要求算法的空间复杂度为O(1)。
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
// 将链表进行反转
void inverse(LinkList La) {
    // 将la的第一个元素赋值给p
    LinkList p = La->next;
    // 将la的指针域置空
    La->next = NULL;
    while (p) {
        // q指向p的下一个元素
        LinkList q = p->next;
        p->next = La->next;
        // 将p插入头节点之后
        La->next = p;
        p = q;
    }
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");

    // 构造测试链表 A: {-2, -1, 0, 1, 2, 3}
    LinkList La = CreateNode(0); // 头节点
    LinkList nodes[] = {
        CreateNode(-2),
        CreateNode(-1),
        CreateNode(0),
        CreateNode(1),
        CreateNode(2),
        CreateNode(3)
    };

    La->next = nodes[0];
    for (int i = 0; i < 5; ++i)
        nodes[i]->next = nodes[i + 1];
    nodes[5]->next = NULL;

    printf("原始链表A: ");
    PrintList(La);

    // 反转链表
    inverse(La);

    printf("反转后链表A: ");
    PrintList(La);
    return 0;
}
