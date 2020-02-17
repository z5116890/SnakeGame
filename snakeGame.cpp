
//  simpleSnakeGame
//
//  Created by Austin Lam on 24/05/2016.


#include "snakeGame.h"

//position for our head, fruit, tail variable. These variables are made
//are made global for functions to allow them to change their value.
int snakeX;
int snakeY;
int candyX;
int candyY;
int tailX[100], tailY[100];
int tailLength;

enum snakeMovement {
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
//direction will hold the direction of the snake
snakeMovement direction;


//draws the map, snake and its tail.
void gameDisplay();
//will change variables of x and y whenever user presses direction buttons.
//draws the movement of snake in correspondence of input
void snakeUpdate();
//moves the snake by decreasing/increasing the height or width of map
void snakeControl();
//kbhit function is used to determine if a key has been pressed or not.
int _kbhit();




int main() {
    //initialises map to 30x15 and puts fruit into place
    gameOver = false;
    direction = STOP;              //snake will not move until we press direction button
    snakeX = width / 2;           //set the position of the head of snake in the middle
    snakeY = height / 2;
    candyX = rand() % width;  //fruits will be randomly generated on map
    candyY = rand() % height;

    
    while(gameOver == false){
        gameDisplay();
        snakeControl();
        snakeUpdate();
    }
    return EXIT_SUCCESS;
}





void gameDisplay(){
    int topRow = 0;
    int bottomRow = 0;
    int rowElement = 0;
    int column = 0;
    bool tailPrint = false;
    int tailCounter = 0;
    //every time the function is called, log will clear to update movement.
    system("cls");
    
    //Game instructions
    printf("HOW TO PLAY:\n Up: W\n Down: S\n Left: A\n Right: D \n");
    
    //will draw the top row of the map.
    while(topRow < width + 2){
        cout << "=";
        topRow++;
    }
    cout << endl;
    
    //inside the square grid, the game will print the current state of the snake, tail and candy.
    //positions will always change after each time it is called.
    while(column < height){
        rowElement = 0;
        while (rowElement < width){
            //print left side of board
            if (rowElement == 0){
                cout << "|";
            }if (column == snakeY && rowElement == snakeX){
                cout << "Q";
            }else if (column == candyY && rowElement == candyX){
                cout << "@";
            }else{
                tailPrint = false;
                tailCounter = 0;
                //if tails of snake is in the current row and col position then it will print
                while(tailCounter < tailLength){
                    if (tailX[tailCounter] == rowElement && tailY[tailCounter] == column){
                        cout << "o";
                        tailPrint = true;
                    }
                    tailCounter++;
                }
                if (tailPrint == false){
                    cout << " ";
                }
            }
            
            //print right side of board
            if (rowElement == width - 1){
                cout << "|";
            }
            rowElement++;
        }
        cout << endl;
        column++;
    }
    //will draw the bottom row of the map.
    while(bottomRow < width + 2){
        cout << "=";
        bottomRow ++;
    }
    cout << endl;
    

}



void snakeUpdate(){
    //when the player moves snake down, the tail doesnt move down straight away. It follows the previous
    //body infront of it.
    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X;
    int prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    int tailPosition = 1;
    int tailNumber = 0;
    
    while(tailPosition < tailLength){
        prev2X = tailX[tailPosition];
        prev2Y = tailY[tailPosition];
        tailX[tailPosition] = prevX;
        tailY[tailPosition] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        tailPosition++;
    }
     

    
    switch(direction){
        case (STOP):
            break;
        case (LEFT):
            snakeX--;  //snake will move left on the x-axis
            break;
        case (RIGHT):
            snakeX++;  //snake will move right on the x-axis
            break;
        case (UP):
            snakeY--;  //snake will move up on the y-axis
            break;
        case (DOWN):
            snakeY++;  //snake will move down on the y-axis
            break;
        default:
            break;
    }
    
    //this will allow the snake to appear
    //on the other side of the board if it
    //goes through a wall
    
    if (snakeY >= height){
        snakeY = 0;
    }else if (snakeY < 0){
        snakeY = height - 1;
    }else if (snakeX >= width){
        snakeX = 0;
    }else if (snakeX < 0){
        snakeX = width - 1;
    }
    
    
    //if any one of the tails is the same position
    //as the head then game over. In other words,
    //if the snake eats it own tail.
    while (tailNumber < tailLength){
        if (tailY[tailNumber] == snakeY && tailX[tailNumber] == snakeX){
            gameOver = true;
        }
        tailNumber++;
    }
    
    //if the snake eats a candy then tail increases
    if (snakeX == candyX && snakeY == candyY){
        candyX = rand() % width;
        candyY = rand() % height;
        tailLength++;
    }
     //updates the speed of the game depending on the tail number
    if(tailLength < 3){
        nanosleep((const struct timespec[]){{0, 320000000L}}, NULL);
    }else if(tailLength >= 3 && tailLength < 6){
        nanosleep((const struct timespec[]){{0, 200000000L}}, NULL);
    }else if(tailLength >= 6 && tailLength < 9){
        nanosleep((const struct timespec[]){{0, 170000000L}}, NULL);
    }else if(tailLength >= 9 && tailLength < 12){
        nanosleep((const struct timespec[]){{0, 130000000L}}, NULL);
    }else if(tailLength >= 12 && tailLength < 15){
        nanosleep((const struct timespec[]){{0, 90000000L}}, NULL);
    }else{
        nanosleep((const struct timespec[]){{0, 50000000L}}, NULL);
    }

}

void snakeControl(){
    if(_kbhit()){
        switch(getchar()){
            case 'a':
                direction = LEFT;
                break;
            case 'd':
                direction = RIGHT;
                break;
            case 'w':
                direction = UP;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
        
    }
    
}


int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;
    
    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    
    timeval timeout;
    fd_set rdset;
    
    FD_ZERO(&rdset);
    FD_SET(STDIN, &rdset);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;
    
    return select(STDIN + 1, &rdset, NULL, NULL, &timeout);
}
