#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
/*
 * fork() will return 0 in child process, and PID of child process in parent.
 */

int main(void)
{
    pid_t pid;
    char *message;
    int n;
    int exit_code;

    printf("To see zombie process with fork.\n");
    pid = fork();
    switch (pid) {
    case -1:

        perror("Fork failed");
        exit(1);

    case 0:

        message = "This is the child.";
        n = 50;
        exit_code = 50;
        break;

    default:
        /*
         * To see the result of zombie in "ps -al", then the number here
         * has to be larger than the former.
         * This will make the parent end later than the child.
         * Thus, the child will becomes a zombie process.
         * And 50 or 30 senconds will make the user has enough time to use
         * "ps -al" and see the result. 
         */
        message = "This is the parent.";
        n = 30;
        exit_code = 0;
        break;
    }

    for (; n > 0; n--){
        puts(message);
        sleep(1);
    }

    /*
     * The code below will make the parent wait the child to exit.
     */
    if (pid != 0){
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished, PID= %d\n", child_pid);
        
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally.\n");
    }

    exit(exit_code);
}
