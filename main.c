/** @file main.c
 * main function for stringlist program. This main routing is classic input loop that takes in a file of commands
 * and outputs the results based on the commands.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

int main(int argc, char **argsv)
{

    // checks if command file was specififed
    if (argc != 2)
    {
        fprintf(stderr, "Please specifiy a ops file\n");
        exit(EXIT_FAILURE);
    }

    // path to ops file
    char *opsFile = argsv[1];

    // open ops file for reading input
    FILE *OPS;
    if ((OPS = fopen(opsFile, "r")) == NULL)
    {
        fprintf(stderr, "Problem opening key file '%s'; errno: %d\n", opsFile, errno);
        exit(EXIT_FAILURE);
    }

    // Initalize Variables
    list_t *list = list_create();
    if (list == NULL)
    {
        fprintf(stderr, "Error allocating memory with malloc");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;     // Variable to contain line returned from getline
    size_t lineSize = 255; // line buffer size
    ssize_t read;

    // iterates through opsFile 1 line at a time
    while ((read = getline(&line, &lineSize, OPS)) != -1)
    {
        // read set of characters until space
        int i = 0;
        char itr = line[i];
        char cmd[10]; // max command size
        while ((itr != ' ') && (itr != '\n'))
        {
            cmd[i] = itr;
            ++i;
            itr = line[i];
        }

        // size command
        if (strncmp(cmd, "s", 1) == 0)
        {
            printf("%d\n", list_size(list));
        }

        // add command
        else if (strncmp(cmd, "a", 1) == 0)
        {
            // size of string - indexes already searched
            char *string;
            string = (char *)malloc(64 * sizeof(char));
            if (string == NULL)
            {
                fprintf(stderr, "error allocating memory\n");
                exit(EXIT_FAILURE);
            }
            int j = 0;
            i++;
            itr = line[i]; // move past space
            while (itr != '\n')
            {
                string[j] = itr;
                ++j;
                ++i;
                itr = line[i];
            }

            if (list_add(list, string) == 1)
            {
                fprintf(stderr, "Error allocating memory with malloc");
                exit(EXIT_FAILURE);
            }
        }
        // add_at command
        else if (strncmp(cmd, "add_at", 6) == 0)
        {
            ++i;
            itr = line[i]; // should be number
            int index = (int)itr;
            i += 2; // jump to next character
            itr = line[i];

            char *string;
            string = (char *)malloc(64 * sizeof(char));
            if (string == NULL)
            {
                fprintf(stderr, "error allocating memory\n");
                exit(EXIT_FAILURE);
            }
            int j = 0;
            while (itr != '\n')
            {
                string[j] = itr;
                ++j;
                ++i;
                itr = line[i];
            }

            int err = list_add_at(list, string, index);
            if (err == 1)
            {
                fprintf(stderr, "Error: index i out of range");
                exit(EXIT_FAILURE);
            }
            else if (err == 2)
            {
                fprintf(stderr, "Error allocating memory with malloc");
                exit(EXIT_FAILURE);
            }
        }
        // get command
        else if (strncmp(cmd, "get", 3) == 0)
        {
            ++i;
            itr = line[i]; // should be number
            char number[1];
            number[0] = itr;

            int index = atoi(number);
            char *getString = list_get(list, index);
            if (getString == NULL)
            {
                fprintf(stderr, "Error: Index i out of range");
                exit(EXIT_FAILURE);
            }
            printf("%s\n", getString);
        }
        // remove command
        else if (strncmp(cmd, "rm", 2) == 0)
        {
            ++i;
            itr = line[i]; // should be number
            char number[1];
            number[0] = itr;

            int index = atoi(number);
            char *result = list_remove_at(list, index);
            if (result == NULL)
            {
                fprintf(stderr, "index out of Range. Cannot remove");
                exit(EXIT_FAILURE);
            }
            else
            {
                // this frees the string memory allocated for each node
                free(result);
            }
        }
        // clear command
        else if (strncmp(cmd, "clear", 5) == 0)
        {
            list_clear(list);
        }
    }

    // close the ops file
    fclose(OPS);
    // destory list
    list_clear(list);
    list_destroy(list);
}
