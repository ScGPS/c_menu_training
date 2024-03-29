#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "linktable.h"

int Help();
int Quit();

#define CMD_MAX_LEN 128
#define DESC_LEN 1024
#define CMD_NUM 10

/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char *cmd;
    char *desc;
    int (*handler)();
} tDataNode;

int SearchCondition(tLinkTableNode *pLinkTableNode, void *args)
{
    char *cmd = (char *)args;
    tDataNode *pNode = (tDataNode *)pLinkTableNode;
    if (strcmp(pNode->cmd, cmd) == 0)
    {
        return SUCCESS;
    }
    return FAILURE;
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    return (tDataNode *)SearchLinkTableNode(head, SearchCondition, (void *)cmd);
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(head);
    while (pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode *)GetNextLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    return 0;
}

int InitMenuData(tLinkTable **ppLinktable)
{
    *ppLinktable = CreateLinkTable();
    tDataNode *pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "Menu List:";
    pNode->handler = Help;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);
    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "version";
    pNode->desc = "Menu Program V2.8";
    pNode->handler = NULL;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);
    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "Quit from Menu Program V2.8";
    pNode->handler = Quit;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

    return 0;
}

/* menu program */

tLinkTable *head = NULL;

int main()
{
    InitMenuData(&head);
    /* cmd line begins */
    while (1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if (p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc);
        if (p->handler != NULL)
        {
            p->handler();
        }
    }
}

int Help()
{
    ShowAllCmd(head);
    return 0;
}

int Quit()
{
    exit(0);
}