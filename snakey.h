#pragma once
#ifndef SNAKEY_H
#define SNAKEY_H
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
//#include <cstdlib>

using std::vector;
using namespace std;
enum DIRECTION { UP, DOWN, LEFT, RIGHT, INVALID };

#define BSIZE 20 //board size
#define SBODY '@'
#define FOOD 'o'
#define BORDER '#'
#define BLANK ' '

struct Point {
    int x;
    int y;
    //ctor
    Point(int xp, int yp);
    //copy ctor
    Point(const Point& other);
    //~Point();
    friend ostream& operator<<(ostream&, const Point& p) {
        cout << '(' << p.x << ',' << p.y << ')';
        return cout;
    }
    //Point(const Point& src);
};

class Snake {
    int size;
    Point* head;
    vector<Point*> body;

public:
    Snake(Point*);
    ~Snake();
    //not assignable
    void operator=(Snake& other) = delete;
    Point* GetHead();
    Point* MoveAndEat(DIRECTION d, bool eat);//returns head
    void PrintSnake();
    friend void FillBoard(Snake* s, char** board, int size, bool generatefood);
};

//unattached to objs functions


void PrintBoard(char** board, int size);
void PrintBoard(char** board, int size);

void SetUp(Snake** player, char*** board);
bool Play();
//void FillAndPrint(Snake* player, char** board, int size);
DIRECTION getdirection();
bool directionlogic(DIRECTION prevdir, DIRECTION curdir);
void GenerateFood(char** board);

#endif