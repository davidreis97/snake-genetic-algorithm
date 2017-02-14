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
#include <thread>

typedef struct traits{
    DIRECTION MOVE_EMPTY_RIGHT;
    DIRECTION MOVE_EMPTY_LEFT;
    DIRECTION MOVE_EMPTY_DOWN;
    DIRECTION MOVE_EMPTY_UP;
    DIRECTION NOT_MOVE_WALL_RIGHT;
    DIRECTION NOT_MOVE_WALL_LEFT;
    DIRECTION NOT_MOVE_WALL_DOWN;
    DIRECTION NOT_MOVE_WALL_UP;
    DIRECTION MOVE_FRUIT_RIGHT;
    DIRECTION MOVE_FRUIT_LEFT;
    DIRECTION MOVE_FRUIT_DOWN;
    DIRECTION MOVE_FRUIT_UP;
    DIRECTION NOT_MOVE_SNAKEBODY_RIGHT;
    DIRECTION NOT_MOVE_SNAKEBODY_LEFT;
    DIRECTION NOT_MOVE_SNAKEBODY_DOWN;
    DIRECTION NOT_MOVE_SNAKEBODY_UP;
    DIRECTION MOVE_FRUIT_POSITIVE_X;
    DIRECTION MOVE_FRUIT_NEGATIVE_X;
    DIRECTION MOVE_FRUIT_POSITIVE_Y;
    DIRECTION MOVE_FRUIT_NEGATIVE_Y;
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
    void runSnake(bool drawGame, int timeBetweenMove, string readingFrom);
    void setFitness(int fit){fitness = fit;}
    int getFitness(){return fitness;}
    DIRECTION generateNextMove(SnakeGame snake);
    void randomTraits();
    bool operator<(Chromosome& chromo2);
    bool operator>(Chromosome& chromo2);
    TRAITS &getTraits(){return traits;}
    Chromosome(){fitness=0;}
    void mutate();
    void writeToFile(string filename);
    void readFromFile(string filename);
};

#endif /* chromosome_hpp */
