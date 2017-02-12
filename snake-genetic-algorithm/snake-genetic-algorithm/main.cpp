//
//  main.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include "chromosome.hpp"

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    SnakeGame snake;
    while(1){
        snake.drawGame();
    }
}
