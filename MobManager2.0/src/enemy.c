
#include "../headers/enemy.h"

void makeEnemyList(enemyList* enemyList){

    enemyList->first = (enemyCell *) malloc(sizeof (enemyCell));
    enemyList->last = enemyList->first;
    enemyList->first->next = NULL;
    enemyList->size = 0;

}

enemyList* addEnemy(TypeEnemy enemy, enemyList *enemyList) {
    enemyList->last->next = (enemyCell *) malloc(sizeof (enemyCell));
    enemyList->last = enemyList->last->next;
    enemyList->last->enemy = enemy;

    enemyList->last->next = NULL;
    enemyList->size++;
    return enemyList;
}


enemyList* createEnemyList(enemyList *enemyList, int hp, int numberOfEnemies) {

    makeEnemyList(enemyList);

    TypeEnemy enemy;
    enemy.maxHp = hp;
    enemy.curHp = hp;
    enemy.state[0] = 0;
    for(int i = 0; i < numberOfEnemies; i++){
        enemy.ID = (i+1);

        addEnemy(enemy, enemyList);
    }
    return enemyList;
}

enemyCell * findEnemy(enemyList enemyList1, int pos) {
    enemyCell *aux = enemyList1.first->next;
    if(pos < 1 || pos > enemyList1.size){
        printf("\nEnemy not found! press enter to continue...\n");
        getchar();
        getchar();
        return NULL;
    }
    for(int i = 0; i < (pos-1); i++){
        aux = aux->next;
    }
    return aux;
}

void removeStatus(groupList* groupList1, int posX, int posY) {

    groupCell *aux = groupList1->first->next;
    enemyCell *enemy = NULL;
    if(posX < 1 || posX > groupList1->size){
        printf("\nGroup Not Found! press enter to continue...\n");
        getchar();
        return;
    }
    for(int i = 0; i < (posX-1); i++){
        aux = aux->next;
    }

    enemy = findEnemy(*aux->group.enemyList, posY);
    if(enemy == NULL){
        return;
    }

    enemy->enemy.state[0] = 0;

}

void changeStatus(groupList* groupList1, int posX, int posY, char status[10]) {

    groupCell *aux = groupList1->first->next;
    enemyCell *enemy = NULL;
    if(posX < 1 || posX > groupList1->size){
        printf("\nGroup Not Found! press enter to continue...\n");
        getchar();
        getchar();
        return;
    }
    for(int i = 0; i < (posX-1); i++){
        aux = aux->next;
    }

    enemy = findEnemy(*aux->group.enemyList, posY);
    if(enemy == NULL){
        return;
    }

    strcpy(enemy->enemy.state, status);

}

//Can both heal and damage depending on mode, if mode = -1 it damages, else heals.
void damageEnemy(groupList* groupList1, int posX, int posY, int damage, int mode) {

    groupCell *aux = groupList1->first->next;
    enemyCell *enemy = NULL;
    if(posX < 1 || posX > groupList1->size){
        printf("\nGroup Not Found! press enter to continue...\n");
        getchar();
        getchar();
        return;
    }
    for(int i = 0; i < (posX-1); i++){
        aux = aux->next;
    }

    enemy = findEnemy(*aux->group.enemyList, posY);
    if(enemy == NULL){
        return;
    }
    if(mode == -1){
        enemy->enemy.curHp = enemy->enemy.curHp - damage;

        if(enemy->enemy.curHp < 0){
            enemy->enemy.curHp = 0;
        }
    }
    else{
        enemy->enemy.curHp = enemy->enemy.curHp + damage;

        if(enemy->enemy.curHp > enemy->enemy.maxHp){
            enemy->enemy.curHp = enemy->enemy.maxHp;
        }
    }

}

void makeGroupList(groupList * groupList) {

    groupList->first = (groupCell *) malloc(sizeof(groupCell));
    groupList->last = groupList->first;
    groupList->first->next = NULL;
    groupList->size = 0;

}

void addGroup(TypeGroup group, groupList *groupList) {
    groupList->last->next = (groupCell *) malloc(sizeof (groupCell));
    groupList->last = groupList->last->next;
    groupList->last->group = group;
    groupList->last->next = NULL;
    groupList->size++;
}


void freeEnemyList(enemyList * enemyList){
    struct enemyCell *aux, *prv;
    aux = enemyList->first->next;
    for(int i = 0; i < enemyList->size; i++){
        enemyList->first->next = aux->next;
        free(aux);
        aux = enemyList->first->next;
    }
    free(enemyList->first->next);
    free(enemyList->last->next);
    enemyList->size = 0;
    enemyList->first = NULL;
    enemyList->last = NULL;
}

void deleteGroup(groupList * groupList, int pos) {

    if(groupList->size == 1){
        freeEnemyList(groupList->first->next->group.enemyList);
        free(groupList->first->next);
        makeGroupList(groupList);
        return;
    }

    struct groupCell *aux, *prv;
    aux = groupList->first->next;
    prv = groupList->first;
    for(int i = 0; i < (pos-1); i++){
        prv = aux;
        aux = aux->next;
    }
    prv->next = aux->next;
    freeEnemyList(aux->group.enemyList);
    if(prv->next == NULL){
        groupList->last = prv;
    }
    if(aux->group.enemyList->last == NULL){
        free(aux);
    }
    groupList->size--;
}

void editGroup(groupList * groupList, int pos) {

    char name[50];
    int numberOfEnemies;
    int hp;

    struct groupCell *aux;
    aux = groupList->first->next;
    if(pos < 1 || pos >groupList->size){
        printf("\nGroup Not Found! press enter to continue...\n");
        getchar();
        getchar();
        return;
    }
    for(int i = 0; i < (pos-1); i++){
        aux = aux->next;
    }
    freeEnemyList(aux->group.enemyList);
    makeEnemyList(aux->group.enemyList);

    printf("\nInput the type of enemy: ");
    fflush(stdin);
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    fflush(stdin);
    printf("\nInput the HP of the enemies: ");
    scanf("%d%*c", &hp);
    printf("\nInput the number of enemies: ");
    scanf("%d%*c", &numberOfEnemies);
    createEnemyList(aux->group.enemyList, hp, numberOfEnemies);
}

void createGroup(groupList * groupList) {
    char name[50];
    int numberOfEnemies;
    int hp;
    printf("\nInput the type of enemy: ");
    fflush(stdin);
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    fflush(stdin);
    printf("\nInput the HP of the enemies: ");
    scanf("%d%*c", &hp);
    printf("\nInput the number of enemies: ");
    scanf("%d%*c", &numberOfEnemies);

    TypeGroup group;

    enemyList * enemylist = (enemyList*) malloc(sizeof(*enemylist));
    makeEnemyList(enemylist);

    createEnemyList(enemylist, hp, numberOfEnemies);

    strcpy(group.groupName, name);
    group.enemyList = enemylist;

    addGroup(group, groupList);
}

void flushGroupList(groupList *groupList){
    while(groupList->size > 0){
        deleteGroup(groupList, 1);
    }

}