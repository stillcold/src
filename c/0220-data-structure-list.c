#include <stdio.h>
#include <malloc.h>

typedef struct Node{
    struct Node *next;
    int element;
} Node;

Node* insertElement(Node *head, int value);

int main(void)
{
    Node *head;
    Node *p;
    int i, value;
    int len = 5;

    head = NULL;   
    p = head;
    for(i = 0; i < len; i++)
    {
        scanf("%d", &value);
        head = insertElement(head, value);
    }
    printf("Here\n");
    p = head;
    if(head == NULL)
        printf("Bad\n");

    while( p!= NULL)
    {
        printf("%d\n", p->element);
        p = p->next;
    }
    return 0;
}

Node* insertElement(Node *head, int value)
{
    Node *q;
    Node *p;

    if (head == NULL)
    {
        printf("get %d, will go.\n", value);
        head = (Node *) malloc(sizeof(Node));
        head->next = NULL;
        head->element = value;
        return head;
    }

    p = q = head;

    while(p != NULL)
    {
        printf("moving ...\n");
        if (value > p->element)
        {
            q = p;
            p = p->next;
        }else{
            break;
        }
    }

    if (q == head)
    {
        p = (Node *) malloc(sizeof(Node));
        p->element = value;
        p->next = head;
        return p;
    }

    p = (Node *) malloc(sizeof(Node));
    p->next = q->next;
    p->element = value;
    q->next = p;

    return head;
}
