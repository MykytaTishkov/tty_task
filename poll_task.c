#include <stdio.h>
#include <time.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

int main(int argc, char **argv)
{

    struct pollfd poll_fds[2];
    /* Buffer state */
    int ready;
    /* Openning input file and check it */ 
    FILE *input = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r");
    if(input == NULL)
    {
        printf("Cannot open reading file\n");
        exit(1);
    }
    /* Openning output file and check it */ 
    char tty_addr[9];
    snprintf(tty_addr, 10, "/dev/%s", argv[1]);
    FILE *output = fopen(tty_addr, "w");
    if(output == NULL)
    {
        printf("Cannot open writing file\n");
        exit(1);
    }
    /* Setting poll structs */
    poll_fds[0].fd = fileno(input);
    poll_fds[0].events = POLLIN;

    poll_fds[1].fd = fileno(output);
    poll_fds[1].events = POLLOUT;

    
    ready = poll(poll_fds, 2, -1);
    
    if(ready == -1)
    {
        printf("Error");
    }

    

    while(1)
    {
        //sleep(1);
        //printf("Ready: %d\n", ready);
        ready = poll(poll_fds, 2, -1);
        if(ready == 2)
        {

            struct input_event ev;
            read(fileno(input), &ev, sizeof(ev));
            if(ev.value == 1)
            {
                fprintf(output, "Key: %i State: %i\n", ev.code, ev.value);
            }
            poll_fds[0].revents = 0;
            poll_fds[1].revents = 0;
            continue; 

        }else if(!(poll_fds[0].revents & POLLIN))
        {
            /* Logging stuff */
            //printf("Input is not ready\n");  
            poll_fds[0].revents = 0;  
            poll_fds[1].revents = 0;

        }else if(!(poll_fds[1].revents & POLLOUT))
        {

            printf("Output is not ready\n");
            poll_fds[1].revents = 0;

        }else if(ready == -1)
        {
            break;
            
        }

        

        
    }
    
    fclose(input);
    fclose(output);
    
    fprintf(output, "\n R-W is done- poll code: %d", ready);
    printf("\n End");


}