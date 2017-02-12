//
//  generation.hpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#ifndef generation_hpp
#define generation_hpp

#include "chromosome.hpp"

class Generation{
private:
    vector<Chromosome> subjects;
    int generationID;
    int maxFitness;
    float averageFitness;
    float mutationProbability;
public:
    void run();
    void writeToFile(string filename);
    Generation generateNextGeneration();
};

#endif /* generation_hpp */
