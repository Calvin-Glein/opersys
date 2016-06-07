/*
*  kernel.c
*/

unsigned int i =0;
unsigned int j =0; 
char *vidptr = (char*)0xb8000; 	//video mem begins here.
int pos; 



static inline void outb(short port, char val){
asm volatile ("outb %0, %1": :"a"(val), "Nd"(port));
}


static inline char inb(short port){
	char ret;
	asm volatile ("inb %1, %0" :"=a"(ret): "Nd"(port));
	return ret;
}


void move_cursor(int position){

	outb(0x3D4, 0x0F);
	outb(0x3D5, position & 0xFF);

	outb(0x3D4, 0x0E);
	outb(0x3D5, position >> 8&0xFF);


}


void loadingscr(){

int x=0;
int y=0;
while(x!=10){
while(y!=1000){
y++;
}
x++;
}

}



void printc(char ch){
vidptr[i] = ch; 
vidptr[i+1] = 0x07;
i+=2;


}


void prints(char *str){   //function to print string

	char *str1 = str;
	/* this loop writes the string to video memory */
	while(str1[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str1[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = 0x07;
		++j;
		i = i + 2;
	}

}




void printi(int integer)
{
	int temp=0;
	int converter = 0;
	char *tempStr ="";
	char tempChar = ' ';
	j=0;
	while(integer != 0){
		converter = integer%10;
		if(converter ==0)
		{
			tempChar = '0';
		}
		if(converter ==1)
		{
			tempChar = '1';
		}
		if(converter ==2)
		{
			tempChar = '2';
		}
		if(converter ==3)
		{
			tempChar = '3';
		}
		if(converter ==4)
		{
			tempChar = '4';
		}
		if(converter ==5)
		{
			tempChar = '5';
		}
		if(converter ==6)
		{
			tempChar = '6';
		}
		if(converter ==7)
		{
			tempChar = '7';
		}
		if(converter ==8)
		{
			tempChar = '8';
		}
		if(converter ==9)
		{
			tempChar = '9';
		}
		tempStr[j] = tempChar;
		integer /= 10;
		j++;
	}
	tempStr[j] = '\0';
	j--;
	int k = j;
	j=0;
	while(tempStr[j]!= '\0')
	{
		printc(tempStr[k]);
		k--;
		j++;
		
	}
	j=0;

}

void printh(int integer)
{
	unsigned int k = 0;
	char *finalHex = "";
	int temp=0;
	char *tempStr = "";
	int converter = 0;
	char tempChar = ' ';
	while(integer != 0){
		temp = integer%16;
		integer /= 16;
		if(temp ==0)
		{
			tempChar = '0';
		}
		if(temp ==1)
		{
			tempChar = '1';
		}
		if(temp ==2)
		{
			tempChar = '2';
		}
		if(temp ==3)
		{
			tempChar = '3';
		}
		if(temp ==4)
		{
			tempChar = '4';
		}
		if(temp ==5)
		{
			tempChar = '5';
		}
		if(temp ==6)
		{
			tempChar = '6';
		}
		if(temp ==7)
		{
			tempChar = '7';
		}
		if(temp ==8)
		{
			tempChar = '8';
		}
		if(temp ==9)
		{
			tempChar = '9';
		}
		if(temp ==10)
		{
			tempChar = 'A';
		}
		if(temp ==11)
		{
			tempChar = 'B';
		}
		if(temp ==12)
		{
			tempChar = 'C';
		}
		if(temp ==13)
		{
			tempChar = 'D';
		}
		if(temp ==14)
		{
			tempChar = 'E';
		}
		if(temp ==15)
		{
			tempChar = 'F';
		}
		tempStr[k] = tempChar;
		k = k+1;
		tempChar = ' ';
	}
	tempStr[k] = '\0';
	k--;
	int l;
	l=k;
	j=0;
	while(tempStr[j]!='\0'){
		printc(tempStr[k]);
		j++;
		k--;
	}

	prints(finalHex);	

}


void clrscr(){
	i = 0;
	j = 0;

	/* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(j < 80 * 25 * 2) {
		/* blank character */
		vidptr[j] = ' ';
		/* attribute-byte - light grey on black screen */
		vidptr[j+1] = 0x07; 		
		j = j + 2;
	}

	i = 0;
	j = 0;

}


void printLine(char* string)
{
	const char *str = string;
	j = 0;




	
	/* this loop writes the string to video memory */
	while(str[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = 0x07;
		++j;
 		i = i + 2;
	}
}

unsigned char map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		


void space(){
	int x, y;
	
}

void kmain(void)
{
	int status;
	char key;
	clrscr();
	move_cursor(i/2);


	
	printLine("MyOS>");
	while(1){
		
		
		status =inb(0x64);
	
		if(status & 0x01){
				key = inb(0x60);

				if(key<0);
				else { 
					if(key==28){
						printLine("Enterkey");
					}
					else printc(map[key]);
					{
						move_cursor(i/2);
					}
				}
		}

	}


	return;
}






