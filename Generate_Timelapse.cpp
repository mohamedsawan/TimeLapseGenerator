// Generate_Timelapse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "color.h"
#include "Image.h"
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <thread>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define RES_FACTOR 9
#define wt 255//vanilla = 255 ROP = 311
#define ht 156 //vanilla = 156 ROP = 207
#define width wt * RES_FACTOR
#define height ht * RES_FACTOR
#define CALC_POS(w, chan, x, y) w*y*chan + x*chan
#define factionFocus 0

#define R_MAP "Modified_Rome_1.png"
#if factionFocus != 0
#define MAP "Modified_Rome_BLANK.png"
#else
#define MAP "TWRR_campaign_map2.png"
#endif
#define FACTIONS 21 //vanilla = 21 ROP = 20
#define REGIONS 106 //vanilla = 106 ROP = 150
#define gar 18

//ROP----------------------------
//#define MAP "rop_blank.png"
//#define R_MAP "rop.png"

#define julii 1
#define brutii 2
#define scipii 3
#define spqr 0
#define macedon 4
#define egypt 5
#define seleucid 6
#define carthage 7
#define parthia 8
#define pontus 9
#define gaul 10
#define germania 11
#define britannia 12
#define armenia 13
#define dacia 14
#define greek 15
#define numidia 16
#define scythia 17
#define spain 18
#define thrace 19
#define rebels 20

int focus = 0;

Image region_map(R_MAP);
Image u_map(MAP);
Image map(MAP);
Image copy1 = map;
Image copy2 = region_map;

Image garrisonWhite("ArmyOutlines/garrisonWhite2.png");
Image garrisonBlack("ArmyOutlines/garrisonBlack2.png");
Image garrisonRed("ArmyOutlines/enemyGarrison.png");
Image garrisonBlue("ArmyOutlines/allyGarrison.png");

Image battleWon("ArmyOutlines/battleWon.png");
Image battleLost("ArmyOutlines/battleLost.png");

int i = 0;


struct coordinate {
    int x;
    int y;
};

struct battle
{
    coordinate pos;
    int winner;   //attacker or defender
    int loser;
    int turnNumber;
};
//VANILLA DATA--------------
coordinate cityCoordinateMap[] = { {55, 140}, {87, 139}, {135, 139}, {186, 153}, {229, 131}, {248, 152}, {36, 142}, {181, 140}, {48, 139}, {111, 136}, {149, 129}, {57, 128}, {84, 127}, {0, 0}, {95, 130}, {115, 125}, {61, 118}, {190, 114}, {88, 117}, {157, 106}, {46, 113}, {79, 114}, {111, 113}, {131, 106}, {66, 106}, {140, 98}, {99, 104}, {156, 100}, {116, 101}, {175, 95}, {47, 99}, {66, 93}, {216, 91}, {241, 82}, {84, 92}, {94, 90}, {67, 82}, {105, 90}, {150, 83}, {20, 87}, {227, 87}, {118, 75}, {57, 84}, {26, 75}, {83, 84}, {190, 80}, {136, 77}, {91, 80}, {253, 78}, {44, 76}, {96, 82}, {8, 72}, {0, 0}, {79, 57}, {95, 71}, {192, 68}, {160, 73}, {165, 72}, {124, 63}, {138, 68}, {174, 67}, {36, 58}, {114, 63}, {102, 68}, {216, 60}, {17, 58}, {154, 61}, {193, 58}, {136, 59}, {54, 63}, {114, 57}, {162, 57}, {241, 53}, {200, 55}, {132, 55}, {144, 52}, {253, 50}, {158, 49}, {139, 50}, {106, 51}, {94, 48}, {12, 46}, {189, 45}, {212, 46}, {199, 42}, {55, 41}, {82, 45}, {106, 44}, {138, 46}, {205, 43}, {161, 45}, {240, 25}, {83, 34}, {146, 38}, {202, 32}, {213, 27}, {38, 18}, {96, 19}, {130, 19}, {178, 19}, {206, 14}, {166, 2}, {183, 13}, {0, 0}, {61, 1}, {187, 2} };
RGBColor rgbFactionMap[] = { {150, 80, 205}, {165, 20, 20}, {85, 135, 65}, {35, 95, 175}, {0, 0, 0}, {255, 255, 140}, {155, 128, 128}, {255, 255, 255}, {168, 62, 154}, {10, 100, 125}, {77, 95, 45}, {88, 21, 38}, {95, 125, 190}, {32, 115, 85}, {115, 75, 40}, {197, 194, 129}, {55, 80, 90}, {215, 115, 25}, {135, 110, 60}, {115, 195, 195}, {155, 145, 120} };
int regionOwnerMap[REGIONS];// = { 12, 20, 20, 20, 17, 8, 20, 17, 12, 20, 20, 12, 11, -1, 11, 11, 12, 17, 11, 17, 10, 11, 20, 14, 10, 14, 20, 19, 20, 20, 10, 20, 13, 20, 10, 10, 20, 20, 19, 18, 13, 20, 10, 10, 20, 9, 4, 0, 8, 18, 0, 18, -1, 7, 3, 9, 20, 20, 20, 4, 20, 7, 1, 2, 6, 7, 15, 6, 4, 7, 1, 6, 6, 6, 15, 20, 8, 20, 4, 2, 7, 16, 5, 20, 5, 16, 7, 15, 15, 6, 15, 20, 7, 20, 5, 20, 16, 20, 20, 5, 20, 16, 5, -1, 20, 5 };
int besiegedMap[REGIONS];

