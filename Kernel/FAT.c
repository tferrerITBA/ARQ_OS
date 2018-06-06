#include "FAT.h"

static File newFile(char * name);
static Dir newDir(char * name);
//static TableEntry addEntryRec(char * name, bool isDir, TableEntry curr);
static TableEntry getFileOrDirRec(char * name, TableEntry currEntry);
static TableEntry deleteEntryRec(char * name, TableEntry curr, bool * effectivelyDeleted, bool isDir, FAT table);
static void deleteAllFilesInDir(FAT table, TableEntry curr);
static void deleteAllSubDirectories(FAT table, TableEntry curr);
static FAT temporalCd(char * path, char buff[]);
static FAT navigateToDir(char * path,char buff[], bool ignoreLast);
static void deleteSubContent(FAT table);
static void printTableEntriesRec(TableEntry curr);

static int currFd = 0;
static int currDd = 1;
static int openCount = 0;

FAT root = NULL;
FAT cwd = NULL;

File openFiles[MAX_OPEN_FILES] = {0};

void initializeFileSystem() {
	root = newFileTable();
	cwd = root;
}


int validateName(char * name) {
	return strcmp(name, "") && strchr(name, '/') == NULL && strchr(name, '.') == NULL;
}

char * explorePath(char * path, char buff[], bool * hasEnded) {
	int i;
	for(i = 0; *path != '\0' && *path != '/' && i < MAX_NAME_SIZE - 1; path++, i++) {
		buff[i] = *path;
	}
	if(*path == '\0' || (*path == '/' && *(path+1) == '\0'))
		*hasEnded = TRUE;
	buff[i] = '\0';
	return (!(*hasEnded)) ? path+1 : path-i;
}

FAT temporalCd(char * path, char buff[]) {
	FAT aux = navigateToDir(path, buff, TRUE);
	if(aux == NULL)
		return NULL;
	return aux; 
}

int cd(char * path) {
	char buff[MAX_NAME_SIZE] = {0};
	FAT aux = navigateToDir(path, buff, FALSE);
	if(aux == NULL)
		return -1;
	cwd = aux;
	return 1;
}

void ls() {
	putString("Subdirectories:\n\n");
	printTableEntriesRec(cwd->firstDir);
	putString("Files:\n\n");
	printTableEntriesRec(cwd->firstFile);
}

int touch(char * path) {
	char * name = malloc(MAX_NAME_SIZE);
	FAT aux = temporalCd(path, name);
	if(aux == NULL)
		return BAD_DIR;
	addFileEntry(name, aux);
	return TRUE;
}

int mkdir(char * path) {
	char * name = malloc(MAX_NAME_SIZE);
	FAT aux = temporalCd(path, name);
	if(aux == NULL)
		return BAD_DIR;
	addDirEntry(name, aux);
	return TRUE;
}

int rm(char * path, int isDir) {
	if(strcmp(path, "/") == 0)
		return ROOT_RMV_ERR;
	char name[MAX_NAME_SIZE] = {0};
	FAT aux = temporalCd(path, name);
	if(aux == NULL)
		return BAD_DIR;
	if(isDir)
		return deleteDir(name, aux);
	else
		return deleteFile(name, aux);
}

void printTableEntriesRec(TableEntry curr) {
	if(curr == NULL) {
		putString("\n\n");
		return;
	}
	putString("   ");
	putString(curr->name);
	printTableEntriesRec(curr->next);
}

int getFileDetails(char * path) {
	char buff[MAX_NAME_SIZE] = {0};
	File f = (File)findFileOrDir(path, buff, !IS_DIR);
	if(f == NULL)
		return FILE_NOT_FOUND;
	putString("Name: ");
	putString(f->name);
	putString("\n");
	putString("Size: ");
	printDecimal(f->size);
	putString(" Bytes\n");
	putString("Status: ");
	putString((f->openMode == NOT_OPEN) 
		? "Not open" : (f->openMode == READ) ? "Being read" : "Being written");
	putString("\n");
	return TRUE;
}

FAT navigateToDir(char * path, char buff[], bool ignoreLast) {
	if(path == NULL || path[0] == '\0')
		return NULL;
	if(path[0] == '/' && path[1] == '\0') {
		return root;
	}
	if(path[0] == '.' && path[1] == '.') {
		if(cwd != root)
			cwd = cwd->parentDir;
		return cwd;
	}
	Dir aux;
	bool hasEnded = FALSE;
	FAT currentDirTable = (path[0] != '/') ? cwd : root;
	if(path[0] == '/')
		path++;
	do {
		path = explorePath(path, buff, &hasEnded);
		if(!hasEnded || !ignoreLast) {
			aux = getDir(buff, currentDirTable);
			if(aux == NULL)
				return NULL;
			currentDirTable = aux->table;
		}
	} while(!hasEnded);
	return currentDirTable;
}

