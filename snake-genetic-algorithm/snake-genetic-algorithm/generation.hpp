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
#include <thread>

template <class Comparable>
void quickSort(vector<Comparable> &arr, int left, int right) { //http://www.algolist.net/Algorithms/Sorting/Quicksort
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
    
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
    float averageFitness;
    int mutationProbability; //0 - 100
public:
    void runSnake(bool drawGame, int timeBetweenMove);
    void writeToFile(string filename);
    Generation generateNextGeneration();
    Generation(int numberOfSubjects, bool randomize);
};

#endif /* generation_hpp */
