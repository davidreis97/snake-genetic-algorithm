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
                if (timeBetweenMove) std::this_thread::sleep_for(std::chrono::milliseconds(timeBetweenMove));
            }
        }
        (*it).setFitness(snake.getFitness());
        if ((*it).getFitness() > maxFitness){
            maxFitness = (*it).getFitness();
            cout << maxFitness << endl;
        } 
    }
    cout << "Generation " << generationID << " has finished playing. Max Fitness was " << maxFitness << ", Average Fitness was " << getAverageFitness() << endl;
}

Generation::Generation(int numberOfSubjects, int mutationProb){
    generationID = 0;
    maxFitness = 0;
    mutationProbability = mutationProb;
    for(int i = 0; i < numberOfSubjects; i++){
        cout << "Randomizing traits of Subject " << i << endl;
        Chromosome chromo;
        chromo.randomTraits();
        subjects.push_back(chromo);
    }
    cout << "Randomized." << endl;
}

void Generation::generateNextGeneration(){
    quickSort(subjects, 0, subjects.size() - 1);
    vector<Chromosome>::const_iterator first = subjects.begin() + subjects.size()/2;
    vector<Chromosome>::const_iterator last = subjects.end();
    vector<Chromosome> parents(first, last);
    random_shuffle(parents.begin(), parents.end());
    vector<Chromosome> children;
    for(int i = 0; i < parents.size()-1; i+=2){
        mating(children, parents[i], parents[i+1]); //PROBLEM
    }
    parents.insert(parents.end(),children.begin(),children.end());
    while (subjects.size() < parents.size()){
        Chromosome randomDude;
        randomDude.randomTraits();
        parents.push_back(randomDude);
        cout << "Inserted random dude to compensate for infertility" << endl;
    }
    subjects = parents;
    generationID++;
    maxFitness = 0;
}

