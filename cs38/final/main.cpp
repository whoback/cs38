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
void initmapandhud();
void drawmap();
void end();
void loop();
void displayhud();
void introtext();


const int MAP_HEIGHT = 20;
const int MAP_WIDTH = 40;

WINDOW * map;
WINDOW * hud;

struct player {
    std::string name;
    int y = 0;
    int x = 0;
    char sign;
    int turn = 0;
    int gold = 100;
};

player p;
player shop;

//use for all our random number needs
std::random_device rd;
auto rdval = rd();
std::mt19937 ran(rdval);
auto ranval = ran();

std::array<std::string, 3> items = {"Spellbooks", "Magic Items", "Coffee"};

//possible shopekeeper names some created by me and some taken from nethack
std::array<std::string, 25> names = {"Uze Bandi", "Bebe Pitolito", "Habibi Habeeb", "Njezjin", "Tsjernigof", "Ossipewsk", "Gorlowka", "Gomel", "Konosja", "Weliki Oestjoeg", "Syktywkar", "Sablja", "Narodnaja", "Kyzyl", "Walbrzych", "Swidnica", "Klodzko", "Raciborz", "Gliwice", "Brzeg", "Krnov", "Hradec Kralove", "Leuk", "Brig", "Sarnen"};

int startx, starty, width, height;
// keep track of borders
int max_y = 0;
int max_x = 0;

//draw border of our room
char wall = '#';

int main(int argc, const char * argv[])
{
    //start ncurses and show intro text to user
    init();
    
    introtext();
    initmapandhud();
    initchars();
    
    wmove(map, max_x/2, 0);
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
    delwin(hud);
    endwin();
    exit(0);
}

void loop()
{
    while(1)
    {
        //advance our turn
        ++p.turn;
        drawmap();
        displayhud();
        wnoutrefresh(map);
        wnoutrefresh(hud);
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
        if(ch == '.' || ch == ' ')
        {
            // don't do anything this is just like nethack's commands
        }
    }
}

void displayhud()
{
    //clear hud
    werase(hud);
    //move to (x,y) of hud window
    wmove(hud, 0, 0);
    //print player location
    waddstr(hud, "Location: ");
    waddstr(hud, std::to_string(p.x).c_str());
    waddstr(hud, ", ");
    waddstr(hud, std::to_string(p.y).c_str());
    waddch(hud, '\n');
    
    //print who our shopkeeper is
    waddstr(hud, "Shop owned by: ");
    waddstr(hud, shop.name.c_str());
    waddch(hud, '\n');
    
    //print turn number
    waddstr(hud, "Turn: ");
    waddstr(hud, std::to_string(p.turn).c_str());
    
    
}

void initchars()
{
    p.sign = '@';
    p.gold = 100;
    shop.sign = '&';
    shop.x = max_x / 2;
    shop.y = max_y / 2;
    shop.name = names.at(ranval%25);
    shop.gold = 5000;
    
}

void introtext()
{
    printw("Welcome! \n Some quick information: \n 1. To move use the arrow keys\n 2. Quit at anytime by pressing q\n 3. Have fun!");
    printw("Do you want to play? y or n...");
    // this should be printed in the stdscrn before we create our map and hud
    while(1)
    {
        int ch = getch();
        if(ch == 'y')
        {
            
            break;
        }
        if(ch == 'n' || ch == 'q')
        {
            end();
        }

    }
    
}

void initmapandhud()
{
    map = newwin(MAP_HEIGHT, MAP_WIDTH, 0, 0);
    hud  = newwin(5, MAP_WIDTH, MAP_HEIGHT+5, 0);
    getmaxyx(map, max_y, max_x);
    // give player an icon
    
    wrefresh(map);
}