//ROP DATA------------------
//coordinate cityCoordinateMap[] = { {7, 3}, { 64, 201 }, { 97, 198 }, { 142, 200 }, { 151, 177 }, { 214, 169 }, { 222, 178 }, { 10, 3 }, { 79, 178 }, { 49, 186 }, { 238, 177 }, { 182, 171 }, { 47, 167 }, { 64, 160 }, { 248, 167 }, { 89, 168 }, { 264, 147 }, { 37, 154 }, { 206, 152 }, { 171, 157 }, { 143, 156 }, { 227, 148 }, { 61, 156 }, { 85, 159 }, { 6, 145 }, { 22, 150 }, { 75, 156 }, { 83, 158 }, { 131, 147 }, { 14, 147 }, { 105, 152 }, { 192, 148 }, { 74, 151 }, { 235, 137 }, { 57, 146 }, { 37, 140 }, { 127, 143 }, { 8, 138 }, { 135, 131 }, { 175, 137 }, { 23, 134 }, { 218, 129 }, { 184, 135 }, { 270, 121 }, { 99, 138 }, { 149, 123 }, { 55, 138 }, { 84, 139 }, { 124, 134 }, { 92, 131 }, { 106, 125 }, { 305, 118 }, { 34, 131 }, { 43, 131 }, { 73, 134 }, { 167, 127 }, { 16, 131 }, { 6, 126 }, { 61, 129 }, { 78, 124 }, { 215, 115 }, { 85, 125 }, { 22, 125 }, { 119, 126 }, { 131, 119 }, { 46, 125 }, { 239, 117 }, { 34, 122 }, { 60, 124 }, { 68, 115 }, { 4, 117 }, { 13, 119 }, { 39, 120 }, { 53, 121 }, { 188, 112 }, { 116, 116 }, { 11, 116 }, { 91, 113 }, { 99, 111 }, { 144, 117 }, { 27, 116 }, { 61, 112 }, { 37, 115 }, { 168, 114 }, { 55, 113 }, { 8, 109 }, { 138, 104 }, { 45, 110 }, { 53, 113 }, { 300, 112 }, { 32, 110 }, { 79, 107 }, { 159, 108 }, { 264, 90 }, { 40, 110 }, { 288, 104 }, { 55, 107 }, { 67, 103 }, { 112, 102 }, { 192, 99 }, { 43, 108 }, { 177, 97 }, { 215, 85 }, { 5, 107 }, { 33, 105 }, { 40, 105 }, { 58, 104 }, { 88, 100 }, { 37, 103 }, { 98, 97 }, { 138, 89 }, { 5, 100 }, { 151, 94 }, { 298, 93 }, { 60, 101 }, { 105, 97 }, { 226, 90 }, { 48, 94 }, { 101, 87 }, { 104, 73 }, { 179, 88 }, { 170, 77 }, { 287, 81 }, { 97, 83 }, { 7, 0 }, { 203, 74 }, { 301, 76 }, { 35, 78 }, { 80, 76 }, { 88, 75 }, { 10, 0 }, { 29, 75 }, { 63, 74 }, { 118, 61 }, { 82, 69 }, { 54, 65 }, { 293, 65 }, { 72, 44 }, { 209, 49 }, { 89, 52 }, { 305, 38 }, { 144, 35 }, { 111, 32 }, { 85, 37 }, { 188, 30 }, { 100, 17 }, { 159, 21 }, { 121, 6 }, { 174, 13 }, { 195, 1 } };
//RGBColor rgbFactionMap[] = { {51, 1, 72}, {10, 100, 125}, {248, 252, 146}, {10, 39, 117}, {23, 85, 6}, {52, 139, 129}, {164, 20, 20}, {78, 132, 17}, {115, 75, 40}, {247, 73, 2}, {0, 0, 0}, {25, 64, 105}, {255, 255, 255}, {184, 101, 25}, {132, 22, 74}, {247, 73, 2}, {132, 22, 74}, {248, 183, 29}, {56, 80, 90}, {66, 104, 147}, {150, 150, 150} };

