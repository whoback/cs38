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
#include <vector>

const int MAP_HEIGHT = 20;
const int MAP_WIDTH = 50;
const int MAX_ITEMS = 10;

/* generic struct for items.
 items have names
 items have prices
 keep track of if this is in your inventory
 
 */
typedef struct item {
    int x = 0;
    int y = 0;
    char sign;
    std::string color;
    std::string name;
    std::string modifier; // used for things like old or dusty or blessed
    int price;
    int hasbeenpaidfor; //used to check if player is trying to steal item
}item;

struct player {
    std::string name;
    int y = 0;
    int x = 0;
    char sign;
    int turn = 0;
    int gold = 100;
    std::vector<item> inventory;
};


void init();
void initchars();
void initmapandhud();
void drawmap();
void end();
void loop();
void displayhud();
void introtext();
void inspect();
void genitems();
void placeitems();
int finditembylocation(std::array<item, MAX_ITEMS> arr);
void pickupitem();
std::string makeitemstring(int index, std::string s);


// the basic map
WINDOW * map;
// where stats are
WINDOW * hud;
// for text output from chars
WINDOW * logger;



player p;
player shop;

std::array<item, MAX_ITEMS> arrofitems;




//use for all our random number needs
std::random_device rd;
auto rdval = rd();
std::mt19937 ran(rdval);
auto ranval = ran();

//books items coffee
std::array<char, 3> itemsigns = {'b', 'I', 'c'};
//spellbook, gen items, coffee
std::array<int, 3> itemprices = {200, 25, 3};
std::array<std::string, 6> itemnames = {"spellbook", "coffee", "candle", "rope", "parchment", "bag"};
std::array<std::string, 7> itemcolors = {"magenta", "yellow", "black", "red", "white", "green", "blue"};
std::array<std::string, 5> itemmods = {"blessed", "cursed", "worn", "brilliant", "fragile"};

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
    getmaxyx(map, max_y, max_x);
    initchars();
    
    
    wmove(map, max_x/2, 0);
    waddch(map, p.sign);
    genitems();
    
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
    
    wmove(map, shop.y + 5, shop.x +2);
    waddch(map, 'b');
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
        placeitems();
        wnoutrefresh(map);
        wnoutrefresh(hud);
        wnoutrefresh(logger);
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
            // don't do anything this is just like nethack's commands ie wait
        }
        if(ch == 'i')
        {
            // looks at what the player is currently over on the map
            inspect();
        }
        if(ch == 'p')
        {
            pickupitem();
            
        }
    }
}

void displayhud()
{
    //clear hud
    werase(hud);
    //move to (x,y) of hud window
    wmove(hud, 0, 0);
    waddstr(hud, "You are: ");
    waddstr(hud, p.name.c_str());
    //print player location
    waddstr(hud, "\nLocation: ");
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
    p.x = 5;
    p.y = 1;
    shop.sign = '&';
    shop.x = max_x / 2;
    shop.y = max_y / 2;
    shop.name = names.at(ranval%25);
    shop.gold = 5000;
    
}

