//
//  main.cpp
//  final
//
// 0,0 is top left corner of screen
// most functions in ncurses are y,x not x,y

#include <iostream>
#include <ncurses.h>

void move(char dir, int &xloc, int &yloc){
    switch (dir) {
        case KEY_RIGHT:
            yloc++;
            break;
        case KEY_LEFT:
            yloc--;
            break;
        case KEY_UP:
            xloc--;
            break;
        case KEY_DOWN:
            xloc++;
            break;
        default:
            break;
    }
}

int main(int argc, const char * argv[])
{
    initscr(); // ncurses
    curs_set(0); // remove default cursor and only show @ icon
    // give player an icon
    char player = '@';
    // keep track of borders
    int max_y = 0;
    int max_x = 0;
    getmaxyx(stdscr, max_y, max_x);
    //char s = ' ';
    int xloc = max_x/2;
    int yloc = max_y/2;
    //draw border of our room
    char wall = '#';
    cbreak(); // don't buffer lines just use input
    keypad(stdscr, TRUE); // used for arrow keys
    noecho(); // don't echo char input
    box(stdscr, wall, wall);
    mvwaddch(stdscr,xloc,yloc,player);
    refresh();
    int ch = 1;
    // use enter to quit for testing
    while((ch = getch()) != 10)
    {
        if(ch == KEY_RIGHT)
        {
            xloc++;
            if(xloc > max_x - 2) // -2 for the wall
                xloc = max_x - 2;
            mvwaddch(stdscr,yloc,xloc,player);
            
        }
        if(ch == KEY_LEFT)
        {
            xloc--;
            if(xloc < 1)
                xloc = 1;
            mvwaddch(stdscr,yloc,xloc,player);
        }
        if(ch == KEY_DOWN)
        {
            yloc++;
            if(yloc > max_y-2)
                yloc = max_y-2;
            mvwaddch(stdscr,yloc,xloc,player);
        }
        if(ch == KEY_UP)
        {
            yloc--;
            if(yloc < 1)
                yloc = 1;
            mvwaddch(stdscr,yloc,xloc,player);
            
            refresh();
        }
    }
    endwin();
    return 0;
}
