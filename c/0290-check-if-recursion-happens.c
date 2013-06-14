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
    "detect_recursion_result_acpibin.txt",
    "detect_recursion_result_acpidump.txt",
    "detect_recursion_result_acpihelp.txt",
    "detect_recursion_result_acpinames.txt",
    "detect_recursion_result_acpisrc.txt",
    "detect_recursion_result_acpixtract.txt",
    "detect_recursion_result_iasl.txt",
    "detect_recursion_result_acpiexec.txt"
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

#define NUMBER_OF_TOOLS     8


int main(void)
{
    FILE                    *pFile;
    int                     lineNumber = 0;
    char                    mystring [MAX_LINE_LENGTH];
    int                     i;
    int                     counter;
    int                     max_counter;
    int                     user_choice;
    int                     issue_line = 0;
    int                     hit;


    printf ("\nNote:\n");
    printf ("Function whose invoke depth over %d will report warning!\n\n",
        THRESHOLD);

    printf ("We can analysis following tools:");
    while (1)
    {
        printf ("\nplease input the index of the tool you want to analysis\
            (0 for terminate).\n");

        for (i = 0; i < NUMBER_OF_TOOLS; i++)
        {
            printf ("Index %i - %s\n", (i + 1), tools[i]);
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

        printf ("Analysising %s, here is the result:\n", 
            tools[user_choice - 1]);

        pFile = fopen (files[user_choice - 1] , "rb");


        if (pFile == NULL)
        {
            perror ("Error opening file");
        }
        else
        {
            max_counter = 0;
            issue_line = 0;
            hit = 0;
            while (fgets (mystring , MAX_LINE_LENGTH , pFile) != NULL)
            {
                lineNumber ++;
                counter = 0;
                for (i = 0; i < strlen (mystring); i += 4)
                {
                    if (mystring[i] == ' ')
                    {
                        counter ++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (max_counter < counter)
                {
                    hit = 0;
                    max_counter = counter;
                    issue_line = lineNumber;
                }
                else if (max_counter == counter)
                {
                    hit++;
                }

                if (counter >= THRESHOLD)
                {
                    fprintf (stderr, 
                        "line%8d - depth%4d -  possible recursion issue\n",
                        lineNumber, counter);
                }
            }
            if (max_counter < THRESHOLD)
            {
                printf ("This tool is OK, no recursion issue.\n");
            }
            printf (
                "The maximum invoke depth - %4d hit %d times\n",
                max_counter, hit);
            printf ("The isseue locates in - %8d\n", issue_line);

            fclose (pFile);
        }
    }
    return 0;
}