//RTR Imperium Surerction Data


void writeImage(Image im, string s)
{
    int i = 0;

    const char* name = s.c_str();
    im.write(name);
}

void scan(int lx, int rx, int y, stack <coordinate>& s, RGBColor prevC)
{
    if (lx < 0 || rx >= width || y < 0 || y >= height)
        return;
    bool added = false;
    for (int x = lx; x < rx; x++)
    {
        x = x;
        int pos = CALC_POS(width, copy2.channels, x, y);
        if (!(*((RGBColor*)&copy2.data[pos]) == prevC) && !(x < 0 || x >= width || y < 0 || y >= height))
        {
            added = false;
        }
        else if (!added)
        {
            s.push({ x, y });
            added = true;
        }
    }

}

void scan1(int lx, int rx, int y, stack <coordinate>& s, RGBColor prevC, Image* pic)
{
    if (lx < 0 || rx >= (*pic).w || y < 0 || y >= (*pic).h)
        return;
    bool added = false;
    for (int x = lx; x < rx; x++)
    {
        x = x;
        int pos = CALC_POS((*pic).w, copy2.channels, x, y);
        if (!(*((RGBColor*)&pic->data[pos]) == prevC) && !(x < 0 || x >= (*pic).w || y < 0 || y >= (*pic).w))
        {
            added = false;
        }
        else if (!added)
        {
            s.push({ x, y });
            added = true;
        }
    }

}

void fillRegion(coordinate cr, RGBColor newC)
{
    int x = cr.x;
    int y = cr.y;
    y = ((ht - 1) - y) * RES_FACTOR;
    x = x * RES_FACTOR;
    for (int i = 0; i < copy2.size; i++)
    {
        copy2.data[i] = region_map.data[i];
    }
    int startingPos = CALC_POS(width, map.channels, x, y);
    int startingPos1 = CALC_POS(width, copy2.channels, x, y);
    RGBColor prevC = *((RGBColor*)&copy2.data[startingPos1]);
    if (newC == prevC)
        return;
    stack <coordinate> c;
    c.push({ x, y });
    while (!c.empty())
    {
        x = c.top().x;
        y = c.top().y;
        c.pop();
        int lx = x;
        int pos = CALC_POS(width, map.channels, (lx - 1), y);
        int pos1 = CALC_POS(width, copy2.channels, (lx - 1), y);
        while (*((RGBColor*)&copy2.data[pos1]) == prevC && !((lx - 1) < 0 || (lx - 1) >= width || y < 0 || y >= height))
        {
            RGBColor* pix = (RGBColor*)&copy2.data[pos1];
            RGBColor* pix1 = (RGBColor*)&map.data[pos];
            RGBColor* pix2 = (RGBColor*)&u_map.data[pos];
            *pix = newC;
            *pix1 = shiftColor(*pix2, newC, 3);
            lx = lx - 1;
            pos = CALC_POS(width, map.channels, (lx - 1), y);
            pos1 = CALC_POS(width, copy2.channels, (lx - 1), y);
        }
        pos = CALC_POS(width, map.channels, x, y);
        pos1 = CALC_POS(width, copy2.channels, x, y);
        while (*((RGBColor*)&copy2.data[pos1]) == prevC && !(x < 0 || x >= width || y < 0 || y >= height))
        {
            RGBColor* pix = (RGBColor*)&copy2.data[pos1];
            RGBColor* pix1 = (RGBColor*)&map.data[pos];
            RGBColor* pix2 = (RGBColor*)&u_map.data[pos];
            *pix = newC;
            *pix1 = shiftColor(*pix2, newC, 3);
            x = x + 1;
            pos = CALC_POS(width, map.channels, x, y);
            pos1 = CALC_POS(width, copy2.channels, x, y);
        }
        scan(lx, x - 1, y + 1, c, prevC);
        scan(lx, x - 1, y - 1, c, prevC);
    }
}

