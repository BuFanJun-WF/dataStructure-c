/*
 * issue6.c
 * 设计一个算法，通过一趟遍历确定长度为n的单链表中值最大的结点。
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
// 获取链表中最大值
int getMax(LinkList La) {
    if (La->next == NULL) {
        return -1;
    }
    // 假设第一个节点是最大值
    int max = La->next->data;
    // 获取第二个节点
    LinkList p = La->next->next;
    while (p != NULL) {
        if (p->data > max) {
            max = p->data;
        }
        // 遍历链表
        p = p->next;
    }
    return max;
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

    int max = getMax(La);

    printf("链表中最大值为: %d", max);

    return 0;
}
