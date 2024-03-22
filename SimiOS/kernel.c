/*
 *
 * SimiOS Ver 0.001
 * 
 */

#include "SimiOSh/stdkernelio.h"
#include "SimiOSh/shell.h"
#include "SimiOSh/panic.h"
#include "SimiOSh/cursor/cursor.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define NULL 0
#define VERSION 0.001
#define SimiOSaddr 240711

#define cursorp CursorPosition
#define movecr moveCursorRight

#define TRUE 1
#define FALSE 0
#define BEGIN 1
#define END 0

#define GET k_get_char
#define PRINT k_printf
#define STRC strcmp
#define SHELP help

#define DO "do"
#define RUN "./"

static const char* ptr;

int _static_begining_os = TRUE;
int _static_reading_os = FALSE;
int _static_test_os = FALSE;

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

void help() {
    char *message = "Available commands:\nhelp - Display available commands\n";
    k_printf(message, 0);
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
            moveCursorRight();
        }
    }
}

// Funktion zum Ausführen des Befehls
void execute_command(const char *command) {
    // Hier können Sie die Logik zum Ausführen des Befehls implementieren
    // Zum Beispiel:
    if (STRC(command, "help") == 0) {
        SHELP();
    } else if (STRC(command, "exit") == 0) {
        k_printf("Exiting with exit code 0.", 24);
    } else {
        // Befehl nicht gefunden
        k_printf("Command not found.", 0);
    }
}



void k_main() 
{
    boot(0);
	_static_begining_os = TRUE;
    _static_reading_os = FALSE;
    _static_test_os = FALSE;

	if(_static_begining_os == TRUE) {
		sleep(10);
		k_clear_screen();        
		k_printf("Welcome to boot menu of SimiOS", 0);
		sleep(100);
		k_printf("We are getting everything ready for you!", 1);
		sleep(1000);
		k_printf("Thank you for running SimiOS!", 2);
		sleep(1000);
        k_printf("Executing Kernel files....", 3);
		sleep(100);
        k_printf("This could take a little bit...", 5);
        sleep(1000);
        k_printf("Executed successfull!, Exit Code: 0", 6);
        sleep(100);
		k_clear_screen();
        k_printf("Booted successfull! Exit Code: 0", 0);
    }
    else if(_static_reading_os == TRUE) {
        char command[MAX_COMMAND_LENGTH];
        while (1) {
            read_command(command);

            execute_command(command);
        }
    }
	else if(_static_test_os  == TRUE) {
		togglepanic("Panic", 1);
	}
};