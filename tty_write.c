#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main (int argc, char **argv)
{
    
    char tty_addr[9];
    snprintf(tty_addr, 10, "/dev/%s", argv[1]);
    
    
    FILE* tty = fopen(tty_addr, "w");
    
    //printf("%s\n", tty_addr);
    for (int i = 2; i < argc; i++)
    {
        fprintf(tty, "%s", argv[i]);
    }
    //fprintf(tty, "\n");
    //free(tty_addr);
    fclose(tty);
}