#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main (int argc, char **argv)
{
    
    char* tty_addr = calloc(20, sizeof(char));
    tty_addr = strcat("/dev/", argv[1]);
    
    FILE* tty = fopen(tty_addr, "w");
    
    printf("%s\n", tty_addr);
    for (int i = 2; i < argc; i++)
    {
        fprintf(tty, "%s", argv[i]);
    }
    fprintf(tty, "\n");
    free(tty_addr);
    fclose(tty);
}