#include "interface.h"
#include "fileManager.h"
void strcopy(char a[], const char *b, int point) {

    //Copia uma string.
    for(int i = 0 ; i < point; i++){
        a[i] = b[i];
    }
    a[point] = '\0';
}

void help(){
    system("cls");
    printf("Welcome to mob manager TM by Kyuube\n\n");
    printf("\nThe program works by creating groups, and the group has enemies within it");
    printf("\nAn enemy has max hp, current hp, and a status that can be changed.");
    printf("\nAn enemy, like its group, has an index shown by the name.");
    printf("\nIn order to select a specific enemy you must enter the index of the group, then the enemy's, separated by a space");
    printf("\nExample: First group. Second enemy, 1 2");
    printf("\nIf you accidentally type a letter when the program asks for a number it will loop,lmao ( i wont fix it im lazy)");
    printf("\nPress enter to continue...");
    getchar();
}

int startMenu() {
    int option;
    system("cls");
    printf("----- Welcome to Mob Manager TM--------\n\n");
    printf("1 - Mob Menu\n");
    printf("2 - Help\n");
    printf("3 - Save file\n");
    printf("4 - Load file\n");
    printf("4 - Clear cache\n");
    printf("5 - Exit\n");
    printf("\nChoose an option: ");
    scanf("%d", &option);
    return option;
}

int createMenu(){
    int op;
    printf("\n1 - Create Group\n");
    printf("2 - Delete Group\n");
    printf("3 - Edit Group\n");
    printf("4 - Damage Enemy\n");
    printf("5 - Heal Enemy\n");
    printf("6 - Add Status to enemy\n");
    printf("7 - Remove Status from enemy\n");
    printf("8 - Start Menu\n");
    printf("\nChoose an option: ");
    scanf("%d", &op);
    return op;
}



int groupMenu(groupList *groupList1){
    int option;
    int newOp;

    char pos[10];
    char posX[5];
    char posY[5];
    int pause = 0;
    int damage;

    //GROUP MENU
    do{
        printGroups(*groupList1);
        option = createMenu();

        //Create group menu
        if(option == 1){
            createGroup(groupList1);
            saveBackUp(groupList1);
        }

        //Delete Menu
        else if( option == 2){
            printf("\nChoose the number of the group to delete: ");
            scanf("%d", &newOp);
            if(newOp < 1 || newOp > groupList1->size){
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            }
            else{
                deleteGroup(groupList1, newOp);
                saveBackUp(groupList1);
            }
        //Edit menu
        }else if(option == 3){
            printf("\nChoose the number of the group to Edit: ");
            scanf("%d", &newOp);
            if(newOp < 1 || newOp > groupList1->size){
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            }
            else{
                editGroup(groupList1, newOp);
                saveBackUp(groupList1);
            }

        }else if(option == 4){

            printf("\nInput the position of the enemy: ");
            fflush(stdin);
            fgets(pos, 10, stdin);
            pos[strcspn(pos, "\n")] = 0;
            fflush(stdin);
            printf("\nInput the damage dealt: ");
            scanf("%d", &damage);

            for(int i = 0; i < 10; i++){
                if(pos[i] == 32){
                    pause = i;
                    break;
                }
            }

            strcopy(posX, pos,  pause);
            strcopy(posY, (pos+pause+1),  pause);

            if(atoi(posX) < 1 || atoi(posX) > groupList1->size){
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            }
            else{
                damageEnemy(groupList1, atoi(posX), atoi(posY), damage, -1);
                saveBackUp(groupList1);
            }

        } else if(option == 5){

            printf("\nInput the position of the enemy: ");
            fflush(stdin);
            fgets(pos, 10, stdin);
            pos[strcspn(pos, "\n")] = 0;
            fflush(stdin);
            printf("\nInput the heal done: ");
            scanf("%d", &damage);

            for(int i = 0; i < 10; i++){
                if(pos[i] == 32){
                    pause = i;
                    break;
                }
            }

            strcopy(posX, pos,  pause);
            strcopy(posY, (pos+pause+1),  pause);

            if(atoi(posX) < 1 || atoi(posX) > groupList1->size){
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            }
            else{
                damageEnemy(groupList1, atoi(posX), atoi(posY), damage, 1);
            }

        } else if(option == 6) {

            char status[10];

            printf("\nInput the position of the enemy: ");
            fflush(stdin);
            fgets(pos, 10, stdin);
            pos[strcspn(pos, "\n")] = 0;
            fflush(stdin);
            printf("\nInput the status effect: ");
            fgets(status, 10, stdin);
            status[strcspn(status, "\n")] = 0;
            fflush(stdin);

            for (int i = 0; i < 10; i++) {
                if (pos[i] == 32) {
                    pause = i;
                    break;
                }
            }

            strcopy(posX, pos, pause);
            strcopy(posY, (pos + pause + 1), pause);

            if (atoi(posX) < 1 || atoi(posX)> groupList1->size) {
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            } else {
                changeStatus(groupList1, atoi(posX), atoi(posY), status);
                saveBackUp(groupList1);
            }
        } else if(option == 7) {


            printf("\nInput the position of the enemy: ");
            fflush(stdin);
            fgets(pos, 10, stdin);
            pos[strcspn(pos, "\n")] = 0;
            fflush(stdin);

            for (int i = 0; i < 10; i++) {
                if (pos[i] == 32) {
                    pause = i;
                    break;
                }
            }

            strcopy(posX, pos, pause);
            strcopy(posY, (pos + pause + 1), pause);

            if (atoi(posX) < 1 || atoi(posX)> groupList1->size) {
                printf("\nGroup not found! press enter to continue...\n");
                getchar();
                getchar();
            } else {
                removeStatus(groupList1, atoi(posX), atoi(posY));
                saveBackUp(groupList1);
            }
        }
    }while(option != 8);

    return 0;
}

void printEnemies(enemyList enemylist, char name[50]) {
    enemyCell* aux;
    aux = enemylist.first->next;
    if(enemylist.size == 0){
        return;
    }
    for(int i = 0; i < enemylist.size; i++){
        if(aux->enemy.curHp == 0){
            printf("%s %d - DEAD", name, aux->enemy.ID);
        }
        else{
            printf("%s %d - %d/%d HP", name, aux->enemy.ID, aux->enemy.curHp, aux->enemy.maxHp);
            if(aux->enemy.state[0] != 0){
                printf(" %s", aux->enemy.state);
            }
        }
        printf("\n");
        aux = aux->next;
    }
}

void printGroups(groupList groupList) {
    system("cls");
    groupCell* aux;
    aux = groupList.first->next;
    if(groupList.size == 0){
        printf("No Groups!\n");
        return;
    }
    for(int i = 0; i < groupList.size; i++){
        printf("----- Group %d - %s ------\n", (i+1), aux->group.groupName);
        printEnemies(*aux->group.enemyList, aux->group.groupName);
        printf("--------------------------\n\n");
        aux = aux->next;
    }

}