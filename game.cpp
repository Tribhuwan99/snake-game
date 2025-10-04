#include <iostream>
using namespace std;

bool gameOver;
int width = 20;
int height = 20;
int x, y, fruitX, fruitY, score;
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
                cout<<" ";
            }
            
            // cout<<" ";

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

    cout<<"Score: "<<score;
}

void input()
{
}
void logic()
{
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