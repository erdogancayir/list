#include "stdio.h"
#include "unistd.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <sys/signal.h>
# include <errno.h>
# include <fcntl.h>

int main()
{
    int fd[2];
    pipe(fd);
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int n = 5;
        write(fd[1], &n, sizeof(int));
        int arr[5] = {1, 2, 3, 4, 5};
        write(fd[1], arr, sizeof(int) * 5);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int sum = 0;
        int n;
        read(fd[0], &n, sizeof(int));
        int arr[n];
        read(fd[0], arr, sizeof(int) * n);
        int i = 0;
        for (i = 0; i < n; i++)
        {
            printf("n: %d\n", arr[i]);
            sum += arr[i];
        }
        printf("%d\n", sum);
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}