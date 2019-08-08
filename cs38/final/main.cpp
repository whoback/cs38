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
const int MAX_ITEMS = 25;

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
    int indexpos;
}item;

struct player {
    std::string name;
    int y = 0;
    int x = 0;
    char current;
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
void checkmovepos();
void angershopkeeper();
std::string makeitemstring(int index, std::string s);
void checkinventory();
void buyitem();
void additemtoinventory(int index);
char getcurchar();
char switchtotempchar();
// the basic map
WINDOW * map;
// where stats are
WINDOW * hud;
// for text output from chars
WINDOW * logger;



player p;
player shop;

//this holds our in game items
std::array<item, MAX_ITEMS> arrofitems;




//use for all our random number needs
std::random_device rd;
std::mt19937 rng(rd());    // random-number engine used
std::uniform_int_distribution<int> uni(0,5); // guaranteed unbiased
int random_integer = uni(rng);



//books items coffee
std::array<char, 3> itemsigns = {'b', 'I', 'c'};
//spellbook, gen items, coffee
std::array<int, 3> itemprices = {200, 25, 3};
std::array<std::string, 6> itemnames = {"spellbook", "coffee", "candle", "rope", "parchment", "bag"};
std::array<std::string, 6> itemcolors = {"magenta", "yellow", "black", "white", "green", "blue"};
std::array<std::string, 6> itemmods = {"blessed", "cursed", "worn", "brilliant", "fragile", "totally radical"};

//possible shopekeeper names some created by me and some taken from nethack
std::array<std::string, 25> names = {"Uze Bandi", "Bebe Pitolito", "Habibi Habeeb", "Njezjin", "Tsjernigof", "Ossipewsk", "Gorlowka", "Gomel", "Konosja", "Weliki Oestjoeg", "Syktywkar", "Sablja", "Narodnaja", "Kyzyl", "Walbrzych", "Swidnica", "Klodzko", "Raciborz", "Gliwice", "Brzeg", "Krnov", "Hradec Kralove", "Leuk", "Brig", "Sarnen"};

int startx, starty, width, height;
// keep track of borders
int max_y = 0;
int max_x = 0;

//draw border of our room
char wall = '#';
std::pair<int, char> holder = {-1, ' '};
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
            checkmovepos();
        }
        if(ch == KEY_LEFT)
        {
            p.x--;
            checkmovepos();
        }
        if(ch == KEY_DOWN)
        {
            p.y++;
            checkmovepos();
        }
        if(ch == KEY_UP)
        {
            p.y--;
            checkmovepos();
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
        if(ch == 'v')
        {
            checkinventory();
        }
        if(ch == 'b')
        {
            buyitem();
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
    waddch(hud, '\t');
    waddstr(hud, "Char: ");
    waddch(hud, p.current);
    waddch(hud, '\n');
    
    //print who our shopkeeper is
    waddstr(hud, "Shop owned by: ");
    waddstr(hud, shop.name.c_str());
    waddch(hud, '\n');
    
    //print turn number
    waddstr(hud, "Turn: ");
    waddstr(hud, std::to_string(p.turn).c_str());
    waddch(hud, '\n');
    //gold amount
    waddstr(hud, "Gold: ");
    waddstr(hud, std::to_string(p.gold).c_str());
    
    //inventory stat
    waddstr(hud, std::to_string(p.inventory.size()).c_str());
    waddstr(hud, " items in your inventory");
}

void initchars()
{
    //    std::uniform_int_distribution<int> name(0, names.size());
    //    random_integer = name(rng);
    p.sign = '@';
    p.gold = 100;
    p.x = 5;
    p.y = 1;
    
    shop.sign = '&';
    shop.x = max_x / 2;
    shop.y = max_y / 2;
    std::uniform_int_distribution<int> n(0,24);
    shop.name = names.at(n(rng));
    shop.gold = 5000;
    
}

void introtext()
{
    printw("Welcome! \n Some quick information: \n 1. To move use the arrow keys. \n'i' is inspect. \n'v' to see your inventory. \n'b' to buy. \n 2. Quit at anytime by pressing q\n 3. Have fun!\n");
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
            std::string playername;
            char s[100];
            getnstr(s, 99);
            playername = s;
            p.name = playername;
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
    //this is the char returned from mvwinch
    char c = inspectedint;
    //get the actual item index as there could be multiples
    int index = 0;
    index = finditembylocation(arrofitems);
    if(index == -1)
    {
        inspectoutput = "negative 1 ";
    }
    if(c == p.sign)
    {
        inspectoutput = "Theres nothing here!";
        waddstr(logger, inspectoutput.c_str());
    }
    else
    {
        //we have an actual item
        
        std::string s = "You see a ";
        std::string info = makeitemstring(index, s);
        
        waddstr(logger, info.c_str());
    }
    
}

void genitems()
{
    int itemx = 1;
    int itemy = 11;
    
    //generate names first
    for(int i = 0; i < arrofitems.size(); i++)
    {
        arrofitems.at(i).name = itemnames.at(uni(rng));
        arrofitems.at(i).hasbeenpaidfor = 0;
        arrofitems.at(i).modifier = itemmods.at(uni(rng));
        arrofitems.at(i).x = itemx;
        arrofitems.at(i).y = itemy;
        arrofitems.at(i).indexpos = i; //keep track of orig index
        itemx+=2;
        
        
    }
    //based on names generate attributes
    for(int i = 0; i < arrofitems.size(); i++)
    {
        if( arrofitems.at(i).name == "spellbook")
        {
            arrofitems.at(i).sign = itemsigns.at(0);
            arrofitems.at(i).color = itemcolors.at(uni(rng));
            arrofitems.at(i).price = itemprices.at(0);
        }
        else if( arrofitems.at(i).name == "coffee")
        {
            arrofitems.at(i).sign = itemsigns.at(2);
            arrofitems.at(i).color = itemcolors.at(2);
            arrofitems.at(i).price = itemprices.at(2);
            
        }
        else
        {
            arrofitems.at(i).sign = itemsigns.at(1);
            arrofitems.at(i).color = itemcolors.at(uni(rng));
            arrofitems.at(i).price = itemprices.at(1);
            
        }
        
    }
}
void placeitems()
{
    if(holder.first != -1)
    {
        //we know we have to change a item sign back
        arrofitems.at(holder.first).sign = holder.second;
    }
    for(int i = 0; i < arrofitems.size(); i++)
    {
        wmove(map, arrofitems.at(i).y, arrofitems.at(i).x);
        waddch(map, arrofitems.at(i).sign);
        
    }
}

int finditembylocation(std::array<item, MAX_ITEMS> arr)
{
    
    int arrindex = 0;
    //loop through array of items on the map
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr.at(i).x == p.x)
        {
            if(arr.at(i).y == p.y)
            {
                arrindex = i;
            }
            else
            {
                arrindex = -1;
            }
        }
    }
    
    return arrindex;
    
}
void pickupitem()
{
    wclear(logger);
    //move cursor of logger to 0,0
    wmove(logger, 0, 0);
    int inspectedint = mvwinch(map, p.y, p.x) & A_CHARTEXT;
    char test = inspectedint;
    //make sure we're not trying to pickup on an empty space
    if(test == p.sign)
    {
        waddstr(logger, "You can't pick that up!");
    }
    else
    {
        //index is where our item lives in the items array
        int index = finditembylocation(arrofitems);
        if(index == -1)
        {
            waddstr(logger, "Out of bounds!");
            return;
        }
        // get the struct for our item from items array
        auto pickedupitem = arrofitems.at(index);
        //add struct to the vector
        p.inventory.push_back(pickedupitem);
        //use back cause we always want last added item for this
        std::string s = "You picked up a ";
        std::string output = makeitemstring(index, s);
        
        waddstr(logger, output.c_str());
    }
    
}
std::string makeitemstring(int index, std::string s)
{
    if(index == -1)
    {
        s.append("An error!");
    }
    else
    {
        
        s.append(arrofitems.at(index).modifier);
        s.append(" ");
        s.append(arrofitems.at(index).color);
        s.append(" ");
        s.append(arrofitems.at(index).name);
        s.append(" ");
    }
    return s;
}

