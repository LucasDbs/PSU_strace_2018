#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// int main()
// {  
//         int i;

//         printf("Child pid = %d\n", getpid());
//         sleep(10);
//         for(i = 0;i < 10; ++i) {
//                 write(1, "In process\n", 11);
//                 kill(getpid(), SIGUSR1);
//         }
//         return 0;
// }

int main()
{
        int i;

        printf("pid = %d\n", getpid());
        sleep(10);
        // execve("/usr/ls", "/");
        for(i = 0;i < 10; ++i) {
                printf("My counter: %d\n", i);
                // kill(getpid(), SIGUSR1);
                sleep(2);
        }
        return 0;
}