void * findFileOrDir(char * path, char buff[], bool isDir) {
	if(path == NULL || path[0] == '\0')
		return NULL;
	if(path[0] == '/' && path[1] == '\0')
		return NULL;
	bool hasEnded = FALSE;
	FAT currentDirTable = (path[0] != '/') ? cwd : root;
	if(path[0] == '/')
		path++;
	while((path = explorePath(path, buff, &hasEnded)) && !hasEnded) {
		Dir aux = getDir(buff, currentDirTable);
		if(aux == NULL)
			return NULL;
		currentDirTable = aux->table;
	}
	int length = strlen(buff);
	if(buff[length-1] == '/')
		buff[length-1] = '\0';
	if(isDir)
		return (void *) getDir(buff, currentDirTable);
	return (void *) getFile(buff, currentDirTable);
}

Dir getDir(char * name, FAT table) {
	TableEntry ret = getFileOrDirRec(name, table->firstDir);
	if(ret == NULL)
		return NULL;
	return (Dir)(ret->entry);
}

File getFile(char * name, FAT table) {
	TableEntry ret = getFileOrDirRec(name, table->firstFile);
	if(ret == NULL)
		return NULL;
	return (File)(ret->entry);
}

TableEntry getFileOrDirRec(char * name, TableEntry currEntry) {
	if(currEntry == NULL)
		return NULL;
	if(strcmp(currEntry->name, name) == 0) {
		return currEntry;
	}
	return getFileOrDirRec(name, currEntry->next);
}

FAT newFileTable() {
	FAT ret = malloc(sizeof(FATCDT));
	ret->firstFile = ret->firstDir = NULL;
	ret->fileCount = ret->subDirCount = 0;
	ret->parentDir = cwd;
	return ret;
}

File newFile(char * name) {
	File ret = malloc(sizeof(FileCDT));
	ret->fd = currFd++;
	ret->name = name;
	ret->size = 0;
	ret->openMode = NOT_OPEN;
	ret->fileContent = NULL;
	return ret;
}

Dir newDir(char * name) {
	Dir ret = malloc(sizeof(DirCDT));
	ret->dd = currDd++;
	ret->name = name;
	ret->table = newFileTable();
	return ret;
}

TableEntry addFileEntry(char * name, FAT table) {
	if(table != NULL && validateName(name)) {
		TableEntry aux = table->lastFile;
		if(aux == NULL) {
			table->firstFile = malloc(sizeof(TableEntryCDT));
			table->lastFile = table->firstFile;
		}
		else {
			aux->next = malloc(sizeof(TableEntryCDT));
			table->lastFile = aux->next;
		}
		table->lastFile->name = name;
		table->lastFile->entry = (void *) newFile(name);
		table->lastFile->next = NULL;
		table->fileCount++;
		return table->lastFile;
	}
	return NULL;
}

TableEntry addDirEntry(char * name, FAT table) {
	if(table != NULL && validateName(name)) {
		TableEntry aux = table->lastDir;
		if(aux == NULL) {
			table->firstDir = malloc(sizeof(TableEntryCDT));
			table->lastDir = table->firstDir;
		}
		else {
			aux->next = malloc(sizeof(TableEntryCDT));
			table->lastDir = aux->next;
		}
		table->lastDir->name = name;
		table->lastDir->entry = (void *) newDir(name);
		table->lastDir->next = NULL;
		table->subDirCount++;
		return table->lastDir;
	}
	return NULL;
}

/*TableEntry addEntryRec(char * name, bool isDir, TableEntry curr) {
	if(curr == NULL) {
		TableEntry ret = malloc(sizeof(TableEntryCDT));
		if(!isDir)
			ret->entry = (void *) newFile(name);	
		else
			ret->entry = (void *) newDir(name);
		ret->next = NULL;
		ret->name = name;
		return ret;
	}
	curr->next = addEntryRec(name, isDir, curr->next);
	return curr;
}*/

int deleteFile(char * name, FAT table) {
	if(table == NULL)
		return -2;
	bool effectivelyDeleted = FALSE;
	table->firstFile = deleteEntryRec(name, table->firstFile, &effectivelyDeleted, FALSE, table);
	if(effectivelyDeleted) {
		table->fileCount--;
		return 1;
	}
	return -1;
}

int deleteDir(char * name, FAT table) {
	if(table == NULL)
		return -2;
	bool effectivelyDeleted = FALSE;
	table->firstDir = deleteEntryRec(name, table->firstDir, &effectivelyDeleted, TRUE, table);
	if(effectivelyDeleted) {
		table->subDirCount--;
		return 1;
	}
	return -1;
}

