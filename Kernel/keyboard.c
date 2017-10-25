extern char read_key();

void printInput() {
	char input = read_key();
	if(input == 0)
		return;
	input -= 30;
	input += 'A';
	char * p = 0xB8000;
	*p = input;
	*(p+1) = 0xF2;
}