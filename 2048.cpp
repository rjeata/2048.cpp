#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define QUIT 113

bool processInput(std::string);
void playGame();
bool moveArray(int[4][4], int);
void displayArray(int[4][4]);
bool checkValidMoves(int[4][4]);
bool isFull(int[4][4]);

int main(){
    std::string input;

    std::cout << "Welcome to 2048" << std::endl;

    do{
        std::cout << "1     -   Start Game\n";
        std::cout << "2     -   How to Play\n";
        std::cout << "3/q   -   Quit\n";

        std::cin >> input;
    }while(processInput(input));

    if(input == "1")
        playGame();

    std::cout << "Thank you for playing, Goodbye\n";

    return 0;
}

bool processInput(std::string input){
    if(input == "1")
        return false;
    else if(input == "2")
        std::cout << "How to Play\n";
    else if(input == "3" or input == "q"){
        std::cout << "Quitting\n";
        return false;
    }
    else
        std::cout << "Invalid Input\n";
    
    return true;
}

void playGame(){
    //  initialize starting array
    int array[4][4] = {0};
    int randX = 0;
    int randY = 0;
    int input = 0;
    
    srand(time(NULL));

    //  populate random array locations
    array[rand() % 4][rand() % 4] = 2;
    array[rand() % 4][rand() % 4] = 2; 

   while(true){
        //  clear consle and print array
        system("cls");
        displayArray(array);

        std::cout << "Waiting for move. (q - Exit game) \n";
        input = getch();

        //  if input is valid, move array
        if(moveArray(array, input)){
            system("cls");
            displayArray(array);

            //  check if there are any valid moves left, if so, populate a new tile
            if(checkValidMoves(array) and !isFull(array)){
                
                /*
                    TODO:
                        -   figure out how to add two tiles at once
                        -   figure out how to add 4 instead of 2 sometimes
                */
                while(array[randX][randY] != 0){
                    randX = rand() % 4;
                    randY = rand() % 4;
                }
            
                //  set tile equal to 2
                array[randX][randY] = 2;
            }

            //  else if there are no valid moves left, end game
            else if(!checkValidMoves(array)){
                std::cout << "Game Over\n";
                break;
            }
        }

        //  else if input is quit, ask for confirmation
        else if(input == QUIT){
            std::cout << "Quit game? (q)\nPress any input to cancel.\n";

            input = getch();
            if(input == QUIT)  
                break;
        }
    } 
}

bool moveArray(int array[4][4], int move){
    int lastMerge = 0;
    int prevPos = 0;
    int nextPos = 0;

    if(move == KEY_UP){
        for(int j = 0; j < 4; j++){
            lastMerge = 0;

            for(int i = 1; i < 4; i++){
                if(array[i][j] != 0){
                    prevPos = i - 1;

                    //  skip empty tiles about current
                    while(prevPos > lastMerge and array[prevPos][j] == 0){ 
                        prevPos--;
                    }

                    //  move to empty tile
                    if(array[prevPos][j] == 0){
                        array[prevPos][j] = array[i][j];
                    }
                    
                    //  combine matching tiles
                    else if(array[prevPos][j] == array[i][j]){
                        array[prevPos][j] *= 2;
                        lastMerge = prevPos + 1;
                    }
                    
                    //  move to next tile
                    else if(array[prevPos][j] != array[i][j] and prevPos + 1 != i){
                        array[prevPos + 1][j] = array[i][j];
                    }
                    if(prevPos + 1 != i or array[i][j] == array[prevPos][j]){
                        array[i][j] = 0;
                    }
                }
            }
        }

        return true;
    }
    else if(move == KEY_DOWN){
        for(int j = 0; j < 4; j++){
            lastMerge = 3;

            for(int i = 2; i >= 0; i--){
                if(array[i][j] != 0){
                    nextPos = i + 1;

                    //  skip empty tiles 
                    while(nextPos < lastMerge and array[nextPos][j] == 0){ 
                        nextPos++;
                    }

                    //  move to empty tile
                    if(array[nextPos][j] == 0){ 
                        array[nextPos][j] = array[i][j];
                    }

                    //  merge matching tiles
                    else if(array[nextPos][j] == array[i][j]){
                        array[nextPos][j] *= 2;
                     lastMerge = nextPos - 1;
                    }

                    //  move to next tile
                    else if(array[nextPos][j] != array[i][j] and nextPos - 1 != i){ 
                    }

                    if(nextPos - 1 != i or array[i][j] == array[nextPos][j]){
                        array[i][j] = 0;
                    }
                }
            }
        }

        return true;
    }

    else if(move == KEY_LEFT){
        for(int i = 0; i < 4; i++){
            lastMerge = 0;

            for(int j = 1; j < 4; j++){
                if(array[i][j] != 0){
                    int prevPos = j - 1;

                    //  skip empty tiles to the left 
                    while(prevPos > lastMerge and array[i][prevPos] == 0){
                        --prevPos;
                    }

                    //  move to empty tile
                    if(array[i][prevPos] == 0){
                        array[i][prevPos] = array[i][j];
                    }

                    //  combine matching tile
                    else if(array[i][prevPos] == array[i][j]){
                        array[i][prevPos] *= 2;
                        lastMerge = prevPos + 1;
                    }

                    //  move to next position
                    else if(array[i][prevPos] != array[i][j] and prevPos + 1 != j){
                        array[i][prevPos + 1] = array[i][j];
                    }

                    if(prevPos + 1 != j or array[i][j] == array[i][prevPos]){
                        array[i][j] = 0;
                    }
                }
            }
        }
        return true;
    }

    else if(move == KEY_RIGHT){
        for(int i = 0; i < 4; i++){
            lastMerge = 3;

            for(int j = 2; j >= 0; j--){
                if(array[i][j] != 0){
                    nextPos = j + 1;

                    //  skip to empty tile to the right
                    while(nextPos < lastMerge and array[i][nextPos] == 0){
                        nextPos++;
                    }

                    //  move to empty tile
                    if(array[i][nextPos] == 0){
                        array[i][nextPos] = array[i][j];
                    }

                    //  combine matching tile
                    else if(array[i][nextPos] == array[i][j]){
                        array[i][nextPos] *= 2;
                        lastMerge = nextPos - 1;
                    }

                    //  move to next position
                    else if(array[i][nextPos] != array[i][j] and nextPos - 1 != j){
                        array[i][nextPos - 1] = array[i][j];
                    }

                    if(nextPos - 1 != j or array[i][j] == array[i][nextPos]){
                        array[i][j] = 0;
                    }
                }
            }
        }

        return true;
    }

    return false;
}

bool checkValidMoves(int array[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            //  check above, below, left, and right for valid moves, 
            //      return true if there are any
            if(i > 0 and array[i][j] == array[i-1][j]) 
                return true; 
            if(i < 3 and array[i][j] == array[i+1][j]) 
                return true;
            if(j > 0 and array[i][j] == array[i][j-1]) 
                return true; 
            if(j < 3 and array[i][j] == array[i][j+1]) 
                return true; 
        }
    }

    return false;
}

bool isFull(int array[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            //  check if there are any empty tiles
            if(array[i][j] == 0)
                return false;
        }
    }

    return true;
}

void displayArray(int array[4][4]){
    std::cout << "-------------------------------------\n";

    for(int i = 0; i < 4; i++){
        std::cout << "|";
        for(int j = 0; j < 4; j++){
            std::cout << std::setfill(' ') << std::setw(5) 
                << array[i][j] << "   |";
        }
        std::cout << "\n-------------------------------------\n";

    }
}