void fill(coordinate cr, RGBColor newC, Image* pic)
{
    int x = cr.x;
    int y = cr.y;
    int startingPos = CALC_POS((*pic).w, 3, x, y);
    RGBColor prevC = *((RGBColor*)&pic->data[startingPos]);
    if (newC == prevC)
        return;
    stack <coordinate> c;
    c.push({ x, y });
    while (!c.empty())
    {
        x = c.top().x;
        y = c.top().y;
        c.pop();
        int lx = x;
        int pos = CALC_POS((*pic).w, map.channels, (lx - 1), y);
        while (*((RGBColor*)&pic->data[pos]) == prevC && !((lx - 1) < 0 || (lx - 1) >= (*pic).w || y < 0 || y >= (*pic).h))
        {
            RGBColor* pix = (RGBColor*)&((*pic).data[pos]);
            *pix = newC;
            lx = lx - 1;
            pos = CALC_POS((*pic).w, 3, (lx - 1), y);
        }
        pos = CALC_POS((*pic).w, 3, x, y);
        while (*((RGBColor*)&pic->data[pos]) == prevC && !(x < 0 || x >= (*pic).w || y < 0 || y >= (*pic).h))
        {
            RGBColor* pix = (RGBColor*)&(pic->data[pos]);
            *pix = newC;
            x = x + 1;
            pos = CALC_POS((*pic).w, 3, x, y);
        }
        scan1(lx, x - 1, y + 1, c, prevC, pic);
        scan1(lx, x - 1, y - 1, c, prevC, pic);
    }
}




void PrintMatches(string str, std::regex reg)
{
    smatch matches;
    while (std::regex_search(str, matches, reg))
    {
        cout << matches.str(1) << endl;
        str = matches.suffix().str();
        cout << endl;
    }
}

void colorArmy(Image* army, RGBColor color, RGBColor border, int size)
{
    size = ((size / 67) * 2) + 3;
    if (border == BLACK)
    {
        string s = "army" + size;
        Image army(s.c_str());
    }
    if (border == WHITE)
    {
        string s = "army" + size + 'w';
        Image army(s.c_str());
    }
    int pos = CALC_POS(size, 3, (size / 2), (size / 2)); //(3 * 27 + 10) * 3;
    RGBColor* pixel = (RGBColor*)&((*army).data[pos]);
}

void colorGarrison(Image* garrison, RGBColor color, int border, int depth)
{
    int wdth = gar - 2;
    if (border == 1)
    {
        for (int i = 0; i < gar * gar * 3; i++)
            (*garrison).data[i] = garrisonBlack.data[i];
    }
    if (border == 0)
    {
        for (int i = 0; i < gar * gar * 3; i++)
            (*garrison).data[i] = garrisonWhite.data[i];
    }
    if (border == 2)
    {
        wdth -= 2;
        depth -= 2;
        color = { 205, 14, 14 };
        for (int i = 0; i < gar * gar * 3; i++)
            (*garrison).data[i] = garrisonRed.data[i];
    }
    if (border == 3)
    {
        wdth -= 2;
        depth -= 2;
        color = { 5, 51, 216 };
        for (int i = 0; i < gar * gar * 3; i++)
            (*garrison).data[i] = garrisonBlue.data[i];
    }
    int pos;
    if (border == 2 || border == 3)
        pos = CALC_POS(gar, 3, 2, (gar - 3));
    else
        pos = CALC_POS(gar, 3, 1, (gar - 2));
    RGBColor* pixel = (RGBColor*)&((*garrison).data[pos]);
    int north = -gar, east = 1, south = gar, west = -1;
    for (int i = 0; i < wdth; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            *(pixel + (j * north) + i) = color;
        }
    }
}

void placeArmy(Image army, coordinate c)
{

    int x = c.x * RES_FACTOR;
    int y = ((ht - 1) - c.y) * RES_FACTOR;
    int pos = CALC_POS(copy1.w, copy1.channels, x, y);
    RGBColor* c1 = (RGBColor*)&army.data[0];
    RGBColor* c2 = (RGBColor*)&copy1.data[pos];
    for (int i = 0; i < army.w * army.h; i++)
    {
        int nX = x + (i % army.h);
        int nY = y + (i / army.w);
        if ((*(c1 + i) != cNULL) && (nX < copy1.w) && (nY < copy1.h))
        {
            *(c2 + ((i / army.h) * copy1.w) + (i % army.h)) = *(c1 + i);
        }
    }
}

void placeGarrison(Image garrison, coordinate c)
{
    int x = (c.x - 1) * RES_FACTOR;
    int y = ((ht - 1) - c.y - 1) * RES_FACTOR;
    int pos = CALC_POS(copy1.w, copy1.channels, x, y);
    RGBColor* c1 = (RGBColor*)&garrison.data[0];
    RGBColor* c2 = (RGBColor*)&copy1.data[pos];
    for (int i = 0; i < gar * gar; i++)
    {
        *(c2 + ((i / gar) * copy1.w) + (i % gar)) = *(c1 + i);
    }
}

