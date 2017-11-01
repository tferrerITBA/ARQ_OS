#include "keyboard.h"

static short index = 0;
static char * screenPosition = (char *) 0xB8020;
static char * buffer[80 * 25] = {0};
static unsigned char upperCase = 0;
//Todas las teclas
/*static char * characters[] = {0,"Esc","1","2","3","4","5","6","7","8","9","0","?","¿",
0,"Tab","q","w","e","r","t","y","u","i","o","p","´","+","\n","Ctrl","a","s","d",
"f","g","h","j","k","l","ñ","{","|","LShift","}","z","x","c","v",
"b","n","m",",",".","-","RShift","ImprPant","Alt"," ","CapsLock","F1","F2","F3","F4",
"F5","F6","F7","F8","F9","F10","Pausa","hola1","Inicio","up","RePg","Hola4","left","hola6",
"right","hola8","Fin","down","AvPg","Insert","Supr","j1","j2","<","F11","F12","w1","w2",
"Win","w4","RClick"};*/

static unsigned char characters[] = {0,0,'1','2','3','4','5','6','7','8','9','0',
'?',0xA8,0,'\t','q','w','e','r','t','y','u','i','o','p',0xEF,'+','\n',0,'a','s','d',
'f','g','h','j','k','l',0xA4,'{','|',0,'}','z','x','c','v',
'b','n','m',',','.','-',0,0,0,' '};

static unsigned char altCharacters[] = {0,0,'!','"','#','$','%','&','/','(',')','=',
'?',0xAD,0,'\t','Q','W','E','R','T','Y','U','I','O','P',0xF9,'*','\n',0,'A','S','D',
'F','G','H','J','K','L',0xA5,'[','°',0,']','Z','X','C','V',
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

void printInput() {
	unsigned char input = read_key();
	if(input == 0 || (input > 0x80 && input != 0xAA && input != 0xB6))
		return;
	// backspace
	if(input == 0x0E) {
		screenPosition -= 2;
		deleteChar(screenPosition);
		return;
	}
	if(input == 0x1c) {
		//newLine();
		screenPosition = (char *)((unsigned)screenPosition + 160 - (unsigned)screenPosition % 80);
		return;
	}
	//0x3A CapsLock, 0x2A LShift, 0x36 RShift, 0xAA LShift release, 0xB6 RShift release
	if(input == 0x3A || input == 0x2A || input == 0x36 ||
			 input == 0xAA || input == 0xB6) {
		upperCase = !upperCase;
		return;
	}
	// key break signal
	/*if(input - 0x80 == buffer[index-1] + 2 - '1')
		return;*/
	if(!upperCase)
		buffer[index] = characters[input];//input - 2 + '1';
	else if(upperCase)
		buffer[index] = altCharacters[input];
	printOneChar(screenPosition, buffer[index], 0x0F);
	//writeToScreen(screenPosition, buffer[index], 0x0F);
	index = (index < 80 * 25) ? index + 1 : 0;
	screenPosition += 2;
}

