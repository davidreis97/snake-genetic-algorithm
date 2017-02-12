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
