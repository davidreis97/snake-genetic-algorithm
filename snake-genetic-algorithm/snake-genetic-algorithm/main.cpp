//
//  main.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "generation.hpp"

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    Generation gen(10,true);
    gen.runSnake(true, 1);
    
    //FIX FITNESS CALCULATION BUG
}
