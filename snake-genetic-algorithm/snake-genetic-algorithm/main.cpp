//
//  main.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "generation.hpp"


int main(int argc, const char * argv[]) {
    cout.precision(10);
    cout << fixed;
    srand((unsigned int)time(NULL));
    Generation gen(100000,20);
    while(1){
        gen.runSnake(false, 250);
        gen.generateNextGeneration();
        cout << "Generation size is " << gen.getPopulation() << "." << endl;
    }
}


/*
int main(){
    cout << "Please insert generationID ([GEN]_[SUBJECT] or best[GEN]): " << endl;
    string generationID;
    cin >> generationID;
    while(1){
        stringstream ss;
        ss << "chromo" << generationID;
        cout << "Reading from " << ss.str() << endl;
        Chromosome chromo;
        chromo.readFromFile(ss.str());
        chromo.runSnake(true, 150);
        generationID++;
    }
}*/
