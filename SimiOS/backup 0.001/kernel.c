/*
 *
 * SimiOS Ver 0.001
 * 
 */

#include "headers/stdkernelio.h"
#include "headers/shell.h"
#include "headers/panic.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define NULL 0
#define VERSION 0.001
#define TRUE 1
#define FALSE 0
#define BEGIN 1
#define END 0

int _static_begining_os = TRUE;
int _static_test_os = FALSE;

char k_get_char() {
    char character;

    // Warten bis ein Zeichen verfügbar ist
    while (!(inb(0x64) & 0x01)) {
        // Warten bis ein Zeichen verfügbar ist
    }

    // Zeichen von der Tastatur lesen
    character = inb(0x60); // Zeichen von Tastaturport lesen (PS/2-Tastatur)

    // Warten bis keine Taste mehr gedrückt wird
    while (inb(0x64) & 0x01) {
        // Warten bis keine Taste mehr gedrückt wird
    }

    return character;
}

void help() {
    char *message = "Available commands:\nhelp - Display available commands\n";
    k_printf(message, 0);
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

void execute_command(char *command) {
    if (strcmp(command, "help") == 0) {
        help();
    } else {
        char *message = "Command not found. Type 'help' for available commands.\n";
        k_printf(message, 0);
    }
}

void read_command(char *command) {
    int index = 0;
    char c;

    while (1) {
        c = k_get_char();
        k_printf(&c, 24); // Zeigt das eingegebene Zeichen an

        if (c == '\n' || c == '\r') {
            k_printf("\n", 24); // Neue Zeile nach der Eingabe
            command[index] = '\0';
            return;
        } else {
            command[index++] = c;
        }
    }
}

void moveCursorLine(int line) {
    // Die VGA-Hardware verwendet einen 80-Zeichen-Bildschirm
    // und der Textmodus hat normalerweise 25 Zeilen.
    // Wir müssen also sicherstellen, dass 'line' im gültigen Bereich liegt.
    if (line < 0 || line >= 25) {
        // Fehlerbehandlung für ungültige Zeilennummer
        return;
    }

    // Berechne die Cursorposition für die gegebene Zeile
    unsigned short position = (unsigned short)(line * 80);

    // Teilen Sie die Cursorposition in das niedrigere und höhere Byte auf
    unsigned char low_byte = (unsigned char)(position & 0xFF);
    unsigned char high_byte = (unsigned char)((position >> 8) & 0xFF);

    // Schreiben Sie den niedrigeren Byte-Wert an den VGA-Controller-Port
    outb(0x3D4, 0x0F); // Wählen Sie das Niedriger-Byte-Kommando (14) aus
    outb(0x3D5, low_byte);

    // Schreiben Sie den höheren Byte-Wert an den VGA-Controller-Port
    outb(0x3D4, 0x0E); // Wählen Sie das Höher-Byte-Kommando (15) aus
    outb(0x3D5, high_byte);
}











/* simple kernel written in C */
void k_main() 
{
    boot(0);
	_static_begining_os = FALSE;
	if(_static_begining_os == TRUE) {
		sleep(10000);
		k_clear_screen();
		k_printf("Welcome to boot menu of SimiOS", 0);
		sleep(100);
		k_printf("We are getting everything ready for you!", 1);
		sleep(10000);
		k_printf("Thank you for running SimiOS!", 2);
		sleep(1000);
		k_printf("Booted successfull!", 3);
		sleep(30000);
		k_clear_screen();
	}
	else if(_static_test_os  == TRUE) {
		togglepanic(0);
	}
	else {
		char command[MAX_COMMAND_LENGTH];

		while (1) {
			k_printf("SimiTerm>> ", 24); // Ausgabe der Eingabeaufforderung
			read_command(command); // Benutzereingabe lesen
			execute_command(command); // Eingegebenen Befehl ausführen
		}		
	}

};