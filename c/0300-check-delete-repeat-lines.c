/*
 * To calculate the number of spaces before a line.
 * Coding style: all lines no more than 75 c.
 * Author: Chao Guan
 */
#include <stdio.h>
#include <string.h>

/* Large enough to make sure that it can contains a real long line */
#define MAX_LINE_LENGTH     1000
#define THRESHOLD           39
char                        *files[]=
{
    "recursive_acpibin.txt",
    "recursive_acpidump.txt",
    "recursive_acpihelp.txt",
    "recursive_acpinames.txt",
    "recursive_acpisrc.txt",
    "recursive_acpixtract.txt",
    "recursive_iasl.txt",
    "recursive_acpiexec.txt"
};

char                        *tools[]=
{
    "acpibin",
    "acpidump",
    "acpihelp",
    "acpinames",
    "acpisrc",
    "acpixtract",
    "iasl",
    "acpiexec"
};

char                        last_lines[10][MAX_LINE_LENGTH];

#define NUMBER_OF_TOOLS     8


int main(void)
{
    FILE                    *pFile;
    int                     lineNumber = 0;
    char                    mystring [MAX_LINE_LENGTH];
    int                     i;
    int                     user_choice;
    int                     find_same;
    int                     gbl_index = 0;


    printf ("For functions which has recursive behavior:\n\n\n");
    while (1)
    {
        fprintf (stderr, "\nplease input the index of the tool to analysis\
            (0 for terminate).\n");

        for (i = 0; i < NUMBER_OF_TOOLS; i++)
        {
            fprintf (stderr, "Index %i - %s\n", (i + 1), tools[i]);
        }

        scanf ("%d", &user_choice);
        if (!user_choice)
            return 0;

        if (user_choice > NUMBER_OF_TOOLS)
        {
            fprintf (stderr,
                "Invalid input, should no more than %d", NUMBER_OF_TOOLS);
            return -1;
        }

        printf ("\n\n%s:\n", 
            tools[user_choice - 1]);

        pFile = fopen (files[user_choice - 1] , "rb");


        if (pFile == NULL)
        {
            perror ("Error opening file");
        }
        else
        {
            while (fgets (mystring , MAX_LINE_LENGTH , pFile) != NULL)
            {
                lineNumber ++;
                for (i =0; i < 10; i ++)
                {
                    if ((strlen (last_lines[i]) != 0) & (strncmp (last_lines[i], mystring, 80) == 0))
                    {
                        find_same = 1;
                        break;
                    }
                    find_same = 0;
                }
                if (!find_same)
                {
                    strcpy (last_lines[((gbl_index++)%10)], mystring);
                    printf ("%s", mystring);
                }
            }

            fclose (pFile);
        }
    }
    return 0;
}
