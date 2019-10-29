#include "linktable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CMD_MAX_LEN 100

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char *cmd;
    char *desc;
    int (*handler)();
} tDataNode;

int Help();
int Exit();

int InitMenuData(tLinkTable **ppLinkTable)
{
    *ppLinkTable = CreateLinkTable();

    tDataNode *pNode = (tDataNode *)malloc(sizeof(tDataNode));

    pNode->cmd = "help";
    pNode->desc = "this is a help command";
    pNode->handler = Help;
    AddLinkTableNode(*ppLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "version";
    pNode->desc = "Menu Program V2.5";
    pNode->handler = NULL;
    AddLinkTableNode(*ppLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "exit";
    pNode->desc = "Exit from Menu Program";
    pNode->handler = Exit;
    AddLinkTableNode(*ppLinkTable, (tLinkTableNode *)pNode);

    return 0;
}

tDataNode *FindCmd(tLinkTable linkTable, char *cmd)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(linkTable);
    while (pNode != NULL)
    {
        if (strcmp(pNode->cmd, cmd) == 0)
        {
            return pNode;
        }
        pNode = (tDataNode *)GetNextLinkTableNode(linkTable, (tLinkTableNode *)pNode);
    }
    return NULL;
}

int ShowAllCmd(tLinkTable LinkTable)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(LinkTable);
    while (pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode *)GetNextLinkTableNode(LinkTable, (tLinkTableNode *)pNode);
    }
    return 0;
}

tLinkTable *pLinkTable = NULL;

int main()
{
    InitMenuData(&pLinkTable);
    while (1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Input a cmd > ");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(*pLinkTable, cmd);
        if (p == NULL)
        {
            printf("This is a wrong cmd!You may need 'help' cmd\n");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc);
        if (p->handler != NULL)
        {
            p->handler();
        }
    }
    return 0;
}

int Help()
{
    ShowAllCmd(*pLinkTable);
    return 0;
}

int Exit()
{
    exit(0);
}
