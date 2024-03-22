#define PANICNUM 2147483647
#define PANICBEGIN 1
#define PANICEND 0
#define PANIC kernel_panic

void togglepanic(char *reason, int line) {
    k_clear_screen();
    k_printf(reason, line);
}