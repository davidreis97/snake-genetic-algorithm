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
    srand(time(NULL));
    Generation gen(100000,true);
    while(gen.getAverageFitness() < 5){
        gen.runSnake(false, 0);
        gen.generateNextGeneration();
        cout << "Generation size is " << gen.getPopulation() << "." << endl;
    }
}
