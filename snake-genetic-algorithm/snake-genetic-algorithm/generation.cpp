//
//  generation.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "generation.hpp"

void Generation::runSnake(bool drawGame, int timeBetweenMove) {
    maxFitness = 0;
    for(vector<Chromosome>::iterator it = subjects.begin(); it != subjects.end(); it++){
        SnakeGame snake;
        while(snake.nextTick((*it).generateNextMove(snake))){
            if (drawGame) {
                snake.drawGame();
                std::this_thread::sleep_for(std::chrono::milliseconds(timeBetweenMove));
            }
        }
        (*it).setFitness(snake.getFitness());
        if ((*it).getFitness() > maxFitness){
            maxFitness = (*it).getFitness();
            cout << maxFitness << endl;
        }
    }
    cout << "Generation " << generationID << " has finished playing. Max Fitness was " << maxFitness << "." << endl;
}

Generation::Generation(int numberOfSubjects, bool randomize){
    if(!randomize){
        return;
    }
    for(int i = 0; i < numberOfSubjects; i++){
        cout << "Randomizing traits of Subject " << i << endl;
        Chromosome chromo;
        chromo.randomTraits();
        subjects.push_back(chromo);
    }
    cout << "Randomized." << endl;
}
