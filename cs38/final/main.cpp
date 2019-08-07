//
//  main.cpp
//  final
//
// 0,0 is top left corner of screen
// most functions in ncurses are y,x not x,y

#include <iostream>
#include <ncurses.h>
#include <string>
#include <array>
#include <random>

void init();
void initchars();
void drawmap();
void end();
void loop();
void hud();



const int MAP_HEIGHT = 40;
const int MAP_WIDTH = 80;

WINDOW * map;
WINDOW * disp;

struct player {
    std::string name;
    int y = 0;
    int x = 0;
    char sign;
    int gold = 100;
};

struct storekeep {
    std::string name;
    int y = 0;
    int x = 0;
    char sign;
    int gold = 0;
};

player p;
storekeep shop;

std::random_device rd;
auto rdval = rd();
std::mt19937 ran(rdval);
auto ranval = ran();


std::array<std::string, 25> names = {"Uze Bandi", "Bebe Pitolito", "Habibi Habeeb", "Njezjin", "Tsjernigof", "Ossipewsk", "Gorlowka", "Gomel", "Konosja", "Weliki Oestjoeg", "Syktywkar", "Sablja", "Narodnaja", "Kyzyl", "Walbrzych", "Swidnica", "Klodzko", "Raciborz", "Gliwice", "Brzeg", "Krnov", "Hradec Kralove", "Leuk", "Brig", "Sarnen"};

int startx, starty, width, height;
// keep track of borders
int max_y = 0;
int max_x = 0;
//char s = ' ';
int xloc = (max_x / 2);
int yloc = (max_y / 2);
//draw border of our room
char wall = '#';

int main(int argc, const char * argv[])
{
    
    init();
    initchars();
    
    wmove(map, xloc, yloc);
    waddch(map, p.sign);
    wrefresh(map);
    loop();
    return 0;
}

void init()
{
    initscr(); // ncurses
    cbreak();
    noecho();
    raw();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE); // used for arrow keys
    noecho(); // don't echo char input
    curs_set(0); // remove default cursor and only show @ icon
    map = newwin(MAP_HEIGHT, MAP_WIDTH, 0, 0);
    disp  = newwin(5, MAP_WIDTH, MAP_HEIGHT+5, 0);
    getmaxyx(map, max_y, max_x);
    // give player an icon
 
    wrefresh(map);
    
}

void drawmap()
{
    //clear the map
    werase(map);
    //draw the border
    wborder(map, '|', '|', '-', '-', '+', '+', '+', '+');
    //move to player pos and draw player
    wmove(map, p.y, p.x);
    waddch(map, p.sign);
    
    //move to shopkeeper pos and draw shopkeeper
    wmove(map, shop.y, shop.x);
    waddch(map, shop.sign);
    wrefresh(map);
}

void end()
{
    clear();
    delwin(map);
    endwin();
    exit(0);
}

void loop()
{
    while(1)
    {
        drawmap();
        hud();
        wnoutrefresh(map);
        wnoutrefresh(disp);
        doupdate();
        int ch = getch();
        if(ch == KEY_RIGHT)
        {
            p.x++;
            if(p.x > max_x - 2) // -2 for the wall
                p.x = max_x - 2;
        }
        if(ch == KEY_LEFT)
        {
            p.x--;
            if(p.x < 1)
                p.x = 1;
        }
        if(ch == KEY_DOWN)
        {
            p.y++;
            if(p.y > max_y-2)
                p.y = max_y-2;
        }
        if(ch == KEY_UP)
        {
            p.y--;
            if(p.y < 1)
                p.y = 1;
        }
        if (ch == 'Q' || ch == 'q')
        {
            end();
        }
    }
}

void hud()
{
    std::string x = std::to_string(p.x);
    std::string y = std::to_string(p.y);
    std::string locs = std::to_string(max_x/2);
    locs += std::to_string(max_y/2);
    
    
    werase(disp);
    
    wmove(disp, 0, 0);
    
    waddstr(disp, "Current coordinates: ");
    waddstr(disp, x.c_str());
    waddstr(disp, ", ");
    waddstr(disp, y.c_str());
    waddch(disp, '\n');
    waddstr(disp, "Shopkeeper name: ");
    waddstr(disp, shop.name.c_str());
    waddch(disp, '\n');
    waddstr(disp, "XYLocs: ");
    waddstr(disp, locs.c_str());
}

void initchars()
{
    p.sign = '@';
    p.x = xloc;
    p.y = yloc;
    p.gold = 100;
    shop.sign = '&';
    shop.x = max_x / 2;
    shop.y = max_y / 2;
    shop.name = names.at(ranval%25);
    shop.gold = 5000;
    
}
