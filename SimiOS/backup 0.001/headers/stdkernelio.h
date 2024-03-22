#define WHITE_TXT 0x07 /* light gray on black text */

void k_clear_screen();
void sleep();
unsigned int k_printf(char *message, unsigned int line);

// READ INPUTS: {
// Port einlesen (8 Bit)
unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ __volatile__("inb %w1, %b0" : "=a"(value) : "Nd"(port));
    return value;
}

// Port schreiben (8 Bit)
void outb(unsigned short port, unsigned char value) {
    __asm__ __volatile__("outb %b0, %w1" : : "a"(value), "Nd"(port));
}


// Read Inputs }

/* k_printf : the message and the line # */
unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=WHITE_TXT;
			i++;
		};
	};

	return(1);
}

void boot(int load) {
    k_printf("Initalizing Kernel, loading Kernel, booting Kernel...", 0);
}

void sleep(int seconds) {
    volatile int i = 0;
    while (i < (10000000 * seconds)) {
        i++;
    }
}

/* k_clear_screen : to clear the entire text screen */
void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};
