//
//  main.cpp
//  final
//
//  Created by Will Hoback on 7/18/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#include <iostream>
#include <ncurses.h>

typedef enum {
    right,
    left,
    up,
    down,
} direction;

constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 20;

void move(direction dir){
    
}

int main(int argc, const char * argv[]) {
    initscr(); // ncurses
    char player = '@';
    char s = ' ';
    int xloc = MAP_WIDTH / 2;
    int yloc = MAP_HEIGHT / 2;
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
        if(ch == KEY_RIGHT) yloc++;
        if(ch == KEY_LEFT) yloc--;
        if(ch == KEY_DOWN)
        {
            
             if(xloc == getmaxy(stdscr) - 1)
                 printw("max x");
            else
                xloc++;
            mvwaddch(stdscr,xloc,yloc,player);
            mvwaddch(stdscr, xloc-1, yloc-1, s);
        }
        if(ch == KEY_UP)
        {
            if(xloc == getbegy(stdscr) + 1)
                printw("beg y");
            else
            xloc--;
            mvwaddch(stdscr,xloc,yloc,player);
            mvwaddch(stdscr, xloc-1, yloc-1, s);
            refresh();
        }
    }
    endwin();
    return 0;
}
