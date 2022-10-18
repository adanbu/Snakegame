#include "snakey.h"
/*
class Game{
    bool gameover=false;
    int highscore=0;

    Game();
    ~Game();

    public:

    //not clonable
    Game(Game &other)= delete;
    //not assignable
    void operator=(const Game &) = delete;
    static Game *PlayGame(const std::string& value);
};*/
/*
void FillAndPrint(Snake* player, char** board, int size) {
    FillBoard(player, board, BSIZE);
    PrintBoard(board, BSIZE);
}*/

//returns wether setup was successful


void EndGame(Snake* player, char** board) {
    //check NULL
    for (int i = 0; i < BSIZE; i++) {
        delete[] board[i];
    }
    delete[] board;
    delete player;
}


void PrintBoard(char** board, int size) {
    Sleep(200);
    system("cls");//windows only
    int i, j;
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

DIRECTION getdirection() {
    DIRECTION d;

    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {

        case 'a':
            return LEFT;
        case 'd':
            return RIGHT;
        case 'w':
            return UP;
        case 's':
            return DOWN;
        default:
            cout << "WAS PRESSED" << ch;
            return INVALID;
            break;
        }
    }
    return INVALID;
}
bool directionlogic(DIRECTION prevdir, DIRECTION curdir) {
    if (prevdir == UP) {
        if (curdir != DOWN)
            return true;
    }
    if (prevdir == DOWN) {
        if (curdir != UP)
            return true;
    }
    if (prevdir == RIGHT) {
        if (curdir != LEFT) {
            return true;
        }
    }
    if (prevdir == LEFT) {
        if (curdir != RIGHT) {
            return true;
        }
    }
    return false;
}
/*
bool Play(){
    Snake* player;
    char** board;
    SetUp(player,board);
    cout<<"Press space bar to start"<<endl<<"Use w,a,s,d to move the snake"<<endl;
    while(getch()!=' ');//busy wait bad practice
    //generate food
    DIRECTION dir=UP,prevdir=UP,tempdir;
    Point* head;
    while(true){
        cout<<"HELLLLLLLLLLLLO";
        tempdir=getdirection();
        cout<<"HELLO3";
        if(tempdir!=INVALID){
            if(directionlogic(dir,tempdir)){
                prevdir=dir;
                dir=tempdir;
            }
        }
        head=player->GetHead();
        cout<<"HELLO4";

        Point next(*head); //check &point ctor //make function instead of copyig code
        if(dir==UP){
            (next.y)--;
        }
        if(dir==DOWN)
            (next.y)++;
        if(dir==LEFT)
            (next.x)--;
        if(dir==RIGHT)
            (next.x)++;
        switch(board[next.x][next.y])
        {
            case SBODY:
                //gameover
                return false;
                break;
            case BORDER:
                //gameover
                return false;
                break;
            case FOOD:
                player->MoveAndEat(dir,true);
                //generate food
                break;
            case BLANK:
                cout<<"HELLO5";
                player->MoveAndEat(dir,false);
                break;
        }
        FillAndPrint( player,board, BSIZE);


        //get direction from user
    }

    //EndGame();
    return true;
}*/

//generate fruit
//game rules of going into a wall/into the body
//get input from user and move accordingly
