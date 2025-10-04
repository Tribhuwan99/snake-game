#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;


bool gameOver;
int width = 20;
int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
enum sDirection
{
    Stop = 0,
    Up,
    Down,
    Left,
    Right
};
sDirection dir;
void setup()
{
    gameOver = false;
    dir = Stop;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("clear");

    for (int i = 0; i < width+2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        { 
            if (j == 0)
            {
                cout << "#";
            }
            if(i == x && j == y){
                cout<<"O";
            }
            else if(i == fruitX && j == fruitY){
                cout<<"o";
            }
            else{
                bool print = false;
                for(int k = 0; k < ntail; k++){
                    if(tailX[k] == i && tailY[k] == j){
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print){
                    cout<<" ";
                }
               
            }

            if(j == width - 1){
                cout << "#";
            }
        }
        cout<<endl;
    }

    for (int i = 0; i < width+2; i++)
    {
        cout << "#";
    }
    cout << endl;

    cout<<"Score: "<<score<<endl;
}

// ***************** For kbhit *******************

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


// ************** For Getch() *****************
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;  // disable buffered i/o
    old.c_lflag &= ~ECHO;    // disable echo mode
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}


void input()
{
    if(kbhit()){
        switch (getch()){
            case 'a':
                dir = Left;
                break;
            case 's':
                dir= Down;
                break;
            case 'd':
                dir = Right;
                break;
            case 'w':
                dir= Up;
                break;
            case 'x':
                gameOver = true;
                break;    
        }
    }
}
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < ntail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case Left:
        y--;
        break;
    case Right:
        y++;
        break;
    case Up:
        x--;
        break;
    case Down:
        x++;
        break;
    default:
        break;
    }
    if(x > width || x < 0 || y > height || y < 0)
        gameOver = true;

    for (int i = 0; i < ntail; i++)
    {
        if(x == tailX[i] && y == tailY[i]){
            gameOver = true;
        }
    }
    
    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }    
}

int main()
{

    setup();
    while (!gameOver)
    {

        draw();
        input();
        logic();
    }

    return 0;
}