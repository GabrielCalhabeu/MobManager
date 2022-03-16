#ifndef MOBMANAGER_ENEMY_H
#define MOBMANAGER_ENEMY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Segment for Enemy, enemyCell, and enemyList creation.

typedef struct enemy {

    int ID;
    int maxHp;
    int curHp;
    char state[10];

}TypeEnemy;


typedef struct enemyCell {

    TypeEnemy enemy;
    struct enemyCell* next;

}enemyCell;


typedef struct enemyList{

    int size;
    struct enemyCell* first;
    struct enemyCell* last;

}enemyList;



//Segment for Group, groupCell, and groupList.

typedef struct group{

    char groupName[50];
    enemyList* enemyList;

}TypeGroup;


typedef struct groupCell{

    TypeGroup group;
    struct groupCell* next;

}groupCell;


typedef struct groupList{

    int size;
    struct groupCell* first;
    struct groupCell* last;

}groupList;



enemyList* createEnemyList(enemyList *enemyList, int hp, int numberOfEnemies);
enemyList* addEnemy(TypeEnemy enemy, enemyList *enemyList);
void makeEnemyList(enemyList* enemyList);
void makeGroupList(groupList * groupList);
void addGroup(TypeGroup group, groupList *groupList);
void createGroup(groupList * groupList);
void freeEnemyList(enemyList * enemyList);
void deleteGroup(groupList * groupList, int pos);
void editGroup(groupList * groupList, int pos);
void damageEnemy(groupList* groupList1, int posX, int posY, int damage, int mode);
void changeStatus(groupList* groupList1, int posX, int posY, char status[10]);
void removeStatus(groupList* groupList1, int posX, int posY);
void flushGroupList(groupList *groupList);

#endif //MOBMANAGER_ENEMY_H
