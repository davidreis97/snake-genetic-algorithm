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
    int subjectID = 0;
    SnakeGame snake;
    for(vector<Chromosome>::iterator it = subjects.begin(); it != subjects.end(); it++, subjectID++){
        snake.createNewGame();
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
            stringstream ss;
            ss << generationID;
            (*it).writeToFile("chromobest" + ss.str());
        }else if (subjectID%10000 == 0){
            stringstream ss;
            ss << generationID << "_" << subjectID;
            (*it).writeToFile("chromo" + ss.str());
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
        mating(children, parents[i], parents[i+1]);
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
    child1.getTraits().MOVE_EMPTY_RIGHT = mother.getTraits().MOVE_EMPTY_RIGHT;
    child1.getTraits().MOVE_EMPTY_LEFT = father.getTraits().MOVE_EMPTY_LEFT ;
    child1.getTraits().MOVE_EMPTY_DOWN = mother.getTraits().MOVE_EMPTY_DOWN;
    child1.getTraits().MOVE_EMPTY_UP = father.getTraits().MOVE_EMPTY_UP;
    child1.getTraits().NOT_MOVE_WALL_RIGHT = mother.getTraits().NOT_MOVE_WALL_RIGHT;
    child1.getTraits().NOT_MOVE_WALL_LEFT = father.getTraits().NOT_MOVE_WALL_LEFT;
    child1.getTraits().NOT_MOVE_WALL_LEFT = mother.getTraits().NOT_MOVE_WALL_LEFT;
    child1.getTraits().NOT_MOVE_WALL_UP = father.getTraits().NOT_MOVE_WALL_UP;
    child1.getTraits().MOVE_FRUIT_RIGHT = mother.getTraits().MOVE_FRUIT_RIGHT;
    child1.getTraits().MOVE_FRUIT_LEFT = father.getTraits().MOVE_FRUIT_LEFT;
    child1.getTraits().MOVE_FRUIT_DOWN = mother.getTraits().MOVE_FRUIT_DOWN;
    child1.getTraits().MOVE_FRUIT_UP = father.getTraits().MOVE_FRUIT_UP;
    child1.getTraits().NOT_MOVE_SNAKEBODY_RIGHT = mother.getTraits().NOT_MOVE_SNAKEBODY_RIGHT;
    child1.getTraits().NOT_MOVE_SNAKEBODY_LEFT = father.getTraits().NOT_MOVE_SNAKEBODY_LEFT;
    child1.getTraits().NOT_MOVE_SNAKEBODY_DOWN = mother.getTraits().NOT_MOVE_SNAKEBODY_DOWN;
    child1.getTraits().NOT_MOVE_SNAKEBODY_UP = father.getTraits().NOT_MOVE_SNAKEBODY_UP;
    child1.getTraits().MOVE_FRUIT_POSITIVE_X = mother.getTraits().MOVE_FRUIT_POSITIVE_X;
    child1.getTraits().MOVE_FRUIT_NEGATIVE_X = father.getTraits().MOVE_FRUIT_NEGATIVE_X;
    child1.getTraits().MOVE_FRUIT_POSITIVE_Y = mother.getTraits().MOVE_FRUIT_POSITIVE_Y;
    child1.getTraits().MOVE_FRUIT_NEGATIVE_Y = father.getTraits().MOVE_FRUIT_NEGATIVE_Y;
    child1.getTraits().emptyPriority = mother.getTraits().emptyPriority;
    child1.getTraits().wallPriority = father.getTraits().wallPriority;
    child1.getTraits().fruitPriority = mother.getTraits().fruitPriority;
    child1.getTraits().snakebodyPriority = father.getTraits().snakebodyPriority;
    child1.getTraits().fruitDistancePriority = mother.getTraits().fruitDistancePriority;
    
    child2.getTraits().MOVE_EMPTY_RIGHT = father.getTraits().MOVE_EMPTY_RIGHT;
    child2.getTraits().MOVE_EMPTY_LEFT = mother.getTraits().MOVE_EMPTY_LEFT;
    child2.getTraits().MOVE_EMPTY_DOWN = father.getTraits().MOVE_EMPTY_DOWN;
    child2.getTraits().MOVE_EMPTY_UP = mother.getTraits().MOVE_EMPTY_UP;
    child2.getTraits().NOT_MOVE_WALL_RIGHT = father.getTraits().NOT_MOVE_WALL_RIGHT;
    child2.getTraits().NOT_MOVE_WALL_LEFT = mother.getTraits().NOT_MOVE_WALL_LEFT;
    child2.getTraits().NOT_MOVE_WALL_LEFT = father.getTraits().NOT_MOVE_WALL_LEFT;
    child2.getTraits().NOT_MOVE_WALL_UP = mother.getTraits().NOT_MOVE_WALL_UP;
    child2.getTraits().MOVE_FRUIT_RIGHT = father.getTraits().MOVE_FRUIT_RIGHT;
    child2.getTraits().MOVE_FRUIT_LEFT = mother.getTraits().MOVE_FRUIT_LEFT;
    child2.getTraits().MOVE_FRUIT_DOWN = father.getTraits().MOVE_FRUIT_DOWN;
    child2.getTraits().MOVE_FRUIT_UP = mother.getTraits().MOVE_FRUIT_UP;
    child2.getTraits().NOT_MOVE_SNAKEBODY_RIGHT = father.getTraits().NOT_MOVE_SNAKEBODY_RIGHT;
    child2.getTraits().NOT_MOVE_SNAKEBODY_LEFT = mother.getTraits().NOT_MOVE_SNAKEBODY_LEFT;
    child2.getTraits().NOT_MOVE_SNAKEBODY_DOWN = father.getTraits().NOT_MOVE_SNAKEBODY_DOWN;
    child2.getTraits().NOT_MOVE_SNAKEBODY_UP = mother.getTraits().NOT_MOVE_SNAKEBODY_UP;
    child2.getTraits().MOVE_FRUIT_POSITIVE_X = father.getTraits().MOVE_FRUIT_POSITIVE_X;
    child2.getTraits().MOVE_FRUIT_NEGATIVE_X = mother.getTraits().MOVE_FRUIT_NEGATIVE_X;
    child2.getTraits().MOVE_FRUIT_POSITIVE_Y = father.getTraits().MOVE_FRUIT_POSITIVE_Y;
    child2.getTraits().MOVE_FRUIT_NEGATIVE_Y = mother.getTraits().MOVE_FRUIT_NEGATIVE_Y;
    child2.getTraits().emptyPriority = father.getTraits().emptyPriority;
    child2.getTraits().wallPriority = mother.getTraits().wallPriority;
    child2.getTraits().fruitPriority = father.getTraits().fruitPriority;
    child2.getTraits().snakebodyPriority = mother.getTraits().snakebodyPriority;
    child2.getTraits().fruitDistancePriority = father.getTraits().fruitDistancePriority;
    
    if(rand()%100+1 < mutationProbability){
        child1.mutate();
    }
    
    if(rand()%100+1 < mutationProbability){
        child2.mutate();
    }
    
    children.push_back(child1);
    children.push_back(child2);
}

double Generation::getAverageFitness(){
    double totalFitness = 0;
    for (vector<Chromosome>::iterator it = subjects.begin(); it!= subjects.end();it++){
        totalFitness += (*it).getFitness();
    }
    return totalFitness/subjects.size();
}

