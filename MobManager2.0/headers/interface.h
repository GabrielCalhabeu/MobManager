
#ifndef MOBMANAGER_INTERFACE_H
#define MOBMANAGER_INTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"

int startMenu();
void printEnemies(enemyList enemylist, char name[50]);
void printGroups(groupList groupList);
int createMenu();
int groupMenu(groupList *groupList1);
enemyCell * findEnemy(enemyList enemyList1, int pos);
void strcopy(char a[], const char *b, int size);
void help();

#endif //MOBMANAGER_INTERFACE_H
