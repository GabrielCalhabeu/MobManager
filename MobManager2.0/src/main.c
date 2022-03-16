#include <stdio.h>
#include "enemy.h"
#include "interface.h"
#include "fileManager.h"
int main() {

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
