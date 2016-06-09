unsigned int ptrIndex = 0;
char *vidptr = (char*)0xb8000;
void print(char *string) {
	int i=0;
	while(string[i] != '\0') {
		vidptr[ptrIndex++] = string[i];
		vidptr[ptrIndex++] = 0x07;
		i++;
	}
}