void introtext()
{
    
    printw("Welcome! \n Some quick information: \n 1. To move use the arrow keys\n 2. Quit at anytime by pressing q\n 3. Have fun!\n");
    printw("Do you want to play? y or n...");
    // this should be printed in the stdscrn before we create our map and hud
    while(1)
    {
        int ch = getch();
        if(ch == 'y')
        {
            clear();
            printw("What is your character name? ");
            //turn echo on to help user enter name
            echo();
            char n[120];
            getstr(n);
            
            p.name = n;
            refresh();
            noecho();
         
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
    //           lines, cols, beginy, beginx
    map = newwin(MAP_HEIGHT, MAP_WIDTH, 2, 0);
    hud  = newwin(5, MAP_WIDTH, MAP_HEIGHT+5, 0);
    logger = newwin(2, MAP_WIDTH, 0, 0);
    wrefresh(logger);
    wrefresh(hud);
    // give player an icon
    
    wrefresh(map);
}

void inspect()
{
    wclear(logger);
    //move cursor of logger to 0,0
    wmove(logger, 0, 0);
    
    //make sure we're moving within our map window
    int inspectedint = mvwinch(map, p.y, p.x) & A_CHARTEXT;
    std::string inspectoutput;
    char c = inspectedint;
    //do we have an actual item?
    if(c == 'b' || c == 'I' || c == 'c')
    {
        //get the actual item index as there could be multiples
        int index = finditembylocation(arrofitems);
        std::string s = "You see a ";
        std::string info = makeitemstring(index, s);
        
        
        waddstr(logger, info.c_str());
    }
     else inspectoutput = "You see a ";
    
    if(c == p.sign)
    {
        inspectoutput = "Theres nothing here!";
    }
    waddstr(logger, inspectoutput.c_str());
 
}

void genitems()
{
    int itemx = 1;
    int itemy = 11;
    
    for(int i = 0; i < arrofitems.size(); i++)
    {
        
        arrofitems.at(i).name = itemnames.at(ranval%6);
        
        //if we're a spellbook
        if(arrofitems.at(i).name == itemnames.at(0))
        {
            arrofitems.at(i).sign = itemsigns.at(0);
            
        }
        //if we're a coffee
        if(arrofitems.at(i).name == itemnames.at(1))
        {
            arrofitems.at(i).sign = itemsigns.at(2);
        }
        //then we're just an item
        if(arrofitems.at(i).name == itemnames.at(2) ||
           arrofitems.at(i).name == itemnames.at(3) ||
           arrofitems.at(i).name == itemnames.at(4) ||
           arrofitems.at(i).name == itemnames.at(5))
        {
            arrofitems.at(i).sign = itemsigns.at(1);
        }
        arrofitems.at(i).color = itemcolors.at(ranval%7);
        arrofitems.at(i).modifier = itemmods.at(ranval%5);
        
        // temp for now
        arrofitems.at(i).price = 25;
        
        //0 for not paid 1 for paid
        arrofitems.at(i).hasbeenpaidfor = 0;
        arrofitems.at(i).x = itemx;
        arrofitems.at(i).y = itemy;
        //itemy++;
        itemx++;
        ranval = ran();
        
    }
}
void placeitems()
{
 for(int i = 0; i < arrofitems.size(); i++)
 {
     wmove(map, arrofitems.at(i).y, arrofitems.at(i).x);
     waddch(map, arrofitems.at(i).sign);
     
     
 }
}

int finditembylocation(std::array<item, MAX_ITEMS> arr)
{
    //this is where player currently is
    std::pair<int, int> xy;
    xy.first = p.x;
    xy.second = p.y;
    int arrindex = 0;
    for(int i = 0; i < arrofitems.size(); i++)
    {
        if(arrofitems.at(i).x == xy.first && arrofitems.at(i).y == xy.second)
        {
            arrindex = i;
        }
        
    }
    
    return arrindex;
    
}
void pickupitem()
{
    wclear(logger);
    //move cursor of logger to 0,0
    wmove(logger, 0, 0);
    //index is where our item lives in the items array
    auto index = finditembylocation(arrofitems);
    // get the struct for our item from items array
    auto pickedupitem = arrofitems.at(index);
    //add struct to the vector
    p.inventory.push_back(pickedupitem);
    //use back cause we always want last added item for this
    std::string s = "You picked up a ";
    std::string output = makeitemstring(index, s);
    
    waddstr(logger, output.c_str());
    
}
std::string makeitemstring(int index, std::string s)
{
    
    s.append(arrofitems.at(index).modifier);
    s.append(" ");
    s.append(arrofitems.at(index).color);
    s.append(" ");
    s.append(arrofitems.at(index).name);
    s.append(" ");
    
    return s;
}
