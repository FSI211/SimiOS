#define PANICNUM 2147483647
#define PANICBEGIN 1
#define PANICEND 0
#define PANIC kernel_panic

void togglepanic(int reason) {
    static const char* panicM;
    if(PANICNUM) {
        k_printf("KERNEL PANIC!!!!!!!, quit........", 5);
    }
} 