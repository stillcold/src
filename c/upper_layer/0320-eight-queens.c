#include <stdio.h>
#include <string.h>
/* Include this head file to use boolean type */
#include "mytypes.h"

/* This is not necessary, eight queens is for 8-checker chessboard */
#define CHECKERNUM          8
#define THREDHOLD           10

static int                  Gbl_answer[CHECKERNUM];
static int                  Gbl_counter;

boolean is_valid (int level, int offset);
void do_scan (int level);
void print_result (void);

/**************************************************************************
 *
 * Check if the move valid
 *
 *************************************************************************/
boolean is_valid (int level, int offset)
{
    int                     i;
    int                     right_leaning_offset;
    int                     left_leaning_offset;


    for (i = 0; i < CHECKERNUM; i++)
    {
        right_leaning_offset = i + offset - level;
        left_leaning_offset = offset + level - i;
        /* This is why eight-queens has answer */
        if ((right_leaning_offset <= 7) & (right_leaning_offset >= 0)
            & (Gbl_answer[i] == right_leaning_offset))
        {
            return FALSE;
        }
        if ((left_leaning_offset <= 7) & (left_leaning_offset >= 0)
            & (Gbl_answer[i] == left_leaning_offset))
        {
            return FALSE;
        }
        if (Gbl_answer[i] == offset)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void do_scan (int level)
{
    int                     i;


    for (i = 0; i < CHECKERNUM; i++)
    {
        if (is_valid(level, i))
        {
            Gbl_answer[level] = i;
            if (level == (CHECKERNUM -1))
            {
                Gbl_counter++;
                if (Gbl_counter < THREDHOLD)
                {
                    print_result();
                }
                /* Watch out here, that's why it is called backtrace */
                Gbl_answer[level] = -1;
                return;
            }
            do_scan (level+1);
            /* Watch out here, that's why it is called backtrace */
            Gbl_answer[level] = -1;
        }
    }
}

void print_result (void)
{
    int                     i;
    int                     j;


    for (i = 0; i < CHECKERNUM; i++)
    {
        for (j = 0; j < CHECKERNUM; j++)
        {
            if (j == Gbl_answer[i])
            {
                printf ("_ ");
            }
            else
            {
                printf (". ");
            }
        }
        printf ("\n");
    }
    printf ("\n");
}

int main (void)
{
    memset (Gbl_answer, -1, sizeof (Gbl_answer));
    do_scan(0);
    printf ("%d\n", Gbl_counter);

    return 0;
}
