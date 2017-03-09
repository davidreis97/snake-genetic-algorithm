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
        numberOfTimes[traits.NOT_MOVE_WALL_LEFT]-= 1 * traits.wallPriority;
    }else if (block_at_left == EMPTY){
        numberOfTimes[traits.MOVE_EMPTY_LEFT]+= 1 * traits.emptyPriority;
    }else if (block_at_left == FRUIT){
        numberOfTimes[traits.MOVE_FRUIT_LEFT]+= 1 * traits.fruitPriority;
    }else if (block_at_left == SNAKEBODY){
        numberOfTimes[traits.NOT_MOVE_SNAKEBODY_LEFT]-= 1 * traits.snakebodyPriority;
    }
    
    if (block_at_right == SNAKEBODY){
        numberOfTimes[traits.NOT_MOVE_SNAKEBODY_RIGHT]-= 1 * traits.snakebodyPriority;
    }else if (block_at_right == FRUIT){
        numberOfTimes[traits.MOVE_FRUIT_RIGHT]+= 1 * traits.fruitPriority;
    }else if (block_at_right == WALL){
        numberOfTimes[traits.NOT_MOVE_WALL_RIGHT]-= 1 * traits.wallPriority;
    }else if (block_at_right == EMPTY){
        numberOfTimes[traits.MOVE_EMPTY_RIGHT]+= 1 * traits.emptyPriority;
    }
    
    if (block_at_down == FRUIT){
        numberOfTimes[traits.MOVE_FRUIT_DOWN]+= 1 * traits.fruitPriority;
    }else if (block_at_down == WALL){
        numberOfTimes[traits.NOT_MOVE_WALL_DOWN]-= 1 * traits.wallPriority;
    }else if (block_at_down == EMPTY){
        numberOfTimes[traits.MOVE_EMPTY_DOWN]+= 1 * traits.emptyPriority;
    }else if (block_at_down == SNAKEBODY){
        numberOfTimes[traits.NOT_MOVE_SNAKEBODY_DOWN]-= 1 * traits.snakebodyPriority;
    }
    
    if (block_at_up == EMPTY){
        numberOfTimes[traits.MOVE_EMPTY_UP]+= 1 * traits.emptyPriority;
    }else if (block_at_up == WALL){
        numberOfTimes[traits.NOT_MOVE_WALL_UP]-= 1 * traits.wallPriority;
    }else if (block_at_up == FRUIT){
        numberOfTimes[traits.MOVE_FRUIT_UP]+= 1 * traits.fruitPriority;
    }else if (block_at_up == SNAKEBODY){
        numberOfTimes[traits.NOT_MOVE_SNAKEBODY_UP]-= 1 * traits.snakebodyPriority;
    }
    
    if (snake.getCurrentFruitRelativeToHead().x >= 0){
        numberOfTimes[traits.MOVE_FRUIT_POSITIVE_X]+= 1 * traits.fruitDistancePriority;
    }else{
        numberOfTimes[traits.MOVE_FRUIT_NEGATIVE_X]+= 1 * traits.fruitDistancePriority;
    }
    
    if (snake.getCurrentFruitRelativeToHead().y >= 0){
        numberOfTimes[traits.MOVE_FRUIT_POSITIVE_Y]+= 1 * traits.fruitDistancePriority;
    }else{
        numberOfTimes[traits.MOVE_FRUIT_NEGATIVE_Y]+= 1 * traits.fruitDistancePriority;
    }
    
    int maxValue = numberOfTimes[0];
    int maxIndex = 0;
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
    traits.MOVE_EMPTY_RIGHT = randomDirection();
    traits.MOVE_EMPTY_LEFT = randomDirection();
    traits.MOVE_EMPTY_DOWN = randomDirection();
    traits.MOVE_EMPTY_UP = randomDirection();
    traits.NOT_MOVE_WALL_RIGHT = randomDirection();
    traits.NOT_MOVE_WALL_LEFT = randomDirection();
    traits.NOT_MOVE_WALL_DOWN = randomDirection();
    traits.NOT_MOVE_WALL_UP = randomDirection();
    traits.MOVE_FRUIT_RIGHT = randomDirection();
    traits.MOVE_FRUIT_LEFT = randomDirection();
    traits.MOVE_FRUIT_DOWN = randomDirection();
    traits.MOVE_FRUIT_UP = randomDirection();
    traits.NOT_MOVE_SNAKEBODY_RIGHT = randomDirection();
    traits.NOT_MOVE_SNAKEBODY_LEFT = randomDirection();
    traits.NOT_MOVE_SNAKEBODY_DOWN = randomDirection();
    traits.NOT_MOVE_SNAKEBODY_UP = randomDirection();
    traits.MOVE_FRUIT_POSITIVE_X = randomDirection();
    traits.MOVE_FRUIT_NEGATIVE_X = randomDirection();
    traits.MOVE_FRUIT_POSITIVE_Y = randomDirection();
    traits.MOVE_FRUIT_NEGATIVE_Y = randomDirection();
    traits.emptyPriority = rand()%10;
    traits.wallPriority = rand()%10;
    traits.fruitPriority = rand()%10;
    traits.snakebodyPriority = rand()%10;
    traits.fruitDistancePriority = rand()%10;
}

bool Chromosome::operator<(Chromosome& chromo2){
    return fitness<chromo2.getFitness();
}

bool Chromosome::operator>(Chromosome& chromo2){
    return fitness>chromo2.getFitness();
}

