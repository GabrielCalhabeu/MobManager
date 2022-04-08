#include "fileManager.h"

int extractFileName() {
    printf("\n");
    char* file = "Saves";
    DIR *d;
    struct dirent *dir;
    d = opendir(file);
    int found = 0;
    if (d)
    {

        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == 0) {
                printf("%s\n", dir->d_name);
                found = 1;
            }
        }

        closedir(d);
    }
    if(found){
        return 1;
    }
    else{
        printf("\nNo Files\n");
        printf("Press enter...");
        getchar();
        getchar();
        return 0;
    }
}



void writeLine(TypeEnemy *e, char name[50], char* fileName) {
    FILE *file = fopen(fileName, "a");
    fprintf(file, FORMAT_OUT, name, e->ID, e->curHp, e->maxHp, e->state);
    fclose(file);
}

void readFile(TypeEnemy *e, char name[50], char* fileName) {
    FILE *file = fopen(fileName, "r");
    char state[10];
    state[0] = 0;
    fscanf(file, FORMAT_IN, name, &e->ID, &e->curHp, &e->maxHp, state);
    memcpy(&e->state, state, 10);
    fclose(file);
}


void saveBackUp(groupList *groupList) {

    if(groupList->size == 0){
        printf("\nGroups are empty!\n");
        return;
    }

    FILE *File = fopen(cacheFilePath, "w");
    groupCell * aux;
    enemyCell * enemyCell1;
    char state[10];
    aux = groupList->first->next;
    for(int i = 0; i < groupList->size; i++){
        enemyCell1 = aux->group.enemyList->first->next;
        for(int j = 0; j < aux->group.enemyList->size; j++){
            if(enemyCell1->enemy.state[0] != 0){
                memcpy(state, enemyCell1->enemy.state, 10);
            }
            else{
                state[0] = 35;
            }
            fprintf(File, "%s, %d, %d, %d, %s\n", aux->group.groupName , enemyCell1->enemy.ID, enemyCell1->enemy.curHp,
                    enemyCell1->enemy.maxHp, state);

            enemyCell1 = enemyCell1->next;
        }
        aux = aux->next;
    }
    fclose(File);
}

void loadBackUp(groupList *groupList) {

    FILE *File = fopen(cacheFilePath, "r");
    fseek(File, 0, SEEK_SET);
    groupCell * aux;
    enemyCell * enemyCell1;
    TypeEnemy temp;
    int last = 0;
    char name[50];
    char dump;
    char state[10];
    state[0] = 0;
    enemyList * enemylist;
    TypeGroup group;
    while (fscanf(File, "%[^,], %d, %d, %d, %s", name, &temp.ID, &temp.curHp, &temp.maxHp, state)){
        if(last == 1){
            addGroup(group, groupList);
        }
        if(temp.ID == 1){
            enemylist = (enemyList*) malloc(sizeof  (*enemylist));
            makeEnemyList(enemylist);
        }
        if(strcmp(state, "#") != 0){
            memcpy(temp.state, state, 10);
        }
        else{
            temp.state[0] = 0;
        }
        addEnemy(temp, enemylist);
        memcpy(group.groupName, name, 50);

        group.enemyList = enemylist;


        last = temp.ID;
        dump = fgetc(File);
        if(dump == EOF){
            break;
        }

    }
    fclose(File);

}

void loadFile(groupList *groupList, char fileName[50]) {
    if(groupList->size > 0){
        flushGroupList(groupList);
    }

    char filePath[63];
    int i = 0;
    while(fileName[i] != 0){
        if(fileName[i] == 32){
            fileName[i] = 95;
        }
        i++;
    }


    memcpy(filePath, "Saves\\\0", 8);
    strncat(filePath, fileName, 50);
    strncat(filePath, ".dat\0", 5);
    FILE *File = fopen(filePath, "r");
    if(File == NULL){
        printf("\nFile not found!\n");
        printf("Press enter...");
        getchar();
        return;
    }
    fseek(File, 0, SEEK_SET);

    int hp = 0, numEnemies = 0, change = 0;
    char dump;
    char name[50];
    char first = 0;
    TypeGroup group;
    while (fscanf(File, "%[^,\n], %d, %d\n", name, &hp, &numEnemies)){
        for(int i = 0; i < 50; i++){
            group.groupName[i] = 0;
        }

        enemyList * enemylist = (enemyList*) malloc(sizeof(*enemylist));
        makeEnemyList(enemylist);

        createEnemyList(enemylist, hp, numEnemies);
        if(change){
            group.groupName[0] = first;
            strncat(group.groupName, name, strlen(name));
        }
        else{
            strcpy(group.groupName, name);
        }

        group.enemyList = enemylist;

        addGroup(group, groupList);

        dump = fgetc(File);
        if(dump == EOF){
            break;
        }
        else{
            first = dump;
            change = 1;
        }
    }
    printf("\nFile Loaded!\n");
    printf("Press enter...");
    getchar();
    fclose(File);
}

void saveFile(groupList *groupList, char fileName[50]) {
    if(groupList->size == 0){
        printf("\nGroups are empty!\n");
        return;
    }
    char filePath[62];
    int i = 0;
    while(fileName[i] != 0){
        if(fileName[i] == 32){
            fileName[i] = 95;
        }
        i++;
    }

    memcpy(filePath, "Saves\\\0", 7);
    strncat(filePath, fileName, 50);
    strncat(filePath, ".dat\0", 5);


    FILE *File = fopen(filePath, "w");
    groupCell * aux;
    aux = groupList->first->next;
    for(int i = 0; i < groupList->size; i++){
        fprintf(File, "%s, %d, %d\n", aux->group.groupName , aux->group.enemyList->last->enemy.maxHp, aux->group.enemyList->size);
        aux = aux->next;
    }
    printf("\nFile Saved!\n");
    printf("Press enter...");
    getchar();
    fclose(File);
}
