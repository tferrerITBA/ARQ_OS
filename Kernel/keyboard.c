#include "keyboard.h"
#include "videoMode.h"
#include "functionGraph.h"

static unsigned index = 0;
//buffer circular
static unsigned char buffer[BUFFER_SIZE] = {0};
static unsigned char upperCase = 0;
//chequea que no se haya pulsado una tecla especial como Calculator
static unsigned char useless = 0;
//Todas las teclas
/*static char * characters[] = {0,"Esc","1","2","3","4","5","6","7","8","9","0","?","¿",
0,"Tab","q","w","e","r","t","y","u","i","o","p","´","+","\n","Ctrl","a","s","d",
"f","g","h","j","k","l","ñ","{","|","LShift","}","z","x","c","v",
"b","n","m",",",".","-","RShift","ImprPant","Alt"," ","CapsLock","F1","F2","F3","F4",
"F5","F6","F7","F8","F9","F10","Pausa","hola1","Inicio","up","RePg","Hola4","left","hola6",
"right","hola8","Fin","down","AvPg","Insert","Supr","j1","j2","<","F11","F12","w1","w2",
"Win","w4","RClick"};*/

static unsigned char characters[] = {0,0,'1','2','3','4','5','6','7','8','9','0',
'?',159,0,'\t','q','w','e','r','t','y','u','i','o','p',148,'+','\n',0,'a','s','d',
'f','g','h','j','k','l',209,'{','|',0,'}','z','x','c','v',
'b','n','m',',','.','-',0,0,0,' '};

static unsigned char altCharacters[] = {0,0,'!','"','#','$','%','&','/','(',')','=',
'\\',129,0,'\t','Q','W','E','R','T','Y','U','I','O','P',136,'*','\n',0,'A','S','D',
'F','G','H','J','K','L',177,'[',144,0,']','Z','X','C','V',
'B','N','M',';',':','_',0,0,0,' '};

void readInput() {
	/*char input = read_key();
	if(input == 0)
		return;
	input -= 30; //si apreto A, se imprime A
	input += 'A';
	buffer[index++] = input;
	writeToScreen(0xB8020, buffer[index-1], 0xF2);*/
}

int divideZero();

int divideZero() {
	int a = 1;
	int b = 0;
	return a / b;
}

void printInput() {
	unsigned char input = read_key();
	// key break signal: key+0x80
	if(input == 0 || (input > 0x80 && input != 0xAA && input != 0xB6))
		return;
	//special keys (like calculator)
	if(input == 0xE0) {
		useless = 1;
		return;
	}
	if(useless) {
		useless = 0;
		return;
	}
	//Insert, Supr, arrows, F1-F12, etc.
	if(input > 0x3A && input != 0x56 && input < 0x80)
		return;
	// backspace
	if(input == 0x0E) {
		buffer[index] = 0x08;
		index = (index < LAST_INDEX) ? index + 1 : 0;
		return;
	}
	//intro
	if(input == 0x1C) {
		buffer[index] = '\n';
		index = (index < LAST_INDEX) ? index + 1 : 0;
		return;
	}
	//0x3A CapsLock, 0x2A LShift, 0x36 RShift, 0xAA LShift release, 0xB6 RShift release
	if(input == 0x3A || input == 0x2A || input == 0x36 ||
			 input == 0xAA || input == 0xB6) {
		upperCase = !upperCase;
		return;
	}
	//Tab
	if(input == 0x0F) {
		buffer[index] = buffer[index+1] = buffer[index+2] = buffer[index+3] = ' ';
		index = (index < LAST_INDEX - 4) ? index + 4 : 0;
		return;
	}
	//LCtrl
	if(input == 0x1D || input == 0x37 || input == 0x38)
		return;
	if(!upperCase)
		buffer[index] = characters[input];
	else if(upperCase)
		buffer[index] = altCharacters[input];
	//'<' '>'
	if(input == 0x56) {
		if(!upperCase)
			buffer[index] = '<';
		else
			buffer[index] = '>';
	}
	
	mathFunc(0.05,5,-40);
	index = (index < LAST_INDEX) ? index + 1 : 0;
}

unsigned char getLastInsertion() {
	int i = (index > 0) ? index - 1 : LAST_INDEX;
	return buffer[i];
}

char * readBuffer(uint64_t rbx, char * str, uint64_t bufSize) {
	if(getLastInsertion() == 0)
		return 0x0;
	while(bufSize > 0) {
		index = (index > 0) ? index - 1 : LAST_INDEX;
		str[bufSize - 1] = buffer[index];
		buffer[index] = 0;
		bufSize--;
	}
	return str;
	/*if(!(getLastInsertion() == 0 || getLastInsertion() == '\n'))
		return 0x0;
	unsigned i = (index > 1) ? index - 2 : LAST_INDEX - 1 + index;
	while(buffer[i] != '\n' && buffer[i] != 0) {
		i = (i > 0) ? i - 1 : LAST_INDEX;
	}
	i = (i < LAST_INDEX) ? i + 1 : 0;
	unsigned j;
	for(j = 0; buffer[i] != '\n' && buffer[i] != 0 && j > bufSize; j++) {
		str[j] = buffer[i];
		i = (i < LAST_INDEX) ? i + 1 : 0;
	}
	return str;*/
}

void incrementIndex() {
	index = (index < LAST_INDEX) ? index + 1 : 0;
}