void angershopkeeper()
{
    wclear(logger);
    //move cursor of logger to 0,0
    wmove(logger, 0, 0);
    waddstr(logger, "Hey watch it buddy!");
}

void checkmovepos()
{
    if(p.x > max_x - 2) // -2 for the wall
    {
        p.x = max_x - 2;
    }
    if(p.x < 1)
    {
        p.x = 1;
    }
    if(p.y > max_y-2)
    {
        p.y = max_y-2;
    }
    if(p.y < 1)
    {
        p.y = 1;
    }
    if(p.x == shop.x && p.y == shop.y)
    {
        
        
        if(random_integer > 0)
        {
            p.x -= uni(rng);
            
            p.y -= uni(rng);
            
            
        }else{
            p.x += uni(rng);
            
            p.y += uni(rng);
            
            
        }
        angershopkeeper();
    }
    //see if we're on an item
    p.current = getcurchar();
    if(p.current == 'b')
    {
        
        //if so find the index of the item
        int i = finditembylocation(arrofitems);
        holder.first = i;
        holder.second = p.current;
        
        //change its sign to the player @ symbol
        arrofitems.at(i).sign = p.sign;
//        refresh();

    }
    
}

void checkinventory()
{
    //new window to show our inventory
    int ch;
    
    std::string empty = " ";
    WINDOW *w;
    std::string title = p.name + "'s "+"Inventory";
    int sz = static_cast<int>(title.size());
    w = newwin(MAP_HEIGHT, MAP_WIDTH, 2, 0);
    box(w, 0, 0);
    //print title of inventory
    mvwprintw(w, 0, (MAP_WIDTH - sz)/2, title.c_str());
    
    
    for(int i=0; i<p.inventory.size(); i++)
    {
        std::string s;
        //use original index to help make inventory strings
        int ogindex = p.inventory.at(i).indexpos;
        std::string str = makeitemstring(ogindex, s);
        wmove(w, i+1, 1);
        waddstr(w, str.c_str());
    }
    wrefresh(w);
    while ((ch = getch()) != '\n');
    
    //Cleanup
    delwin(w);
}

