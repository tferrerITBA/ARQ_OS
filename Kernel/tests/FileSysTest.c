#include <stdio.h>
#include <stdlib.h>
#include "FAT.h"

extern FAT root;
extern FAT cwd;

int main(void) {

	initializeFileSystem();
	/*// explorePath	
	char * str = calloc(1, 50);
	strcpy(str, "home/patonn/descargas");
	unsigned char hasEnded = 0;
	char buff[255] = {0};
	do {
		str = explorePath(str, buff, &hasEnded);
		printf("str: %s\n", str);
		printf("buff: %s\n", buff);
	} while(!hasEnded);
	strcpy(str, "mnt");
	do {
		str = explorePath(str, buff, &hasEnded);
		printf("str: %s\n", str);
		printf("buff: %s\n", buff);
	} while(!hasEnded);

	printf("\n-----------------------------------------\n");
	
	//validateName
	printf("%d ", validateName(str));
	printf("%d ", validateName("holis"));
	printf("%d \n", validateName(""));

	printf("\n-----------------------------------------\n");
	*/
	//agregado y borrado
	addFileEntry("pepe", root);
	addFileEntry("pepe2", cwd);
	addDirEntry("pepeDir", root);
	printf("%s\n", ((File)(root->firstFile->entry))->name);
printf("%s\n", ((File)(cwd->lastFile->entry))->name);
addFileEntry("pepe3", root);
printf("%s\n", ((File)(cwd->lastFile->entry))->name);
	printf("%s\n", ((File)(root->firstDir->entry))->name);
	printf("FileCount: %d\n", cwd->fileCount);

	deleteFile("", root);
	printf("FileCount: %d (nothing deleted)\n", cwd->fileCount);
	deleteFile("pepe", root);
	printf("FileCount: %d (pepe deleted)\n", cwd->fileCount);
	addFileEntry("pepe4", root);
	printf("FileCount: %d (pepe4 added)\n", cwd->fileCount);
	deleteFile("pepe4", root);
	printf("FileCount: %d (pepe4 deleted)\n", cwd->fileCount);
	addDirEntry("pepeDir2", root);

	printf("\n-----------------------------------------\n");

	//navegacion
	printf("en root:\n");
	ls();
	printf("\n");
	printf("en pepeDir:\n");
	cd("/pepeDir");
	addFileEntry("pepe5", cwd);
	addDirEntry("pepeDir3", cwd);
	ls();
	printf("\n");
	printf("en root de nuevo:\n");
	cd("..");
	cd(".."); // haciendo .. en root
	ls();
	char buff[50] = {0};
	File f = (File)findFileOrDir("pepeDir/pepe0", buff, FALSE);
	printf("%s\n", (f != NULL) ? f->name : "Null");
	f = (File)findFileOrDir("pepeDir/pepe5", buff, FALSE);
	printf("%s\n", (f != NULL) ? f->name : "Null");
	cd("..");

	printf("\n-----------------------------------------\n");
	
	// open, close, read, write
	int open1 = open("pepeDir/pepe5", "w");
	close(open1);
	open1 = open("pepeDir/pepe5", "w");
	char * hello = "Hello world!";
	int status = write(hello, 14, 1, open1);
	close(open1);
	open1 = open("pepeDir/pepe5", "r");
	char buffer[MAX_FILE_SIZE] = {0};
	status = read(buffer, 7, 2, open1);
	printf("Read: %s\n", buffer);
	printf("pepe5 info: \n");
	getFileDetails("pepeDir/pepe5");
	close(open1);
	open1 = open("pepeDir/pepe5", "w");
	status = write("", 7, 2, open1);
	close(open1);
	open1 = open("/pepeDir/pepe5", "r");
	status = read(buffer, 7, 2, open1);
	printf("Despues del 2do read: %s\n", buffer);

	printf("Creando cosas en pepeDir/pepeDir3\n");
	touch("/pepeDir/pepeDir3/holis");
	mkdir("/pepeDir/pepeDir3/holisDir");
	touch("/pepeDir/pepeDir3/holis2");
	mkdir("/pepeDir/pepeDir3/holisDir2");
	cd("/pepeDir/");
	printf("Eliminando pepeDir3, desde pepeDir\n");
	rm("/pepeDir/pepeDir3", TRUE);
	ls();

	printf("\n-----------------------------------------\n");

	// borrado
	cd("/");
	rm("pepeDir", TRUE);
	ls();
	if(cwd == root)
		printf("No cambio el directorio porque pepeDir ya no existe.\n");
return 0;
} 
