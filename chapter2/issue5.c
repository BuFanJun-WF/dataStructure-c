/*
 * issue5.c
 * 设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B和C，
 * 其中B表的结点为A表中值小于零的结点，而C表的结点为A表中值大于零的结点
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
// 分解链表函数：将La分解成B（负数）和C（正数）
void disCompose(LinkList La,LinkList *Lb, LinkList *Lc) {
    // 初始化B、C链表头节点
    *Lb = CreateNode(0);
    *Lc = CreateNode(0);

    LinkList pb = *Lb;
    LinkList pc = *Lc;

    // 遍历A链表
    LinkList p = La->next;
    while (p) {
        if (p->data < 0) {
            pb->next = p;
            pb = p;
        }
        else if (p->data > 0) {
            pc->next = p;
            pc = p;
        }

        p = p->next;
    }
    // 结束两个新链表
    pb->next = NULL;
    pc->next = NULL;
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

    LinkList Lb, Lc;

    printf("原始链表A: ");
    PrintList(La);

    disCompose(La, &Lb, &Lc);

    printf("分解后B(负数): ");
    PrintList(Lb);

    printf("分解后C(正数): ");
    PrintList(Lc);

    return 0;
}