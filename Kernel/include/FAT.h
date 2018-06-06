#include <stddef.h>
#include "videoMode.h"
#include "fileErrors.h"
#include "string.h"
#define NOT_OPEN 7
#define READ 0
#define WRITE 1
#define FALSE 0
#define TRUE 1
#define IS_DIR TRUE
#define MAX_NAME_SIZE 50
#define MAX_FILE_SIZE 200
#define MAX_OPEN_FILES 5
#define EOF -1

typedef unsigned char bool;

typedef struct FileCDT * File;
typedef struct FileCDT {
	int fd;
	void * fileContent;
	char * name;
	unsigned size;
	unsigned char openMode; // NOT_OPEN, READ, WRITE
} FileCDT;

typedef struct TableEntryCDT * TableEntry;
typedef struct TableEntryCDT {
	void * entry; // either Dir or File
	char * name;
	TableEntry next;
} TableEntryCDT;

typedef struct FATCDT * FAT;
typedef struct FATCDT {
	TableEntry firstFile;
	TableEntry lastFile;
	TableEntry firstDir;
	TableEntry lastDir;
	unsigned fileCount;
	unsigned subDirCount;
	FAT parentDir;
} FATCDT;

typedef struct DirCDT * Dir;
typedef struct DirCDT {
	int dd;
	FAT table;
	char * name;
} DirCDT;

void initializeFileSystem();

FAT newFileTable();
TableEntry addFileEntry(char * name, FAT table);
TableEntry addDirEntry(char * name, FAT table);
File getFile(char * name, FAT table);
Dir getDir(char * name, FAT table);
File findFile(char * path);
int cd(char * path);
void ls();
int mkdir(char * path);
int touch(char * path);
int rm(char * path, int isDir);
int deleteFile(char * name, FAT table);
int deleteDir(char * name, FAT table);
int getFileDetails(char * path);
int open(char * name, const char * mode); // mode: "r" or "w"
int close(int id);
int read(void * dest, size_t blockSize, size_t blockNum, int fileId);
int write(void * src, size_t blockSize, size_t blockNum, int fileId);
int validateName(char * name);
char * explorePath(char * path, char buff[], bool * hasEnded);
void * findFileOrDir(char * path, char buff[], bool isDir);
