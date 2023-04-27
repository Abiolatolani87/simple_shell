#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        char *prompt = "(ABshell) $ ";
        char *lineptr = NULL;
        size_t sizeb = 0;
        ssize_t newchar_read;

        (void)argc;
        (void)argv;

        while (1)
        {
                printf("%s", prompt);

                newchar_read = getline(&lineptr, &sizeb, stdin);

                if (newchar_read == -1)
                {
                        perror("getline");
                        return (-1);
                }
                printf("%s\n", lineptr);
                free(lineptr);
                lineptr = NULL;
                sizeb = 0;
}
return (0);
}