void Generation::mating(vector<Chromosome>& children, Chromosome father, Chromosome mother){
    Chromosome child1, child2;
    child1.getTraits().EMPTY_RIGHT = mother.getTraits().EMPTY_RIGHT;
    child1.getTraits().EMPTY_LEFT = father.getTraits().EMPTY_LEFT ;
    child1.getTraits().EMPTY_DOWN = mother.getTraits().EMPTY_DOWN;
    child1.getTraits().EMPTY_UP = father.getTraits().EMPTY_UP;
    child1.getTraits().WALL_RIGHT = mother.getTraits().WALL_RIGHT;
    child1.getTraits().WALL_LEFT = father.getTraits().WALL_LEFT;
    child1.getTraits().WALL_DOWN = mother.getTraits().WALL_DOWN;
    child1.getTraits().WALL_UP = father.getTraits().WALL_UP;
    child1.getTraits().FRUIT_RIGHT = mother.getTraits().FRUIT_RIGHT;
    child1.getTraits().FRUIT_LEFT = father.getTraits().FRUIT_LEFT;
    child1.getTraits().FRUIT_DOWN = mother.getTraits().FRUIT_DOWN;
    child1.getTraits().FRUIT_UP = father.getTraits().FRUIT_UP;
    child1.getTraits().SNAKEBODY_RIGHT = mother.getTraits().SNAKEBODY_RIGHT;
    child1.getTraits().SNAKEBODY_LEFT = father.getTraits().SNAKEBODY_LEFT;
    child1.getTraits().SNAKEBODY_DOWN = mother.getTraits().SNAKEBODY_DOWN;
    child1.getTraits().SNAKEBODY_UP = father.getTraits().SNAKEBODY_UP;
    child1.getTraits().FRUIT_POSITIVE_X = mother.getTraits().FRUIT_POSITIVE_X;
    child1.getTraits().FRUIT_NEGATIVE_X = father.getTraits().FRUIT_NEGATIVE_X;
    child1.getTraits().FRUIT_POSITIVE_Y = mother.getTraits().FRUIT_POSITIVE_Y;
    child1.getTraits().FRUIT_NEGATIVE_Y = father.getTraits().FRUIT_NEGATIVE_Y;
    child1.getTraits().BANNED_MOVE_FACING_RIGHT = mother.getTraits().BANNED_MOVE_FACING_RIGHT;
    child1.getTraits().BANNED_MOVE_FACING_LEFT = father.getTraits().BANNED_MOVE_FACING_LEFT;
    child1.getTraits().BANNED_MOVE_FACING_DOWN = mother.getTraits().BANNED_MOVE_FACING_DOWN;
    child1.getTraits().BANNED_MOVE_FACING_UP = father.getTraits().BANNED_MOVE_FACING_UP;
    child1.getTraits().emptyPriority = mother.getTraits().emptyPriority;
    child1.getTraits().wallPriority = father.getTraits().wallPriority;
    child1.getTraits().fruitPriority = mother.getTraits().fruitPriority;
    child1.getTraits().snakebodyPriority = father.getTraits().snakebodyPriority;
    child1.getTraits().fruitDistancePriority = mother.getTraits().fruitDistancePriority;
    
    child2.getTraits().EMPTY_RIGHT = father.getTraits().EMPTY_RIGHT;
    child2.getTraits().EMPTY_LEFT = mother.getTraits().EMPTY_LEFT;
    child2.getTraits().EMPTY_DOWN = father.getTraits().EMPTY_DOWN;
    child2.getTraits().EMPTY_UP = mother.getTraits().EMPTY_UP;
    child2.getTraits().WALL_RIGHT = father.getTraits().WALL_RIGHT;
    child2.getTraits().WALL_LEFT = mother.getTraits().WALL_LEFT;
    child2.getTraits().WALL_DOWN = father.getTraits().WALL_DOWN;
    child2.getTraits().WALL_UP = mother.getTraits().WALL_UP;
    child2.getTraits().FRUIT_RIGHT = father.getTraits().FRUIT_RIGHT;
    child2.getTraits().FRUIT_LEFT = mother.getTraits().FRUIT_LEFT;
    child2.getTraits().FRUIT_DOWN = father.getTraits().FRUIT_DOWN;
    child2.getTraits().FRUIT_UP = mother.getTraits().FRUIT_UP;
    child2.getTraits().SNAKEBODY_RIGHT = father.getTraits().SNAKEBODY_RIGHT;
    child2.getTraits().SNAKEBODY_LEFT = mother.getTraits().SNAKEBODY_LEFT;
    child2.getTraits().SNAKEBODY_DOWN = father.getTraits().SNAKEBODY_DOWN;
    child2.getTraits().SNAKEBODY_UP = mother.getTraits().SNAKEBODY_UP;
    child2.getTraits().FRUIT_POSITIVE_X = father.getTraits().FRUIT_POSITIVE_X;
    child2.getTraits().FRUIT_NEGATIVE_X = mother.getTraits().FRUIT_NEGATIVE_X;
    child2.getTraits().FRUIT_POSITIVE_Y = father.getTraits().FRUIT_POSITIVE_Y;
    child2.getTraits().FRUIT_NEGATIVE_Y = mother.getTraits().FRUIT_NEGATIVE_Y;
    child2.getTraits().BANNED_MOVE_FACING_RIGHT = father.getTraits().BANNED_MOVE_FACING_RIGHT;
    child2.getTraits().BANNED_MOVE_FACING_LEFT = mother.getTraits().BANNED_MOVE_FACING_LEFT;
    child2.getTraits().BANNED_MOVE_FACING_DOWN = father.getTraits().BANNED_MOVE_FACING_DOWN;
    child2.getTraits().BANNED_MOVE_FACING_UP = mother.getTraits().BANNED_MOVE_FACING_UP;
    child2.getTraits().emptyPriority = father.getTraits().emptyPriority;
    child2.getTraits().wallPriority = mother.getTraits().wallPriority;
    child2.getTraits().fruitPriority = father.getTraits().fruitPriority;
    child2.getTraits().snakebodyPriority = mother.getTraits().snakebodyPriority;
    child2.getTraits().fruitDistancePriority = father.getTraits().fruitDistancePriority;
    
    if(rand()%100+1 < mutationProbability){
        //MUTATION ALGORITHM
    }
    
    children.push_back(child1);
    children.push_back(child2);
}

double Generation::getAverageFitness(){
    double totalFitness;
    for (vector<Chromosome>::iterator it = subjects.begin(); it!= subjects.end();it++){
        totalFitness += (*it).getFitness();
    }
    return totalFitness/subjects.size();
}

