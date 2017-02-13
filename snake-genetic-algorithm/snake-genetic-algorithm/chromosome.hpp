//
//  chromosome.hpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#ifndef chromosome_hpp
#define chromosome_hpp

#include "snake.hpp"

typedef struct traits{
    DIRECTION EMPTY_RIGHT;
    DIRECTION EMPTY_LEFT;
    DIRECTION EMPTY_DOWN;
    DIRECTION EMPTY_UP;
    DIRECTION WALL_RIGHT;
    DIRECTION WALL_LEFT;
    DIRECTION WALL_DOWN;
    DIRECTION WALL_UP;
    DIRECTION FRUIT_RIGHT;
    DIRECTION FRUIT_LEFT;
    DIRECTION FRUIT_DOWN;
    DIRECTION FRUIT_UP;
    DIRECTION SNAKEBODY_RIGHT;
    DIRECTION SNAKEBODY_LEFT;
    DIRECTION SNAKEBODY_DOWN;
    DIRECTION SNAKEBODY_UP;
    DIRECTION FRUIT_POSITIVE_X;
    DIRECTION FRUIT_NEGATIVE_X;
    DIRECTION FRUIT_POSITIVE_Y;
    DIRECTION FRUIT_NEGATIVE_Y;
    DIRECTION BANNED_MOVE_FACING_RIGHT;
    DIRECTION BANNED_MOVE_FACING_LEFT;
    DIRECTION BANNED_MOVE_FACING_DOWN;
    DIRECTION BANNED_MOVE_FACING_UP;
    int emptyPriority;
    int wallPriority;
    int fruitPriority;
    int snakebodyPriority;
    int fruitDistancePriority;
}TRAITS;

class Chromosome{
private:
    TRAITS traits;
    //int age;
    int fitness;
public:
    void setFitness(int fit){fitness = fit;}
    int getFitness(){return fitness;}
    DIRECTION generateNextMove(SnakeGame snake);
    void randomTraits();
    bool operator<(Chromosome& chromo2);
    bool operator>(Chromosome& chromo2);
    TRAITS &getTraits(){return traits;}
    Chromosome(){fitness=0;}
};

#endif /* chromosome_hpp */
