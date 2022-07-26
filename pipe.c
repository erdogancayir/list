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
#include "string.h"

static int	wordcounter(const char *p, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*p)
	{
		if (*p != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*p == c)
			trigger = 0;
		p++;
	}
	return (i);
}

static char	*worddup(const char *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	int		a;
	int		start;

	if (!s)
		return (0);
	i = -1;
	a = 0;
	start = -1;
	split = malloc(sizeof(char *) * (wordcounter(s, c) + 1));
	if (!split)
		return (0);
	while (++i <= strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == strlen(s)) && start >= 0)
		{
			split[a++] = worddup(s, start, i);
			start = -1;
		}
	}
	split[a] = NULL;
	return (split);
}

int main(int ac, char **av, char **env)
{
    int fd[2];
    if (pipe(fd) == -1) return 1;
    int id = fork();

    if (id == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execve("/usr/bin/ls", ft_split("ls -la", ' '), env);
    }
    int id2 = fork();
    if (id2 == 0)
    {
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        execve("/usr/bin/wc", ft_split("wc -l", ' '), env);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(id, NULL, 0);
    waitpid(id2, NULL, 0);
    return 0;
}