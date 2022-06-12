/** @file main.c
 * main function for stringlist program
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
        printf("Please specifiy a ops file\n");
        exit(1);
    }

    // path to ops file
    char *opsFile = argsv[1];

    // open ops file for reading input
    FILE *OPS;
    if ((OPS = fopen(opsFile, "r")) == NULL)
    {
        printf("Problem opening key file '%s'; errno: %d\n", opsFile, errno);
        return 1;
    }

    list_t *list = create_empty_list();

    char *line = NULL;
    size_t lineSize = 255;
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
            printf("%d\n", size(list));
        }
        // add command
        else if (strncmp(cmd, "a", 1) == 0)
        {
            // size of string - indexes already searched
            char *string;
            string = (char *)malloc(64 * sizeof(char));
            if (string == NULL)
            {
                printf("error allocating memory\n");
                exit(1);
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
            add(list, string);
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
                printf("error allocating memory\n");
                exit(1);
            }
            int j = 0;
            while (itr != '\n')
            {
                string[j] = itr;
                ++j;
                ++i;
                itr = line[i];
            }
            add_at(list, string, index);
        }
        // get command
        else if (strncmp(cmd, "get", 3) == 0)
        {
            ++i;
            itr = line[i]; // should be number
            char number[1];
            number[0] = itr;

            int index = atoi(number);
            char *getString = get(list, index);
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
            char *result = remove_at(list, index);
            if (result == NULL)
            {
                printf("index out of Range. Cannot remove");
                exit(1);
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
            clear(list);
        }
    }

    // close the ops file
    fclose(OPS);
    // destory list
    clear(list);
    destroy_empty_list(list);
}
