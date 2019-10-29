#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
#include "menu.h"

int Exit(int argc, char *argv[])
{
    printf("Bye-bye\n");
    exit(0);
}
int Version(int argc, char *argv[])
{
    printf("menu program v3.0\n");
}

int main(int argc, char *argv[])
{
    MenuConfig("version", "menu program v3.0", Version);
    MenuConfig("exit", "Exit this program", Exit);
    ExecuteMenu();
    return 0;
}