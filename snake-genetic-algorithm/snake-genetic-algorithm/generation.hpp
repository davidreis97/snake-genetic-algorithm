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
#include <chrono>
#include <algorithm>

template <class Comparable>
void quickSort(vector<Comparable> &arr, int left, int right) { //http://www.algolist.net/Algorithms/Sorting/Quicksort
    int i = left, j = right;
    Comparable tmp;
    Comparable pivot = arr[(left + right) / 2];
    
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

class Generation{
private:
    vector<Chromosome> subjects;
    int generationID;
    int maxFitness;
    int mutationProbability; //0 - 100
public:
    void runSnake(bool drawGame, int timeBetweenMove);
    void runSnake(bool drawGame, int timeBetweenMove, Chromosome chromo);
    void writeToFile(string filename);
    void generateNextGeneration();
    Generation(int numberOfSubjects, int mutationProbability);
    void mating(vector<Chromosome>& children, Chromosome father, Chromosome mother);
    double getAverageFitness();
    unsigned long getPopulation(){return subjects.size();}
    void nextThread(int index, int maxSteps);
};

#endif /* generation_hpp */
