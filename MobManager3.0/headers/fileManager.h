#ifndef MOBMANAGER_FILEMANAGER_H
#define MOBMANAGER_FILEMANAGER_H



#define save "D:\\Programas\\MobManager\\cmake-build-debug\\Saves\\otherTest.dat"
#define cacheFilePath ".\\cache.dat"

#define FORMAT_OUT "%s, %d, %d, %d, %s\n"
#define FORMAT_IN "%[^,\n], %d, %d, %d, %s"


#include "interface.h"
#include "enemy.h"
#include <dirent.h>
int extractFileName();
void writeLine(TypeEnemy *e, char name[50], char* fileName);
void readFile(TypeEnemy *e, char name[50], char* fileName);
void loadFile(groupList *groupList, char fileName[50]);
void saveFile(groupList *groupList, char fileName[50]);
void saveBackUp(groupList *groupList);
void loadBackUp(groupList *groupList);

#endif //MOBMANAGER_FILEMANAGER_H