void Chromosome::mutate(){
    int i = 5;
    while (i > 0){
        int choice = rand()%25;
        switch (choice){
            case 0:
                traits.MOVE_EMPTY_RIGHT = randomDirection();
                break;
            case 1:
                traits.MOVE_EMPTY_LEFT = randomDirection();
                break;
            case 2:
                traits.MOVE_EMPTY_DOWN = randomDirection();
                break;
            case 3:
                traits.MOVE_EMPTY_UP = randomDirection();
                break;
            case 4:
                traits.NOT_MOVE_WALL_RIGHT = randomDirection();
                break;
            case 5:
                traits.NOT_MOVE_WALL_LEFT = randomDirection();
                break;
            case 6:
                traits.NOT_MOVE_WALL_DOWN = randomDirection();
                break;
            case 7:
                traits.NOT_MOVE_WALL_UP = randomDirection();
                break;
            case 8:
                traits.MOVE_FRUIT_RIGHT = randomDirection();
                break;
            case 9:
                traits.MOVE_FRUIT_LEFT = randomDirection();
                break;
            case 10:
                traits.MOVE_FRUIT_DOWN = randomDirection();
                break;
            case 11:
                traits.MOVE_FRUIT_UP = randomDirection();
                break;
            case 12:
                traits.NOT_MOVE_SNAKEBODY_RIGHT = randomDirection();
                break;
            case 13:
                traits.NOT_MOVE_SNAKEBODY_LEFT = randomDirection();
                break;
            case 14:
                traits.NOT_MOVE_SNAKEBODY_DOWN = randomDirection();
                break;
            case 15:
                traits.NOT_MOVE_SNAKEBODY_UP = randomDirection();
                break;
            case 16:
                traits.MOVE_FRUIT_POSITIVE_X = randomDirection();
                break;
            case 17:
                traits.MOVE_FRUIT_NEGATIVE_X = randomDirection();
                break;
            case 18:
                traits.MOVE_FRUIT_POSITIVE_Y = randomDirection();
                break;
            case 19:
                traits.MOVE_FRUIT_NEGATIVE_Y = randomDirection();
                break;
            case 20:
                traits.emptyPriority = rand()%10;
                break;
            case 21:
                traits.wallPriority = rand()%10;
                break;
            case 22:
                traits.fruitPriority = rand()%10;
                break;
            case 23:
                traits.snakebodyPriority = rand()%10;
                break;
            case 24:
                traits.fruitDistancePriority = rand()%10;
                break;
        }
        i--;
    }
}

void Chromosome::writeToFile(string filename){
    ofstream file;
    file.open(filename);
    file << traits.MOVE_EMPTY_RIGHT << endl << traits.MOVE_EMPTY_LEFT << endl << traits.MOVE_EMPTY_DOWN << endl << traits.MOVE_EMPTY_UP << endl << traits.NOT_MOVE_WALL_RIGHT << endl << traits.NOT_MOVE_WALL_LEFT << endl << traits.NOT_MOVE_WALL_DOWN << endl << traits.NOT_MOVE_WALL_UP << endl << traits.MOVE_FRUIT_RIGHT << endl << traits.MOVE_FRUIT_LEFT << endl << traits.MOVE_FRUIT_DOWN << endl << traits.MOVE_FRUIT_UP << endl << traits.NOT_MOVE_SNAKEBODY_RIGHT << endl << traits.NOT_MOVE_SNAKEBODY_LEFT << endl << traits.NOT_MOVE_SNAKEBODY_DOWN << endl << traits.NOT_MOVE_SNAKEBODY_UP << endl << traits.MOVE_FRUIT_POSITIVE_X << endl << traits.MOVE_FRUIT_NEGATIVE_X << endl << traits.MOVE_FRUIT_POSITIVE_Y << endl << traits.MOVE_FRUIT_NEGATIVE_Y << endl << traits.emptyPriority << endl << traits.wallPriority << endl << traits.fruitPriority << endl << traits.snakebodyPriority << endl << traits.fruitDistancePriority;
    file.close();
}

void Chromosome::readFromFile(string filename) {
    ostringstream osstream;
    string currentLine;
    fstream file;
    file.open(filename.c_str(), fstream::in);
    if (file.fail()){
        cerr << "Requested file was not found/not available." << endl;
        exit(0);
    }
    else{
        getline(file, currentLine);
        traits.MOVE_EMPTY_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_EMPTY_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_EMPTY_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_EMPTY_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_WALL_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_WALL_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_WALL_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_WALL_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_SNAKEBODY_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_SNAKEBODY_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_SNAKEBODY_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.NOT_MOVE_SNAKEBODY_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_POSITIVE_X = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_NEGATIVE_X = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_POSITIVE_Y = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.MOVE_FRUIT_NEGATIVE_Y = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.emptyPriority = stoi(currentLine);
        getline(file, currentLine);
        traits.wallPriority = stoi(currentLine);
        getline(file, currentLine);
        traits.fruitPriority = stoi(currentLine);
        getline(file, currentLine);
        traits.snakebodyPriority = stoi(currentLine);
        getline(file, currentLine);
        traits.fruitDistancePriority = stoi(currentLine);
    }
    file.close();
}

void Chromosome::runSnake(bool drawGame, int timeBetweenMove, string readingFrom){
    SnakeGame snake;
    bool alive = true;
    while(alive){
        if (drawGame) {
            cout << "Reading from " << readingFrom << endl;
            snake.drawGame();
            if (timeBetweenMove) std::this_thread::sleep_for(std::chrono::milliseconds(timeBetweenMove));
        }
        alive = snake.nextTick(generateNextMove(snake));
    }
    cout << "Game ended, final fitness was " << snake.getFitness() << "." << endl;
}











