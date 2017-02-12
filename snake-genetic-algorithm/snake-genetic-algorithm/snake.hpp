//
//  snake.hpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#ifndef snake_hpp
#define snake_hpp

#include <stdio.h>
#include <deque>
#include <random>
#include <string>
#include <iostream>

using namespace std;

typedef struct pos{
    int x;
    int y;
}POS;

typedef enum direction {LEFT,RIGHT,UP,DOWN} DIRECTION;

typedef enum blockType {EMPTY,SNAKEBODY,SNAKEHEAD,WALL,FRUIT} BLOCK_TYPE;

class SnakeGame{
private:
    deque<POS> snake;
    BLOCK_TYPE gameBoard[20][20];
    int currentFitness;
public:
    SnakeGame();
    void drawGame();
    bool nextTick(DIRECTION nextMove);
    void allocateFruit();
    bool isGameWon();
};


#endif /* snake_hpp */
