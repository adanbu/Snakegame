
#include "snakey.h"
//#include "game.cpp"
//#include "point.cpp"
//cd VScode cpp
//g++ -o snakey snakey.cpp
//snakey.exe

//snake is initialized to a vertical snake of size 3  
Snake::Snake(Point* head1) : size(3), head(NULL) {

    int i = 0;
    int yhead = head1->y;
    Point* bodypart = NULL;
    for (i = 0; i < size; i++) {
        try {
            bodypart = new Point(head1->x, yhead);
        }
        catch (std::bad_alloc&) {
            //handle allocation failure
        }
        if (i == 0)
            this->head = bodypart;
        body.push_back(bodypart);
        yhead++;
    }
}

Snake::~Snake() {
    int size = int(body.size());
    int i = 0;
    for (i = 0; i < size; i++) {
        if (body[i] != NULL)
            delete body[i];
    }
    // free vector itself, or does cpp free automatically?
    body.clear();
}
Point* Snake::GetHead() {
    return this->head;
}

/*
Point HeadNext(Point* head, DIRECTION d){
    Point next=(*head);
    if(d==UP)
        (next.y)--;
    if(d==DOWN)
        (next.y)++;
    if(d==LEFT)
        (next.x)--;
    if(d==RIGHT)
        (x)++;

}*/

//return head
Point* Snake::MoveAndEat(DIRECTION d, bool eat) {
    int i;
    if (eat == 1) {
        size++;
        Point* bodypart = new Point(body[0]->x, body[0]->y);
        body.insert(body.begin(), bodypart);
    }
    size = this->size;
    if (eat == 0) {
        for (i = size - 1; i > 0; i--) {
            body[i]->x = body[i - 1]->x;
            body[i]->y = body[i - 1]->y;
        }
    }
    if (d == UP)
        (body[0]->y)--;
    if (d == DOWN)
        (body[0]->y)++;
    if (d == LEFT)
        (body[0]->x)--;
    if (d == RIGHT)
        (body[0]->x)++;
    this->head = body[0];
    return body[0];
}

void FillBoard(Snake* s, char** board, int size,bool generatefood) {
    int xb, yb;
    int i, j;
    for (j = 0; j < size; j++) {
        board[0][j] = BORDER;
        board[size - 1][j] = BORDER;
    }
    for (i = 0; i < size; i++) {
        board[i][0] = BORDER;
        board[i][size - 1] = BORDER;
    }
    for (i = 1; i < size - 1; i++) {
        for (j = 1; j < size - 1; j++) {
            //if we are generating food in a new spot
            //if were not generating food in a new spot, we must keep it in the old spot
            if(generatefood || board[i][j]!=FOOD)
                board[i][j] = BLANK;
        }
    }
    int snsize = (s->body).size();
    for (int i = 0; i < snsize; i++)
    {
        xb = (s->body[i])->x;
        yb = (s->body[i])->y;
        board[xb][yb] = SBODY;
    }
    if (generatefood)
        GenerateFood(board);

}



void Print(const vector<Point*>& v) {
    //vector<int> v;
    for (int i = 0; i < v.size(); i++) {
        cout << *v[i] << endl;
    }
}


void GenerateFood(char** board) {
    int randx = 0, randy = 0;
    do {
        randx = rand() % BSIZE;
        randy = rand() % BSIZE;
    } while (board[randx][randy] != BLANK);
    board[randx][randy] = FOOD;
}

void SetUp(Snake** player, char*** board) {
    //try and catch!!!!

    *board = new char* [BSIZE];
    for (int i = 0; i < BSIZE; i++) {
        (*board)[i] = new char[BSIZE];
    }
    Point center(BSIZE / 2, BSIZE / 2);
    *player = new Snake(&center);
    //GenerateFood(*board);
    //FillAndPrint(*player, *board, BSIZE);
    FillBoard(*player, *board, BSIZE, true);
    PrintBoard(*board, BSIZE);
}

bool Play() {
    Snake* player;
    char** board;
    SetUp(&player, &board);
    cout << "Press space bar to start" << endl << "Use w,a,s,d to move the snake" << endl;
    while (_getch() != ' ');//busy wait bad practice
    //generate food
    DIRECTION dir = UP, prevdir = UP, tempdir;
    Point* head;
    //GenerateFood(board);

    while (true) {
        tempdir = getdirection();
        if (tempdir != INVALID) {
            if (directionlogic(dir, tempdir)) {
                prevdir = dir;
                dir = tempdir;
            }
        }
        head = player->GetHead();
        Point next(*head); //check &point ctor //make function instead of copyig code
        if (dir == UP) {
            (next.y)--;
        }
        if (dir == DOWN)
            (next.y)++;
        if (dir == LEFT)
            (next.x)--;
        if (dir == RIGHT)
            (next.x)++;
        switch (board[next.x][next.y])
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
            player->MoveAndEat(dir, true);
            FillBoard(player, board, BSIZE, true);
            //GenerateFood(&board);
            break;
        case BLANK:
            player->MoveAndEat(dir, false);
            FillBoard(player, board, BSIZE, false);
            break;
        }
        //FillAndPrint(player, board, BSIZE);
        PrintBoard(board, BSIZE);


        //get direction from user
    }

    //EndGame();
    return true;
}

int main() {
    Play();
    cout << "Thanks for playing" << endl;
    /*
    char board[BSIZE][BSIZE];
    Point center(BSIZE/2,BSIZE/2);
    Snake* player1=new Snake(&center);
    //Print(player1->body); //inaccessable




    int temp=6;
    for(int temp=5;temp>0;temp--){
    Print(player1->body); //inaccessable

    FillBoard(player1,board,BSIZE);
    PrintBoard(board,BSIZE);
    player1->MoveAndEat(UP,1);

    //cout<<endl;

    player1->MoveAndEat(RIGHT,0);
    FillBoard(player1,board,BSIZE);
    PrintBoard(board,BSIZE);
    player1->MoveAndEat(RIGHT,0);
    FillBoard(player1,board,BSIZE);
    PrintBoard(board,BSIZE);
    player1->MoveAndEat(DOWN,0);
    FillBoard(player1,board,BSIZE);
    PrintBoard(board,BSIZE);



    delete player1;
    */
    return 0;
}