void buyitem()
{
    int ch;
    WINDOW *w;
    w=newwin(MAP_HEIGHT+2, MAP_WIDTH, 0, 0);
    box(w, 0, 0);
    //get item info to buy
    int index = finditembylocation(arrofitems);
    if(index == -1)
    {
        wclear(w);
        wmove(w, 0, 0);
        waddstr(w, "Nothing here to buy!");
        wrefresh(w);
    }
    else
    {
        //build strings
        
        std::string price = std::to_string(arrofitems.at(index).price);
        std::string item;
        
        item = makeitemstring(index, item);
        std::string doublecheck = "Are you sure you want to buy this " + item + "?";
        std::string finalize = "You just purchased a " + item + " for " + price + " gold.";
        std::string thanks = shop.name + " thanks you for your purchase!";
        
        //ask player to confirm
        wclear(w);
        waddstr(w, doublecheck.c_str());
        wrefresh(w);
        echo();

        while(1)
        {
            ch = getch();
            if(ch == 'y' || ch == '\n')
            {
                //subtract gold from user
                
                p.gold = p.gold - arrofitems.at(index).price;
                
                //add gold to shopkeeper
                shop.gold = shop.gold + arrofitems.at(index).price;
                
                //add to player inventory
                additemtoinventory(index);
                
                wclear(w);
                wmove(w, 5, 0);
                waddstr(w, finalize.c_str());
                waddch(w, '\n');
                waddstr(w, thanks.c_str());
                wrefresh(w);
                //change hasbeenpaidfor flag in item
                noecho();
                ch = getch();
                if(ch == '\n' || ch == ' ' || ch == 'y')
                {
                    break;
                }
            }
            if(ch == 'n')
            {
                break;
            }
        }
        
        wclear(w);
        wrefresh(w);
        delwin(w);
        
    }
    
    
    
}

void additemtoinventory(int index)
{
    p.inventory.push_back(arrofitems.at(index));
}

char getcurchar()
{
    //see if we're on an item
    int inspectedint = mvwinch(map, p.y, p.x) & A_CHARTEXT;
    char c;
    c = inspectedint;
    return c;
}
//char switchtotempchar()
//{
//    int i = finditembylocation(arrofitems);
//    char cur = arrofitems.at(i).sign;
//    char temp = p.sign;
//    arrofitems.at(i).sign = temp;
////    refresh();
////    arrofitems.at(i).sign = cur;
//    return cur;
//}
