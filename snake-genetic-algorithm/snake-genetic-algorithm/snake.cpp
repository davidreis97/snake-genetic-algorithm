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
        for(int j = 0; j < 20; j++){
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
    
    currentFitness = 0;
    
    tickCount = 0;
    
    totalTickCount = 1;
}

void SnakeGame::createNewGame(){
    gameBoard[currentFruit.x][currentFruit.y] = EMPTY;
    
    for(deque<POS>::iterator it = snake.begin(); it != snake.end(); it++){
        gameBoard[(*it).x][(*it).y] = EMPTY;
    }
    
    deque<POS> newSnake;
    
    POS tail;
    tail.x = 10;
    tail.y = 12;
    POS middle;
    middle.x = 10;
    middle.y = 11;
    POS head;
    head.x = 10;
    head.y = 10;
    
    newSnake.push_back(head);
    newSnake.push_back(middle);
    newSnake.push_back(tail);
    
    snake = newSnake;
    
    gameBoard[10][10] = SNAKEHEAD;
    gameBoard[10][11] = SNAKEBODY;
    gameBoard[10][12] = SNAKEBODY;
    
    allocateFruit();
    
    currentFitness = 0;
    
    tickCount = 0;
    
    totalTickCount = 1;
}

void SnakeGame::allocateFruit() {
    bool success = false;
    while(!success){
        int xfruit = rand()%19 + 1;
        int yfruit = rand()%19 + 1;
        if (gameBoard[xfruit][yfruit] == EMPTY){
            gameBoard[xfruit][yfruit] = FRUIT;
            currentFruit.x = xfruit;
            currentFruit.y = yfruit;
            success = true;
        }
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

bool SnakeGame::nextTick(DIRECTION nextMove) {
	tickCount++;
	totalTickCount++;
	bool fruitEaten = false;
	bool alive = true;
	if (tickCount > 400) {
		alive = false;
		goto end;
	}
	POS newHead;
	gameBoard[snake[0].x][snake[0].y] = SNAKEBODY;
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
        case NONE:
            cerr << "ERROR; INVALID DIRECTION (NONE)" << endl;
    }
	gameBoard[snake[0].x][snake[0].y] = SNAKEHEAD;
    if(!fruitEaten){
		gameBoard[snake[snake.size() - 1].x][snake[snake.size() - 1].y] = EMPTY;
        snake.pop_back();
    }
    if(fruitEaten){
        tickCount = 0;
        allocateFruit();
        currentFitness+=100;
    }
    end:
    return alive;
}

bool SnakeGame::isGameWon() { //Needs testing
    if (snake.size() == 361){
        return true;
    }else{
        return false;
    }
}

POS SnakeGame::getCurrentFruitRelativeToHead(){
    POS diff;
    diff.x = currentFruit.x - snake[0].x;
    diff.y = currentFruit.y - snake[0].y;
    return diff;
}

BLOCK_TYPE SnakeGame::getBlockNextToHead(DIRECTION dir){
    switch (dir){
        case LEFT:
            return gameBoard[snake[0].x - 1][snake[0].y];
            break;
        case RIGHT:
            return gameBoard[snake[0].x + 1][snake[0].y];
            break;
        case UP:
            return gameBoard[snake[0].x][snake[0].y - 1];
            break;
        case DOWN:
            return gameBoard[snake[0].x][snake[0].y + 1];
            break;
        case NONE:
            cerr << "ERROR! INVALID DIRECTION! (NONE)" << endl;
            break;
    }
    return EMPTY;
}

DIRECTION SnakeGame::getCurrentDirection(){
    if (snake[0].x - snake[1].x == -1){
        return LEFT;
    }else if (snake[0].x - snake[1].x == 1){
        return RIGHT;
    }else if (snake[0].y - snake[1].y == 1){
        return DOWN;
    }else if (snake[0].y - snake[1].y == -1){
        return UP;
    }else{
        cerr << "ERROR! INVALID DIRECTION! (NONE)" << endl;
    }
    return NONE;
}






