void placeBattle(Image battle, coordinate c) //copy of placeArmy
{

    int x = c.x * RES_FACTOR;
    int y = ((ht - 1) - c.y) * RES_FACTOR;
    int pos = CALC_POS(copy1.w, copy1.channels, x, y);
    RGBColor* c1 = (RGBColor*)&battle.data[0];
    RGBColor* c2 = (RGBColor*)&copy1.data[pos];
    for (int i = 0; i < battle.w * battle.h; i++)
    {
        int nX = x + (i % battle.h);
        int nY = y + (i / battle.w);
        if ((*(c1 + i) != cNULL) && (nX < copy1.w) && (nY < copy1.h))
        {
            *(c2 + ((i / battle.h) * copy1.w) + (i % battle.h)) = *(c1 + i);
        }
    }

}

double calculateDistance(coordinate city, coordinate army)
{
    int x1 = army.x;
    int y1 = army.y;
    int x2 = city.x;
    int y2 = city.y;

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)); //Distance formula


}

int findClosestCity(coordinate army)
{
    int closestCity = 0;
    double shortestDistance = calculateDistance(cityCoordinateMap[0], army), distance;
    for (int i = 0; i < REGIONS; i++)
    {
        distance = calculateDistance(cityCoordinateMap[i], army);
        if (shortestDistance > distance)
        {
            shortestDistance = distance;
            closestCity = i;
        }
    }
    return closestCity;
}

