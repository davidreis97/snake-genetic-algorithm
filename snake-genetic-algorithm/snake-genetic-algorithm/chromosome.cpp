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
        int choice = rand()%29;
        switch (choice){
            case 0:
                traits.EMPTY_RIGHT = randomDirection();
                break;
            case 1:
                traits.EMPTY_LEFT = randomDirection();
                break;
            case 2:
                traits.EMPTY_DOWN = randomDirection();
                break;
            case 3:
                traits.EMPTY_UP = randomDirection();
                break;
            case 4:
                traits.WALL_RIGHT = randomDirection();
                break;
            case 5:
                traits.WALL_LEFT = randomDirection();
                break;
            case 6:
                traits.WALL_DOWN = randomDirection();
                break;
            case 7:
                traits.WALL_UP = randomDirection();
                break;
            case 8:
                traits.FRUIT_RIGHT = randomDirection();
                break;
            case 9:
                traits.FRUIT_LEFT = randomDirection();
                break;
            case 10:
                traits.FRUIT_DOWN = randomDirection();
                break;
            case 11:
                traits.FRUIT_UP = randomDirection();
                break;
            case 12:
                traits.SNAKEBODY_RIGHT = randomDirection();
                break;
            case 13:
                traits.SNAKEBODY_LEFT = randomDirection();
                break;
            case 14:
                traits.SNAKEBODY_DOWN = randomDirection();
                break;
            case 15:
                traits.SNAKEBODY_UP = randomDirection();
                break;
            case 16:
                traits.FRUIT_POSITIVE_X = randomDirection();
                break;
            case 17:
                traits.FRUIT_NEGATIVE_X = randomDirection();
                break;
            case 18:
                traits.FRUIT_POSITIVE_Y = randomDirection();
                break;
            case 19:
                traits.FRUIT_NEGATIVE_Y = randomDirection();
                break;
            case 20:
                traits.BANNED_MOVE_FACING_RIGHT = randomDirection();
                break;
            case 21:
                traits.BANNED_MOVE_FACING_LEFT = randomDirection();
                break;
            case 22:
                traits.BANNED_MOVE_FACING_DOWN = randomDirection();
                break;
            case 23:
                traits.BANNED_MOVE_FACING_UP = randomDirection();
                break;
            case 24:
                traits.emptyPriority = rand()%10;
                break;
            case 25:
                traits.wallPriority = rand()%10;
                break;
            case 26:
                traits.fruitPriority = rand()%10;
                break;
            case 27:
                traits.snakebodyPriority = rand()%10;
                break;
            case 28:
                traits.fruitDistancePriority = rand()%10;
                break;
        }
        i--;
    }
}

void Chromosome::writeToFile(string filename){
    ofstream file;
    file.open(filename);
    file << traits.EMPTY_RIGHT << endl << traits.EMPTY_LEFT << endl << traits.EMPTY_DOWN << endl << traits.EMPTY_UP << endl << traits.WALL_RIGHT << endl << traits.WALL_LEFT << endl << traits.WALL_DOWN << endl << traits.WALL_UP << endl << traits.FRUIT_RIGHT << endl << traits.FRUIT_LEFT << endl << traits.FRUIT_DOWN << endl << traits.FRUIT_UP << endl << traits.SNAKEBODY_RIGHT << endl << traits.SNAKEBODY_LEFT << endl << traits.SNAKEBODY_DOWN << endl << traits.SNAKEBODY_UP << endl << traits.FRUIT_POSITIVE_X << endl << traits.FRUIT_NEGATIVE_X << endl << traits.FRUIT_POSITIVE_Y << endl << traits.FRUIT_NEGATIVE_Y << endl << traits.BANNED_MOVE_FACING_RIGHT << endl << traits.BANNED_MOVE_FACING_LEFT << endl << traits.BANNED_MOVE_FACING_DOWN << endl << traits.BANNED_MOVE_FACING_UP << endl << traits.emptyPriority << endl << traits.wallPriority << endl << traits.fruitPriority << endl << traits.snakebodyPriority << endl << traits.fruitDistancePriority;
    file.close();
}

void Chromosome::readFromFile(string filename) {
    ostringstream osstream;
    string currentLine;
    fstream file;
    file.open(filename.c_str(), fstream::in);
    if (file.fail())
        cout << "Requested file was not found/not available." << endl;
    else{
        getline(file, currentLine);
        traits.EMPTY_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.EMPTY_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.EMPTY_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.EMPTY_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.WALL_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.WALL_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.WALL_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.WALL_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.SNAKEBODY_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.SNAKEBODY_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.SNAKEBODY_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.SNAKEBODY_UP = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_POSITIVE_X = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_NEGATIVE_X = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_POSITIVE_Y = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.FRUIT_NEGATIVE_Y = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.BANNED_MOVE_FACING_RIGHT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.BANNED_MOVE_FACING_LEFT = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.BANNED_MOVE_FACING_DOWN = (DIRECTION)stoi(currentLine);
        getline(file, currentLine);
        traits.BANNED_MOVE_FACING_UP = (DIRECTION)stoi(currentLine);
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

void Chromosome::runSnake(bool drawGame, int timeBetweenMove){
    SnakeGame snake;
    bool alive = true;
    while(alive){
        if (drawGame) {
            snake.drawGame();
            if (timeBetweenMove) std::this_thread::sleep_for(std::chrono::milliseconds(timeBetweenMove));
        }
        alive = snake.nextTick(generateNextMove(snake));
    }
    cout << "Game ended, final fitness was " << snake.getFitness() << ". Would you like to start again with the same generation and same settings? (y/N)" << endl;
    string input;
    cin >> input;
    if (input != "N" && input != (&"N"['\n']) && input != (&"N"['\0'])){
        runSnake(drawGame,timeBetweenMove);
    }
}











