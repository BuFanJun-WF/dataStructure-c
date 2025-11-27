/*
 * issue9.c
 * 已知p指向双向循环链表中的一个结点，其结点结构为data、prior、next三个域，
 * 写出算法change(p)，交换p所指向的结点及其前驱结点的顺序。
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
    struct LNode *prior; // 前向指针域
} LNode, *LinkList;

// 创建链表节点
LinkList CreateNode(ElemType data) {
    LinkList node = (LinkList)malloc(sizeof(LNode));
    if (!node) {
        printf("内存分配失败\n");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    node->prior = NULL;
    return node;
}

// 正向打印链表
void PrintList(LinkList head) {
    LinkList p = head->next;
    if (p == NULL) {
        printf("链表为空\n");
        return;
    }
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 反向打印链表
void PrintListReverse(LinkList head) {
    // 先找到最后一个节点
    LinkList p = head;
    if (p->next == NULL) {
        printf("链表为空\n");
        return;
    }
    
    // 移动到尾节点
    while (p->next != NULL) {
        p = p->next;
    }
    
    // 反向遍历
    while (p != head) {
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("\n");
}
// 交换p指向的数据与前驱
void change(LinkList p) {
    if (p == NULL || p->prior == NULL) {
        return; // 无法交换
    }
    
    LinkList q = p->prior;  // q是p的前驱
    LinkList r = p->next;   // r是p的后继
    LinkList s = q->prior;  // s是q的前驱
    
    // 调整节点连接关系
    s->next = p;
    p->prior = s;
    p->next = q;
    q->prior = p;
    q->next = r;
    if (r != NULL) {
        r->prior = q;
    }
}


int main(void) {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    system("chcp 65001 > nul");
    
    // 创建带头节点的双向循环链表
    LinkList head = CreateNode(0); // 头节点
    if (!head) {
        printf("创建头节点失败\n");
        return -1;
    }
    
    // 创建几个测试节点
    LinkList node1 = CreateNode(1);
    LinkList node2 = CreateNode(2);
    LinkList node3 = CreateNode(3);
    LinkList node4 = CreateNode(4);
    
    if (!node1 || !node2 || !node3 || !node4) {
        printf("创建节点失败\n");
        return -1;
    }
    
    // 构建双向链表
    head->next = node1;
    node1->prior = head;
    node1->next = node2;
    node2->prior = node1;
    node2->next = node3;
    node3->prior = node2;
    node3->next = node4;
    node4->prior = node3;
    node4->next = NULL; // 普通双向链表，末尾为NULL
    
    printf("原始链表（正向）：");
    PrintList(head);
    
    printf("原始链表（反向）：");
    PrintListReverse(head);
    
    // 测试change函数，交换node3和它的前驱node2
    printf("交换节点%d和它的前驱节点%d之后：\n", node3->data, node3->prior->data);
    change(node3);
    
    printf("修改后链表（正向）：");
    PrintList(head);
    
    printf("修改后链表（反向）：");
    PrintListReverse(head);
    
    // 释放内存
    LinkList current = head;
    while (current != NULL) {
        LinkList temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