int main()
{
#if factionFocus != 0
    //rgbFactionMap[carthage] = shiftColor(rgbFactionMap[carthage], BLACK, -3);
#endif
    //string test = "{0, 0, 480, 6, {71, 49, 18, 18, 26, 9}, {140, 89}}, {1, 340, 4, {71, 18, 18, 49}, {140, 98}}, {1, 358, 4, {71, 18, 18, 9}, {131, 106}}";
//}, { 0, 1, 80, 2, {245, 245}, {86, 78} }, { 0, 0, 266, 4, {210, 189, 189, 186}, {88, 81} }, { 1, 198, 3, {210, 189, 189}, {91, 80} }, { 1, 184, 3, {210, 188, 188}, {96, 82} }], {}, { 2, 3, 0 }";
    //char* t = strtok((char*)test.c_str(), " ");
    //t = strtok(NULL, "[");
    //cout << t;
    //std::regex reg("(\\{(?:\\{??[^\\{]*?\\}))");
    //regex reg("\\{(.*?)\\}\\}");
    regex reg("\\{(.*?)\\}\\}");
    //PrintMatches(test, reg);
    for (int i = 0; i < REGIONS; i++)
    {
        regionOwnerMap[i] = -1;
        besiegedMap[i] = -1;
    }
    std::vector<battle> battles;
    char data[100];
    ifstream rawData;
    ifstream battle1;
    rawData.open("RawData1.txt");
    battle1.open("Battle1.txt");
    int i = 0;
    while (!battle1.eof())
    {
        i++;
        string st;
        char sc[100];
        getline(battle1, st);
        strcpy(sc, st.c_str());
        battle temp;
        temp.winner = atoi(strtok(sc, " "));
        temp.loser = atoi(strtok(NULL, " "));
        temp.pos.x = atoi(strtok(NULL, " "));
        temp.pos.y = atoi(strtok(NULL, " "));
        temp.turnNumber = atoi(strtok(NULL, " "));
        battles.push_back(temp);
    }
    string line1;
    char st[10000];
    char st1[10000];
    char* c, * c1;
    streampos prev, curr;
    int prevDiplomacy[FACTIONS - 1][FACTIONS - 1];
    for (int i = 0; i < FACTIONS - 1; i++)
        for (int j = 0; j < FACTIONS - 1; j++)
            prevDiplomacy[FACTIONS - 1][FACTIONS - 1] = 200;
    int ii = 0;
    bool isAlive[FACTIONS - 1];
    for (int i = 0; i < FACTIONS - 1; i++)
        isAlive[i] = true;
    vector<thread> threads;
    while (ii < 334 && isAlive[focus])
    {
        int diplomacyMap[FACTIONS - 1][FACTIONS - 1];
        for (int i = 0; i < FACTIONS - 1; i++)
            for (int j = 0; j < FACTIONS - 1; j++)
                diplomacyMap[i][j] = 200;
        int garrisonMap[REGIONS];
        for (int j = 0; j < REGIONS; j++)
            garrisonMap[j] = 0;
        string ownerLine, besiegedLine, factionLine;
        string factionLines[FACTIONS - 1];
        getline(rawData, ownerLine);
        getline(rawData, ownerLine);
        char* t, * t1;
        getline(rawData, factionLines[0]);
        for (int j = 0; j < FACTIONS - 1; j++)
        {
            getline(rawData, factionLines[j]);
            int r = -1, b = -1;
            for (int k = 0; k < factionLines[j].length(); k++)
            {
                if (factionLines[j][k] == 91) //[
                    r = k;
                if (factionLines[j][k] == 93) //]
                {
                    b = k;
                    break;
                }
            }
            string s1 = factionLines[j].substr(b + 1), s2, s3;
            r = -1, b = -1;
            for (int k = 0; k < s1.length(); k++)
            {
                if (s1[k] == 123) //{
                    r = k;
                if (s1[k] == 125) //}
                {
                    b = k;
                    break;
                }
            }
            s2 = s1.substr(r + 1, b - r - 1); //enemies
            if (r != b - 1)
            {
                char* c_fac;
                int n;
                strcpy(st, s2.c_str());
                c_fac = strtok(st, ", ");
                n = atoi(c_fac);
                diplomacyMap[j][n] = 600;
                while (c_fac != NULL)
                {
                    c_fac = strtok(NULL, ", ");
                    if (c_fac != NULL)
                    {
                        n = atoi(c_fac);
                        diplomacyMap[j][n] = 600;
                    }
                }
            }
            r = -1, b = -1;
            for (int k = 0; k < s1.length(); k++)
            {
                if (s1[k] == 123) //{
                    r = k;
                if (s1[k] == 125) //}
                {
                    b = k;
                }
            }
            s3 = s1.substr(r + 1, b - r - 1); //allies
            if (r != b - 1)
            {
                char* c_fac;
                int n;
                strcpy(st, s3.c_str());
                c_fac = strtok(st, ", ");
                n = atoi(c_fac);
                diplomacyMap[j][n] = 0;
                while (c_fac != NULL)
                {
                    c_fac = strtok(NULL, ", ");
                    if (c_fac != NULL)
                    {
                        n = atoi(c_fac);
                        diplomacyMap[j][n] = 0;
                    }
                }
            }
        }
        if (factionFocus)
        {
            for (int i = 0; i < FACTIONS - 1; i++)
            {
                if (diplomacyMap[focus][i] == 200 && prevDiplomacy[focus][i] != 200)
                {
                    for (int j = 0; j < REGIONS; j++)
                    {
                        if ((regionOwnerMap[j] == i || besiegedMap[j] == i) && (cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0))
                            fillRegion(cityCoordinateMap[j], WHITE);
                    }
                }
                if (diplomacyMap[focus][i] == 600 && prevDiplomacy[focus][i] != 600)
                {
                    for (int j = 0; j < REGIONS; j++)
                    {
                        if ((regionOwnerMap[j] == i || besiegedMap[j] == i) && (cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0))
                            fillRegion(cityCoordinateMap[j], rgbFactionMap[i]);
                    }
                }
                if (diplomacyMap[focus][i] == 0 && prevDiplomacy[focus][i] != 0)
                {
                    for (int j = 0; j < REGIONS; j++)
                    {
                        if ((regionOwnerMap[j] == i || besiegedMap[j] == i) && (cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0))
                            fillRegion(cityCoordinateMap[j], rgbFactionMap[i]);
                    }
                }
            }
        }
        getline(rawData, besiegedLine);
        strcpy(st, ownerLine.c_str());
        strcpy(st1, besiegedLine.c_str());
        c = strtok_s(st, " ", &t);
        c1 = strtok_s(st1, " ", &t1);
        int n = atoi(c);
        int n1 = atoi(c1);
        if (factionFocus)
        {
            if (n != regionOwnerMap[0] || ((besiegedMap[0] != -1) && (n1 == -1)) && (focus == regionOwnerMap[0] || diplomacyMap[focus][regionOwnerMap[0]] == 600 || diplomacyMap[focus][regionOwnerMap[0]] == 0))
                fillRegion(cityCoordinateMap[0], rgbFactionMap[n]);
            if (n1 != besiegedMap[0] && n1 != -1 && (focus == regionOwnerMap[0] || diplomacyMap[focus][regionOwnerMap[0]] == 600 || diplomacyMap[focus][regionOwnerMap[0]] == 0))
                fillRegion(cityCoordinateMap[0], shiftColor(rgbFactionMap[n], WHITE, 1));

        }
        else
        {
            if (n != regionOwnerMap[0] || ((besiegedMap[0] != -1) && (n1 == -1)))
                fillRegion(cityCoordinateMap[0], rgbFactionMap[n]);
            if (n1 != besiegedMap[0] && n1 != -1)
                fillRegion(cityCoordinateMap[0], shiftColor(rgbFactionMap[n], WHITE, 1));
        }
        regionOwnerMap[0] = n;
        besiegedMap[0] = n1;
        for (int j = 1; j < REGIONS; j++)
        {
            c = strtok_s(NULL, " ", &t);
            n = atoi(c);
            c1 = strtok_s(NULL, " ", &t1);
            n1 = atoi(c1);
            if ((cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0) && (regionOwnerMap[j] != n) || ((besiegedMap[j] != -1) && (n1 == -1)))
            {
                if (factionFocus)
                {
                    if (n == focus)
                        fillRegion(cityCoordinateMap[j], rgbFactionMap[n]);
                    else if (diplomacyMap[focus][n] == 0)
                        fillRegion(cityCoordinateMap[j], rgbFactionMap[n]);
                    else if (diplomacyMap[focus][n] == 600 && n != 20)
                        fillRegion(cityCoordinateMap[j], rgbFactionMap[n]);
                    else if (regionOwnerMap[j] == n || diplomacyMap[focus][regionOwnerMap[j]] == 600 || diplomacyMap[focus][regionOwnerMap[j]] == 0 || n == 20)
                    {
                        fillRegion(cityCoordinateMap[j], WHITE);
                    }
                }
                else
                {
                    if (n == 20)
                    { }
                       // fillRegion(cityCoordinateMap[j], WHITE);
                    else
                        fillRegion(cityCoordinateMap[j], rgbFactionMap[n]);
                }
            }

            if (besiegedMap[j] != n1 && n1 != -1)
            {
                if (factionFocus)
                {
                    if (n1 == focus)
                        fillRegion(cityCoordinateMap[j], shiftColor(rgbFactionMap[n1], WHITE, 1));
                    else if (diplomacyMap[focus][n1] == 0)
                        fillRegion(cityCoordinateMap[j], shiftColor(rgbFactionMap[n1], WHITE, 1));
                    else if (diplomacyMap[focus][n1] == 600 && n != 20)
                        fillRegion(cityCoordinateMap[j], shiftColor(rgbFactionMap[n1], WHITE, 1));
                }
                else
                {
                    if (n1 == carthage)
                        fillRegion(cityCoordinateMap[j], shiftColor(rgbFactionMap[n1], BLACK, 1));
                    else
                        fillRegion(cityCoordinateMap[j], shiftColor(rgbFactionMap[n1], WHITE, 1));
                }
            }
            regionOwnerMap[j] = n;
            besiegedMap[j] = n1;

        }
        for (int j = 0; j < copy1.size; j++)
            copy1.data[j] = map.data[j];
        for (int j = 0; j < FACTIONS - 1; j++)
        {
            strcpy(st, factionLines[j].c_str());
            c = strtok(st, ": ");
            n = atoi(c);         //faction number
            int factionNum = n;
            c = strtok(NULL, ", ");
            n = atoi(c);         //regions controlled
            if (n == 0)
            {
                isAlive[factionNum] = false;
                continue;
            }
            c = strtok(NULL, ",");
            n = atoi(c);         //money
            int r = -1, b = -1;
            for (int k = 0; k < factionLines[j].length(); k++)
            {
                if (factionLines[j][k] == 91) //[          123 = {, 125 = }
                    r = k;
                if (factionLines[j][k] == 93) //]
                {
                    b = k;
                    break;
                }
            }
            if (r != (b - 1))
            {
                string s1 = factionLines[j].substr(r + 1, b - r - 1);  //armies
                cout << s1 << endl << endl;
                smatch matches;
                while (regex_search(s1, matches, reg))
                {
                    cout << "{" << matches.str(1) << "}" << endl;
                    strcpy(st, matches.str(1).c_str());
                    c = strtok(st, ", ");
                    n = atoi(c); //garrison
                    int garrison = n, naval = 0;
                    if (n == 0)
                    {
                        c = strtok(NULL, ", ");
                        n = atoi(c); //naval
                        naval = n;
                    }
                    c = strtok(NULL, ", ");
                    n = atoi(c); //army size
                    int armySize = n;
                    c = strtok(NULL, ", ");
                    n = atoi(c); //unit count
                    int unitCount = n;
                    cout << "{";
                    if (unitCount != 0)
                    {
                        for (int k = 0; k < unitCount; k++)
                        {
                            c = strtok(NULL, " {,");
                            n = atoi(c); //unit ID
                            cout << n << " ";
                        }
                    }
                    cout << "} ";
                    c = strtok(NULL, ", {");
                    n = atoi(c); //x coordinate
                    int x = n;
                    c = strtok(NULL, ", }");
                    n = atoi(c); //y coordinate
                    int y = n;
                    int size = ((armySize / 134) * 2) + 3;
                    if (armySize > 1734)
                        size = 27;

                    if (size > 3)
                    {
                        if (factionFocus)
                        {
                            if (garrison)
                            {
                                garrisonMap[findClosestCity({ x, y })] = armySize;
                            }
                            else if (focus == factionNum || diplomacyMap[focus][factionNum] == 600 || diplomacyMap[focus][factionNum] == 0)
                            {
                                string footer = (factionNum == macedon) ? "w.png" : ".png";
                                string s = "ArmyOutlines/army" + to_string(size) + footer;
                                Image army(s.c_str());
                                coordinate c1;
                                c1.x = army.w / 2;
                                c1.y = army.h / 2;
                                fill(c1, rgbFactionMap[factionNum], &army);
                                placeArmy(army, { x, y });
                            }

                        }
                        else
                        {
                            if (garrison)
                            {
                                garrisonMap[findClosestCity({ x, y })] = armySize;
                            }
                            else
                            {
                                string footer = (j == macedon) ? "w.png" : ".png";
                                string s = "ArmyOutlines/army" + to_string(size) + footer;
                                Image army(s.c_str());
                                coordinate c1;
                                c1.x = army.w / 2;
                                c1.y = army.h / 2;
                                fill(c1, rgbFactionMap[factionNum], &army);
                                placeArmy(army, { x, y });
                            }
                        }
                    }
                    s1 = matches.suffix().str();
                    cout << endl << endl;
                }

            }
        }
        int divFactor = 2000 / (gar - 2);
        divFactor++;
        int max = divFactor * (gar - 2);
        for (int j = 0; j < REGIONS; j++)
        {
            int size = garrisonMap[j] / divFactor;
            if (garrisonMap[j] >= max)
                size = (gar - 2);
            size += 1;
            if (factionFocus == true)
            {
                if ((cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0) && regionOwnerMap[j] != 20 && (regionOwnerMap[j] == focus || diplomacyMap[focus][regionOwnerMap[j]] == 600 || diplomacyMap[focus][regionOwnerMap[j]] == 0))
                {
                    Image garr(27, 27, 3);
                    if (regionOwnerMap[j] == focus)
                    {
                        if (regionOwnerMap[j] == macedon)
                            colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 0, size);
                        else
                            colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 1, size);
                    }
                    else if (diplomacyMap[focus][regionOwnerMap[j]] == 600)
                    {
                        colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 2, size);
                    }
                    else if (diplomacyMap[focus][regionOwnerMap[j]] == 0)
                    {
                        colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 3, size);
                    }
                    placeGarrison(garr, cityCoordinateMap[j]);
                }

            }
            else
            {
                //UNCOMMENT IF YOU WANT TO SHOW GARRISONS
                if ((cityCoordinateMap[j].x != 0 && cityCoordinateMap[j].y != 0) && regionOwnerMap[j] != 20)
                {
                    Image garr(27, 27, 3);
                    if (regionOwnerMap[j] == macedon)
                        colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 0, size);
                    else
                        colorGarrison(&garr, rgbFactionMap[regionOwnerMap[j]], 1, size);
                    placeGarrison(garr, cityCoordinateMap[j]);
                }
            }

        }
        if (factionFocus)
        {
            for (int i = 0; i < battles.size(); i++)
            {
                if (battles[i].turnNumber == ii)
                {
                    if (battles[i].winner == focus)
                        placeBattle(battleWon, battles[i].pos);
                    if (battles[i].loser == focus)
                        placeBattle(battleLost, battles[i].pos);
                }
                if (battles[i].turnNumber > ii)
                    break;
            }
        }
        string s;
        stringstream out, out1, out2;
        out << "campaign_photos/Campaign Map_" << ii << ".png";
        s = out.str();
        const char* name = s.c_str();
        //copy1.write(name);
        threads.push_back(thread(writeImage, copy1, s));
        if ((ii + 1) % 8 == 0)
        {
            system_clock::time_point t01 = system_clock::now();
            for (thread& th : threads)
                th.join();
            threads.clear();
            system_clock::time_point t02 = system_clock::now();
            auto ms0 = std::chrono::duration_cast<std::chrono::milliseconds>(t02 - t01);
            cout << "--------------------Copying images finished----------------------------" << endl;
            cout << "Duration, msec: " << ms0.count() << endl;
        }
        //thread worker1(writeImage, s);
        /*out1 << "campaign_photos/Campaign Map_" << ii << "_1.png";
        s = out1.str();
        thread worker2(writeImage, s);
        out2 << "campaign_photos/Campaign Map_" << ii << "_2.png";
        s = out2.str();
        thread worker3(writeImage, s);*/
        //worker1.join();
        //worker2.join();
        //worker3.join();

        for (int i = 0; i < FACTIONS - 1; i++)
            for (int j = 0; j < FACTIONS - 1; j++)
                prevDiplomacy[i][j] = diplomacyMap[i][j];
        ii++;
    }
    rawData.seekg(2, std::ios_base::cur);
    rawData >> data;
    // write the data at the screen.
    cout << data << endl;

    // again read the data from the file and display it.
    rawData >> data;
    cout << data << endl;
    std::cout << "Hello World!\n";
    //fill(214, 156-15, rgbFactionMap[1]);
   // map.write("PAINT_TEST.png");

}
