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
void runSimulationMenu();

int main(int argc, const char * argv[]) {
    cout.precision(10);
    cout << fixed;
    srand((unsigned int)time(NULL));
	cout << "Snake Genetic Algorithm" << endl;
	cout << "1- Run the simulation" << endl;
	cout << "2- Replay a specific chromosome" << endl;
	int choice = 0;
	cin >> choice;
	switch (choice) {
		case 1:
            runSimulationMenu();
			break;
		case 2:
			replayGeneration();
			break;
	}
}

void runSimulationMenu(){
    cout << "Do you wish to see the games playing as they are generated? (Answering yes will make the simulation significantly slower)" << endl;
    cout << "1- Yes" << endl;
    cout << "2- No" << endl;
    int choice = 0;
    cin >> choice;
    switch (choice) {
        case 1:
            runFromStart(100000, 30, true, 100, 100);
            break;
        case 2:
            runFromStart(100000, 30, false, 100, 100);
            break;
    }

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
