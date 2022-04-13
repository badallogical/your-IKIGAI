#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char passion[100][100];
    char mission[100][100];
    char profession[100][100];
    char job[100][100];
    char your_ikagai[100][100];
} Ans;

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0); /* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/

    wrefresh(local_win); /* Show that box 		*/

    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wclear(local_win);
    wrefresh(local_win);
    delwin(local_win);
}

Ans ikagai(char goodAt[][100], char loveDoing[][100], char earnFrom[][100], char useful[][100])
{

    Ans life_ans;

    int match1 = 0;
    int match2 = 0;
    int match3 = 0;

    int p = 0;
    int m = 0;
    int j1 = 0;

    // intesect 1 and 2 ( mission )
    for (int i = 0; strcmp(goodAt[i], "done") != 0; i++)
    {
        for (int j = 0; strcmp(loveDoing[j], "done") != 0; j++)
        {
            if (strcmp(goodAt[i], loveDoing[j]) == 0)
            {
                strcpy(life_ans.mission[match1++], goodAt[i]);
            }
        }
    }

    // passion
    for (int i = 0; strcmp(loveDoing[i], "done") != 0; i++)
    {
        for (int j = 0; strcmp(useful[j], "done") != 0; j++)
        {
            if (strcmp(loveDoing[i], useful[j]) == 0)
            {
                strcpy(life_ans.passion[p++], useful[j]);
            }
        }
    }

    // Job or Profession
    for (int i = 0; strcmp(goodAt[i], "done") != 0; i++)
    {
        for (int j = 0; strcmp(earnFrom[j], "done") != 0; j++)
        {
            if (strcmp(goodAt[i], earnFrom[j]) == 0)
            {
                strcpy(life_ans.job[j1++], goodAt[i]);
            }
        }
    }

    // intersect 1 2, and 3 (Happy Profession)
    for (int i = 0; i < match1; i++)
    {
        for (int j = 0; strcmp(earnFrom[j], "done") != 0; j++)
        {
            if (strcmp(life_ans.mission[i], earnFrom[j]) == 0)
            {
                strcpy(life_ans.profession[match2++], earnFrom[j]);
            }
        }
    }

    // intersect 1,2,3 and 4 (all) i.e Meanig of life
    for (int i = 0; i < match2; i++)
    {
        for (int j = 0; strcmp(useful[j], "done") != 0; j++)
        {
            if (strcmp(life_ans.profession[i], useful[j]) == 0)
            {
                strcpy(life_ans.your_ikagai[match3++], useful[j]);
            }
        }
    }

    strcpy(life_ans.passion[p], "done");
    strcpy(life_ans.mission[match1], "done");
    strcpy(life_ans.job[j1], "done");
    strcpy(life_ans.profession[match2], "done");
    strcpy(life_ans.your_ikagai[match3], "done");

    return life_ans;
}

