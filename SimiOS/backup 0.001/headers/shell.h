// shell.h
#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 50

void help();
int strcmp(const char *str1, const char *str2);
void execute_command(char *command);
void read_command(char *command);

#endif