#include <stdio.h>
#include "enemy.h"
#include "interface.h"
#include "fileManager.h"
int main() {
//
//    enemyList enemyList1;
//    enemyList enemyList2;
//    enemyList enemyList3;
//    groupList groupList1;
//
//    makeEnemyList(&enemyList1);
//    makeEnemyList(&enemyList2);
//    makeGroupList(&groupList1);
//
//    createEnemyList(&enemyList1, 10, 1);
//    createEnemyList(&enemyList2, 20, 5);
//    createEnemyList(&enemyList3, 30, 3);
//
//    TypeGroup group1 = {
//          .groupName = "Bandit",
//          .enemyList = &enemyList1
//    };
//
//    TypeGroup group2 = {
//            .groupName = "Bandit Captain",
//            .enemyList = &enemyList2
//    };
//    TypeGroup group3 = {
//            .groupName = "Bandit Lord",
//            .enemyList = &enemyList3
//    };
//    addGroup(group1, &groupList1);
//    addGroup(group2, &groupList1);
//    addGroup(group3, &groupList1);
//
//    flushGroupList(&groupList1);
//
//    makeEnemyList(&enemyList2);
//    createEnemyList(&enemyList2, 20, 5);
//
//    saveFile(&groupList1, save);
//
//    addGroup(group2, &groupList1);
//    saveBackUp(&groupList1);
//    extractFileName();
//    loadBackUp(&groupList1);
//    printGroups(groupList1);
//


    groupList groupList1;
    makeGroupList(&groupList1);

    int option = 0;
    int newOp = 0;
    char fileName[50];
    do{
        option = startMenu();
        switch (option) {
            case 1:
                option = groupMenu(&groupList1);
                break;
            case 2:
                help();
                getchar();
                break;
            case 3:
                if(groupList1.size == 0){
                    printf("\nEmpty Groups, cannot save! Create at least one group\n");
                    printf("Press enter...");
                    getchar();
                    getchar();
                    break;
                }
                printf("\nName the save file: ");
                fflush(stdin);
                fgets(fileName, 50, stdin);
                fileName[strcspn(fileName, "\n")] = 0;
                fflush(stdin);
                saveFile(&groupList1, fileName);
                break;
            case 4:
                if(!extractFileName())
                    break;
                printf("\nName the save file: ");
                fflush(stdin);
                fgets(fileName, 50, stdin);
                fileName[strcspn(fileName, "\n")] = 0;
                fflush(stdin);
                loadFile(&groupList1, fileName);
                break;
            case 5:
                flushGroupList(&groupList1);
                break;
            default:
                printf("\nNot an option, press enter to continue...");
                getchar();
                getchar();
        }
    }while(option != 5);




    return 0;
}