TableEntry deleteEntryRec(char * name, TableEntry curr, bool * effectivelyDeleted, bool isDir, FAT table) {
	if(curr == NULL)
		return NULL;
	if(strcmp(curr->name, name) == 0) {
		if(isDir) {
			deleteSubContent(((Dir)(curr->entry))->table);
			if(cwd == ((Dir)(curr->entry))->table)
				cwd = root;
		}
		free(curr->entry);
		TableEntry aux = curr->next;
		free(curr);
		*effectivelyDeleted = TRUE;
		return aux;
	}
	bool lastElemReached = FALSE;
	if(curr->next != NULL && curr->next->next == NULL)
		lastElemReached = TRUE;
	curr->next = deleteEntryRec(name, curr->next, effectivelyDeleted, isDir, table);
	if(lastElemReached && curr->next == NULL) {
		if(isDir)
			table->lastDir = curr;
		else
			table->lastFile = curr;
	}
	return curr;
}

void deleteSubContent(FAT table) {
	deleteAllFilesInDir(table, table->firstFile);
	deleteAllSubDirectories(table, table->firstDir);
}

void deleteAllFilesInDir(FAT table, TableEntry curr) {
	if(curr == NULL)
		return;
	TableEntry aux = curr->next;
	free(curr->entry);
	free(curr);
	table->fileCount--;
	deleteAllFilesInDir(table, aux);
}

void deleteAllSubDirectories(FAT table, TableEntry curr) {
	if(curr == NULL)
		return;
	TableEntry aux = curr->next;
	deleteAllFilesInDir(((Dir)(curr->entry))->table, (((Dir)(curr->entry)))->table->firstDir);
	free(((Dir)(curr->entry))->table);
	free(curr);
	table->subDirCount--;
	deleteAllSubDirectories(table, aux);
}

int open(char * path, const char * mode) {
	if(openCount == MAX_OPEN_FILES)
		return FILE_CAP_REACHED;
	char buff[MAX_NAME_SIZE] = {0};
	File file = findFileOrDir(path, buff, !IS_DIR);
	if(file == NULL)
		return FILE_NOT_FOUND;
	if(file->openMode != NOT_OPEN)
		return FILE_OPEN;
	bool validMode = FALSE;
	if(strcmp(mode, "r") == 0) {
		file->openMode = READ;
		validMode = TRUE;
	}
	else if(strcmp(mode, "w") == 0) {
		file->openMode = WRITE;
		validMode = TRUE;
	}
	if(!validMode)
		return INVALID_MODE;
	int i;
	for(i = 0; i < MAX_OPEN_FILES; i++) {
		if(openFiles[i] == NULL) {
			openFiles[i] = file;
			openCount++;
			return i;
		}
	}
	return -1;
}

int validateId(int id) {
	if(openCount == 0)
		return NO_OPEN_FILES;
	if(id >= MAX_OPEN_FILES || id < 0)
		return INVALID_ID;
	if(openFiles[id] == NULL)
		return FILE_NOT_OPEN;
	return TRUE;
}

int validateBlocks(size_t blockSize, size_t blockNum, bool mode) {
	if(blockSize <= 0 || blockNum <= 0)
		return ERR_NGTV;
	if(mode == WRITE) {
		if(blockSize * blockNum > MAX_FILE_SIZE)
			return ERR_CAP_REACHED;
	}
	return TRUE;
}

int close(int id) {
	int idValidation = validateId(id);
	if(!(idValidation == TRUE))
		return idValidation;
	openFiles[id]->openMode = NOT_OPEN; 
	openFiles[id] = NULL;
	openCount--;
	return TRUE;
}

int read(void * dest, size_t blockSize, size_t blockNum, int fileId) {
	int idValidation = validateId(fileId);
	if(idValidation != TRUE)
		return idValidation;
	int blockValidation = validateBlocks(blockSize, blockNum, READ);
	if(blockValidation != TRUE)
		return blockValidation;
	File file = openFiles[fileId];
	if(file->openMode != READ)
		return INVALID_MODE;
	int i, j;
	for(i = 0; i < blockNum && (i+1) * blockSize < file->size; i++) {
		memcpy(dest + i * blockSize,
			file->fileContent + i * blockSize, blockSize);
	}
	if(blockNum * blockSize > file->size) {
		for(j = 0; j < blockSize && ((char *)file->fileContent)[j] != EOF; j++) {
			memcpy(dest + i * blockSize + j,
				file->fileContent + i * blockSize + j, 1);
		}
	}
	return i * blockSize + j;
}

int write(void * src, size_t blockSize, size_t blockNum, int fileId) {
	int idValidation = validateId(fileId);
	if(idValidation != TRUE)
		return idValidation;
	int blockValidation = validateBlocks(blockSize, blockNum, WRITE);
	if(blockValidation != TRUE)
		return blockValidation;
	File file = openFiles[fileId];
	if(file->openMode != WRITE)
		return INVALID_MODE;
	free(file->fileContent);
	file->fileContent = malloc(blockSize * blockNum + 1);
	int i;
	for(i = 0; i < blockNum; i++) {
		memcpy(file->fileContent + i * blockSize,
			src + i * blockSize, blockSize);
	}
	((char *)(file->fileContent))[blockSize * blockNum] = EOF;
	file->size = blockSize * blockNum + 1;
	return blockSize * blockNum;
}
