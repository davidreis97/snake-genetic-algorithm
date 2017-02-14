//
//  main.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "generation.hpp"

void replayGeneration();
void runFromStart(int numberOfSubjects, int mutationProbability, bool printGames, int timeBetweenTicks, int numberOfGenerations);

int main(int argc, const char * argv[]) {
    cout.precision(10);
    cout << fixed;
    srand((unsigned int)time(NULL));
    runFromStart(100000, 30, true, 100, 10000);
    //replayGeneration();
}

void runFromStart(int numberOfSubjects, int mutationProbability, bool printGames, int timeBetweenTicks, int numberOfGenerations){
    Generation gen(numberOfSubjects,mutationProbability);
    int counter = 0;
    while(counter < numberOfGenerations){
        gen.runSnake(printGames, timeBetweenTicks);
        gen.generateNextGeneration(); 
        cout << "Generation size is " << gen.getPopulation() << "." << endl;
        counter++;
    }
}

void replayGeneration(){
    cout << "Please insert generationID ([GEN]_[SUBJECT] or best[GEN]): " << endl;
    string generationID;
    cin >> generationID;
    stringstream ss;
    ss << "chromo" << generationID;
    cout << "Loading " << ss.str() << endl;
    Chromosome chromo;
    chromo.readFromFile(ss.str());
    chromo.runSnake(true, 200, ss.str());
}
