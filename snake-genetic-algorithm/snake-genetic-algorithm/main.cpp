//
//  main.cpp
//  snake-genetic-algorithm
//
//  Created by David Reis on 12/02/2017.
//  Copyright © 2017 David Reis. All rights reserved.
//

#include <iostream>
#include "snake.hpp"

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    SnakeGame snake;
    string input;
    DIRECTION nextMove;
    while(1){
        snake.drawGame();
        cin >> input;
        if (input == "R"){
            nextMove = RIGHT;
        }else if (input == "L"){
            nextMove = LEFT;
        }else if (input == "U"){
            nextMove = UP;
        }else if (input == "D"){
            nextMove = DOWN;
        }else{
            cout << "Unrecognized input: " << input;
        }
        if (snake.nextTick(nextMove)){
            cout << "Still Alive" << endl;
        }else{
            cout << "You're Dead" << endl;
        }
    }
    
        
}
