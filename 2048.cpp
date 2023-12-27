#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define QUIT 113

bool processInput(std::string);
void playGame();
bool moveArray(int[4][4], int);
void displayArray(int[4][4]);

int main(){
    std::string input;

    std::cout << " Welcome to 2048" << std::endl;

    do{
        std::cout << "1     -   Start Game\n";
        std::cout << "2     -   How to Play\n";
        std::cout << "3/q   -   Quit\n";

        std::cin >> input;
    }while(processInput(input));

    std::cout << "---------------------\n";

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
    else if(input == "3" || input == "q"){
        std::cout << "Quitting\n";
        return false;
    }
    else
        std::cout << "Invalid Input\n";
    
    return true;
}

void playGame(){
    std::cout << "Starting game....\n";
    srand(time(0));
    
    //  initialize starting array
    int array[4][4] = {0};
    bool noMoves = false;
    int randX = 0;
    int ranY = 0;
    std::string move; 

    int input = 0;

    array[rand() % 4][rand() % 4] = 2;
    array[rand() % 4][rand() % 4] = 2; 

   while(true){
        displayArray(array);
        std::cout << "Waiting for move. (q - Exit game) \n";
        input = getch();

        if(moveArray(array, input)){
            displayArray(array);

            randX = rand() % 4;
            ranY = rand() % 4;

            if(array[randX][ranY] == 0)
                array[randX][ranY] = 2;
            /* else{
                std::cout << "No more moves\n";
                std::cout << "Game Over\n";
                break;
            } */
        }
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
                    if(prevPos + 1 != i || array[i][j] == array[prevPos][j]){
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
                    while(nextPos < lastMerge && array[nextPos][j] == 0){ 
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
                    else if(array[nextPos][j] != array[i][j] && nextPos - 1 != i){ 
                    }

                    if(nextPos - 1 != i || array[i][j] == array[nextPos][j]){
                        array[i][j] = 0;
                    }
                }
            }
        }

        return true;
    }

    if(move == KEY_LEFT){
        for(int i = 0; i < 4; i++){
            lastMerge = 0;
            for(int j = 1; j < 4; j++){
                if(array[i][j] != 0){
                    int prevPos = j - 1;

                    //  skip empty tiles to the left 
                    while(prevPos > lastMerge && array[i][prevPos] == 0){
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
                    else if(array[i][prevPos] != array[i][j] && prevPos + 1 != j){
                        array[i][prevPos + 1] = array[i][j];
                    }

                    if(prevPos + 1 != j || array[i][j] == array[i][prevPos]){
                        array[i][j] = 0;
                    }
                }
            }
        }
        return true;
    }

    if(move == KEY_RIGHT){
        for(int i = 0; i < 4; i++){
            lastMerge = 3;
            for(int j = 2; j >= 0; j--){
                if(array[i][j] != 0){
                    nextPos = j + 1;

                    //  skip to empty tile to the right
                    while(nextPos < lastMerge && array[i][nextPos] == 0){
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
                    else if(array[i][nextPos] != array[i][j] && nextPos - 1 != j){
                        array[i][nextPos - 1] = array[i][j];
                    }

                    if(nextPos - 1 != j || array[i][j] == array[i][nextPos]){
                        array[i][j] = 0;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

void displayArray(int array[4][4]){
    std::cout << "---------------------\n";

    for(int i = 0; i < 4; i++){
        std::cout << "|";
        for(int j = 0; j < 4; j++){
            std::cout << array[i][j] << "|";
        }
        std::cout << std::endl;
    }

    std::cout << "---------------------\n";
}