void clear_window(WINDOW *win)
{
    wclear(win);
    box(win, 0, 0); /* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
}

int main(int argc, char *argv[])
{

    initscr(); // initialize cursor mode
    refresh();

    int h = 16;
    int w = 55;
    int starty = 2;
    int startx = 5;

    char goodAt[100][100];
    char loveDoing[100][100];
    char earnFrom[100][100];
    char useful[100][100];

    Ans your_ikagai;

    move(1,12);
    attron(A_STANDOUT | A_BOLD);
    printw("IKAGAI : FIND MEANINIG OF YOUR LIFE");
    attroff(A_STANDOUT | A_BOLD);
    refresh();

    WINDOW *win1 = create_newwin(h, w, starty, startx);
    wmove(win1, 2, 2);
    wprintw(win1, "# Things in which you are good. ");
    wrefresh(win1);

    // input the things
    for (int i = 0; i < 10; i++)
    {
        wmove(win1, 4 + i, 2);
        wprintw(win1, "%d : ", i + 1);
        wgetstr(win1, goodAt[i]);
        if (strcmp(goodAt[i], "done") == 0)
        {
            break;
        }
    }

    WINDOW *win2 = create_newwin(h, w, starty, 2 * startx + w);
    wmove(win2, 2, 2);
    wprintw(win2, "# Things which you love to do and makes you happy. ");
    wrefresh(win2);

    // input the things
    for (int i = 0; i < 10; i++)
    {
        wmove(win2, 4 + i, 2);
        wprintw(win2, "%d : ", i + 1);
        wgetstr(win2, loveDoing[i]);
        if (strcmp(loveDoing[i], "done") == 0)
        {
            break;
        }
    }

    WINDOW *win3 = create_newwin(h, w, 2 * starty + h, startx);
    wmove(win3, 2, 2);
    wprintw(win3, "# Things from which you can earn money. ");
    wrefresh(win3);

    // input the things
    for (int i = 0; i < 10; i++)
    {
        wmove(win3, 4 + i, 2);
        wprintw(win3, "%d : ", i + 1);
        wgetstr(win3, earnFrom[i]);
        if (strcmp(earnFrom[i], "done") == 0)
        {
            break;
        }
    }

    WINDOW *win4 = create_newwin(h, w, 2 * starty + h, 2 * startx + w);
    wmove(win4, 2, 2);
    wprintw(win4, "# Things which you can do for the sack of world.");
    wrefresh(win4);

    // input the things
    for (int i = 0; i < 10; i++)
    {
        wmove(win4, 4 + i, 2);
        wprintw(win4, "%d : ", i + 1);
        wgetstr(win4, useful[i]);
        if (strcmp(useful[i], "done") == 0)
        {
            break;
        }
    }

    attron(A_STANDOUT | A_BOLD | A_COLOR);
    mvaddstr(h * 2 + 2 * 2, 6, "All set now we have all your answers, Let get excited !!!");

    your_ikagai = ikagai(goodAt, loveDoing, earnFrom, useful);

    getch();
    destroy_win(win1);
    destroy_win(win2);
    destroy_win(win3);
    destroy_win(win4);
    clear();

    mvaddstr(3, 5, "Let start");
    refresh();

    h = 20, w = 50;
    WINDOW *op_win = create_newwin(h, w, 4, 5);
    wattron(op_win, A_UNDERLINE | A_BOLD);
    wmove(op_win, 1, 3);
    wprintw(op_win, "# Choose your question please :)");
    wattroff(op_win, A_UNDERLINE);
    wattron(op_win, A_BOLD);
    mvwaddstr(op_win, 3, 3, "1.Passion");
    mvwaddstr(op_win, 4, 3, "2.Mission");
    mvwaddstr(op_win, 5, 3, "3.Profession");
    mvwaddstr(op_win, 6, 3, "4.Job");
    mvwaddstr(op_win, 7, 3, "5.Your IKAGAI ( Meaning of life )");
    mvwaddstr(op_win, 9, 3, "select number (1-5) : ");
    wrefresh(op_win);

    WINDOW *result_win = create_newwin(h, w, 4, 2 * 5 + w);
    wattron(result_win, A_UNDERLINE | A_BOLD);
    wmove(result_win, 1, 3);
    wprintw(result_win, "# Your Life Answers :)");
    wattroff(result_win, A_UNDERLINE);
    wattron(result_win,A_BLINK);
    wrefresh(result_win);

    char ch;
    do
    {
        wscanw(op_win, "%c", &ch);
        wmove(op_win, 9, 25);

        // Print the result in result window
        clear_window(result_win);
        wattron(result_win, A_UNDERLINE | A_BOLD);
        wmove(result_win, 1, 3);
        wprintw(result_win, "# Your Life Answers :)");
        wattroff(result_win, A_UNDERLINE);
        wrefresh(result_win);

        switch (ch)
        {
        case '1':
            mvwaddstr(result_win, 3, 3, "Your Passion can be =>");
            for (int i = 0; strcmp(your_ikagai.passion[i], "done") != 0; i++)
            {
                wmove(result_win, 4 + i, 3);
                wprintw(result_win, "%d: %s", i + 1, your_ikagai.passion[i]);
            }
            break;
        case '2':
            mvwaddstr(result_win, 3, 3, "Your Mission can be => ");
            for (int i = 0; strcmp(your_ikagai.mission[i], "done") != 0; i++)
            {
                wmove(result_win, 4 + i, 3);
                wprintw(result_win, "%d: %s", i + 1, your_ikagai.mission[i]);
            }
            break;
        case '3':
            mvwaddstr(result_win, 3, 3, "Your Profession can be => ");
            for (int i = 0; strcmp(your_ikagai.profession[i], "done") != 0; i++)
            {
                wmove(result_win, 4 + i, 3);
                wprintw(result_win, "%d: %s", i + 1, your_ikagai.profession[i]);
            }
            break;
        case '4':
            mvwaddstr(result_win, 3, 3, "Your Job can be =>");
            for (int i = 0; strcmp(your_ikagai.job[i], "done") != 0; i++)
            {
                wmove(result_win, 4 + i, 3);
                wprintw(result_win, "%d: %s", i + 1, your_ikagai.job[i]);
            }
            break;
        case '5':
            mvwaddstr(result_win, 3, 3, "Your IKAGAI is =>");
            for (int i = 0; strcmp(your_ikagai.your_ikagai[i], "done") != 0; i++)
            {
                wmove(result_win, 4 + i, 3);
                wprintw(result_win, "%d: %s", i + 1, your_ikagai.your_ikagai[i]);
            }
            break;
        case '0':
            mvwaddstr(result_win, 3, 3, "Thank you sir :)");
            break;

        default:
            break;
        }
        wrefresh(result_win);

    } while (ch != '0');

    getch();
    destroy_win(op_win);
    destroy_win(result_win);
    endwin();
    return 0;
}