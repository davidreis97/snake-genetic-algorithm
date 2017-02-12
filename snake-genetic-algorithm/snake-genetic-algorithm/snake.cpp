//
//  snake.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "snake.hpp"

SnakeGame::SnakeGame(){
    POS tail;
    tail.x = 10;
    tail.y = 12;
    POS middle;
    middle.x = 10;
    middle.y = 11;
    POS head;
    head.x = 10;
    head.y = 10;
    
    snake.push_back(head);
    snake.push_back(middle);
    snake.push_back(tail);
    
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 19; j++){
            gameBoard[i][j] = EMPTY;
        }
    }
    
    for(int i = 0; i < 20; i++){
        gameBoard[0][i] = WALL;
        gameBoard[i][0] = WALL;
        gameBoard[i][19] = WALL;
        gameBoard[19][i] = WALL;
    }
    
    gameBoard[10][10] = SNAKEHEAD;
    gameBoard[10][11] = SNAKEBODY;
    gameBoard[10][12] = SNAKEBODY;
    
    allocateFruit();
}

void SnakeGame::allocateFruit() {
    int xfruit = rand()%18 + 1;
    int yfruit = rand()%18 + 1;
    if (gameBoard[xfruit][yfruit] == EMPTY){
        gameBoard[xfruit][yfruit] = FRUIT;
        //cout << "Random Numbers: " << xfruit << "x" << yfruit << endl;
    }else{
        //cout << "Realocating" << endl;
        allocateFruit();
    }
}

void SnakeGame::drawGame() {
    for(int y = 0; y < 20; y++){
        string line;
        for(int x = 0; x < 20; x++){
            switch (gameBoard[x][y]){
            case EMPTY:
                line += ' ';
                break;
            case WALL:
                line += '#';
                break;
            case FRUIT:
                line += '*';
                break;
            case SNAKEHEAD:
                line += '@';
                break;
            case SNAKEBODY:
                line += 'o';
                break;
            }
        }
        cout << line << endl;
    }
}

bool SnakeGame::nextTick(DIRECTION nextMove){
    bool fruitEaten = false;
    bool alive = true;
    POS newHead;
    switch(nextMove){
        case LEFT:
            if (gameBoard[snake[0].x - 1][snake[0].y] == FRUIT){
                fruitEaten = true;
            }else if (gameBoard[snake[0].x - 1][snake[0].y] == WALL || gameBoard[snake[0].x - 1][snake[0].y] == SNAKEBODY){
                alive = false;
                goto end;
            }
            newHead.x = snake[0].x-1;
            newHead.y = snake[0].y;
            snake.push_front(newHead);
            break;
        case RIGHT:
            if (gameBoard[snake[0].x + 1][snake[0].y] == FRUIT){
                fruitEaten = true;
            }else if (gameBoard[snake[0].x + 1][snake[0].y] == WALL || gameBoard[snake[0].x + 1][snake[0].y] == SNAKEBODY){
                alive = false;
                goto end;
            }
            newHead.x = snake[0].x+1;
            newHead.y = snake[0].y;
            snake.push_front(newHead);
            break;
        case UP:
            if (gameBoard[snake[0].x][snake[0].y-1] == FRUIT){
                fruitEaten = true;
            }else if (gameBoard[snake[0].x][snake[0].y-1] == WALL || gameBoard[snake[0].x][snake[0].y-1] == SNAKEBODY){
                alive = false;
                goto end;
            }
            newHead.x = snake[0].x;
            newHead.y = snake[0].y-1;
            snake.push_front(newHead);
            break;
        case DOWN:
            if (gameBoard[snake[0].x][snake[0].y+1] == FRUIT){
                fruitEaten = true;
            }else if (gameBoard[snake[0].x][snake[0].y+1] == WALL || gameBoard[snake[0].x][snake[0].y+1] == SNAKEBODY){
                alive = false;
                goto end;
            }
            newHead.x = snake[0].x;
            newHead.y = snake[0].y+1;
            snake.push_front(newHead);
            break;
    }
    for(int x = 0; x < 20; x++){
        for (int y = 0; y < 20; y++){
            if (gameBoard[x][y] == SNAKEBODY || gameBoard[x][y] == SNAKEHEAD){
                gameBoard[x][y] = EMPTY;
            }
        }
    }
    if(fruitEaten){
        allocateFruit();
    }else{
        snake.pop_back();
    }
    for(deque<POS>::iterator it = snake.begin(); it != snake.end(); it++){
        if (it == snake.begin()){
            gameBoard[(*it).x][(*it).y] = SNAKEHEAD;
        }else{
            gameBoard[(*it).x][(*it).y] = SNAKEBODY;
        }
    }
    end:
    return alive;
}































