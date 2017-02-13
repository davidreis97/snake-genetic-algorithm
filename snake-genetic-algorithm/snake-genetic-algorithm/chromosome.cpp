//
//  chromosome.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "chromosome.hpp"

DIRECTION Chromosome::generateNextMove(SnakeGame snake){
    int numberOfTimes[5];
    memset(numberOfTimes, 0, sizeof(int)*5);
    
    BLOCK_TYPE block_at_left = snake.getBlockNextToHead(LEFT);
    BLOCK_TYPE block_at_right = snake.getBlockNextToHead(RIGHT);
    BLOCK_TYPE block_at_down = snake.getBlockNextToHead(DOWN);
    BLOCK_TYPE block_at_up = snake.getBlockNextToHead(UP);
    
    if (block_at_left == WALL){
        numberOfTimes[traits.WALL_LEFT]+= 1 * traits.wallPriority;
    }else if (block_at_left == EMPTY){
        numberOfTimes[traits.EMPTY_LEFT]+= 1 * traits.emptyPriority;
    }else if (block_at_left == FRUIT){
        numberOfTimes[traits.FRUIT_LEFT]+= 1 * traits.fruitPriority;
    }else if (block_at_left == SNAKEBODY){
        numberOfTimes[traits.SNAKEBODY_LEFT]+= 1 * traits.snakebodyPriority;
    }
    
    if (block_at_right == SNAKEBODY){
        numberOfTimes[traits.SNAKEBODY_RIGHT]+= 1 * traits.snakebodyPriority;
    }else if (block_at_right == FRUIT){
        numberOfTimes[traits.FRUIT_RIGHT]+= 1 * traits.fruitPriority;
    }else if (block_at_right == WALL){
        numberOfTimes[traits.WALL_RIGHT]+= 1 * traits.wallPriority;
    }else if (block_at_right == EMPTY){
        numberOfTimes[traits.EMPTY_RIGHT]+= 1 * traits.emptyPriority;
    }
    
    if (block_at_down == FRUIT){
        numberOfTimes[traits.FRUIT_DOWN]+= 1 * traits.fruitPriority;
    }else if (block_at_down == WALL){
        numberOfTimes[traits.WALL_DOWN]+= 1 * traits.wallPriority;
    }else if (block_at_down == EMPTY){
        numberOfTimes[traits.EMPTY_DOWN]+= 1 * traits.emptyPriority;
    }else if (block_at_down == SNAKEBODY){
        numberOfTimes[traits.SNAKEBODY_DOWN]+= 1 * traits.snakebodyPriority;
    }
    
    if (block_at_up == EMPTY){
        numberOfTimes[traits.EMPTY_UP]+= 1 * traits.emptyPriority;
    }else if (block_at_up == WALL){
        numberOfTimes[traits.WALL_UP]+= 1 * traits.wallPriority;
    }else if (block_at_up == FRUIT){
        numberOfTimes[traits.FRUIT_UP]+= 1 * traits.fruitPriority;
    }else if (block_at_up == SNAKEBODY){
        numberOfTimes[traits.SNAKEBODY_UP]+= 1 * traits.snakebodyPriority;
    }
    
    if (snake.getCurrentFruitRelativeToHead().x >= 0){
        numberOfTimes[traits.FRUIT_POSITIVE_X]+= 1 * traits.fruitDistancePriority;
    }else{
        numberOfTimes[traits.FRUIT_NEGATIVE_X]+= 1 * traits.fruitDistancePriority;
    }
    
    if (snake.getCurrentFruitRelativeToHead().y >= 0){
        numberOfTimes[traits.FRUIT_POSITIVE_Y]+= 1 * traits.fruitDistancePriority;
    }else{
        numberOfTimes[traits.FRUIT_NEGATIVE_Y]+= 1 * traits.fruitDistancePriority;
    }
    
    if (snake.getCurrentDirection() == UP){
        numberOfTimes[traits.BANNED_MOVE_FACING_UP] = -1;
    }else if (snake.getCurrentDirection() == DOWN){
        numberOfTimes[traits.BANNED_MOVE_FACING_DOWN] = -1;
    }else if (snake.getCurrentDirection() == RIGHT){
        numberOfTimes[traits.BANNED_MOVE_FACING_RIGHT] = -1;
    }else if (snake.getCurrentDirection() == LEFT){
        numberOfTimes[traits.BANNED_MOVE_FACING_LEFT] = -1;
    }
    
    int maxValue = -1;
    int maxIndex = -1;
    for(int i = 0; i < 4; i++){
        if (numberOfTimes[i] > maxValue){
            maxIndex = i;
            maxValue = numberOfTimes[i];
        }
    }
    
    return (DIRECTION)maxIndex;
}


DIRECTION randomDirection(){
    int random = rand()%5;
    switch (random){
        case 0:
            return LEFT;
        case 1:
            return RIGHT;
        case 2:
            return UP;
        case 3:
            return DOWN;
        case 4:
            return NONE;
    }
    return NONE;
}

void Chromosome::randomTraits(){
    traits.EMPTY_RIGHT = randomDirection();
    traits.EMPTY_LEFT = randomDirection();
    traits.EMPTY_DOWN = randomDirection();
    traits.EMPTY_UP = randomDirection();
    traits.WALL_RIGHT = randomDirection();
    traits.WALL_LEFT = randomDirection();
    traits.WALL_DOWN = randomDirection();
    traits.WALL_UP = randomDirection();
    traits.FRUIT_RIGHT = randomDirection();
    traits.FRUIT_LEFT = randomDirection();
    traits.FRUIT_DOWN = randomDirection();
    traits.FRUIT_UP = randomDirection();
    traits.SNAKEBODY_RIGHT = randomDirection();
    traits.SNAKEBODY_LEFT = randomDirection();
    traits.SNAKEBODY_DOWN = randomDirection();
    traits.SNAKEBODY_UP = randomDirection();
    traits.FRUIT_POSITIVE_X = randomDirection();
    traits.FRUIT_NEGATIVE_X = randomDirection();
    traits.FRUIT_POSITIVE_Y = randomDirection();
    traits.FRUIT_NEGATIVE_Y = randomDirection();
    traits.BANNED_MOVE_FACING_RIGHT = randomDirection();
    traits.BANNED_MOVE_FACING_LEFT = randomDirection();
    traits.BANNED_MOVE_FACING_DOWN = randomDirection();
    traits.BANNED_MOVE_FACING_UP = randomDirection();
    traits.emptyPriority = rand()%10;
    traits.wallPriority = rand()%10;
    traits.fruitPriority = rand()%10;;
    traits.snakebodyPriority = rand()%10;;
    traits.fruitDistancePriority = rand()%10;;
}

bool Chromosome::operator<(Chromosome& chromo2){
    return fitness<chromo2.getFitness();
}

bool Chromosome::operator>(Chromosome& chromo2){
    return fitness>chromo2.getFitness();
}












