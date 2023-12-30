#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <cctype>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define QUIT 113

bool processInput(std::string);
void playGame();
bool moveArray(int[4][4], int, int &);
void displayArray(int[4][4]);
bool checkValidMoves(int[4][4]);
bool isFull(int[4][4]);
bool getScore(int[4][4]);

int main(){
    std::string input;

    system("cls");

    //  print title screen until user quits or starts game
    do{
        std::cout << "|\033[0;43m              \033[0m|\n";
        std::cout << "|\033[0;43m              \033[0m|\n";
        std::cout << "|\033[0;43;33m  2  0  4  8  \033[0m|\n";
        std::cout << "|\033[0;43m              \033[0m|\n";
        std::cout << "|\033[0;43m              \033[0m|\n";

        std::cout << "(S)tart Game\n";
        std::cout << "(H)ow to Play\n";
        std::cout << "(Q)uit\n";

        std::cout << "Enter input: ";
        std::cin >> input;

        std::cout << input << std::endl;

    }while(processInput(input));

    return 0;
}

bool processInput(std::string input){
    //  if user wishes to start game a game
    if(input == "S" or input == "s"){
        playGame();
        std::cout << "Thank you for playing, Goodbye\n";

        return false;
    }
    
    //  else if user wishes to learn how to play
    else if(input == "H" or input == "h"){
        system("cls");
        std::cout << "How to Play\n";

        int array[4][4] = {0};
        array[1][1] = 2;
        array [2][2] = 4;

        displayArray(array);

        std::cout << "Use the arrow keys to move the tiles in the direction of the arrow.\n";

        std::cout << "Enter any input to continue.\n";
        getch();

        system("cls");

        array[1][1] = 0;
        array [2][2] = 0;

        array[0][1] = 2;
        array[0][2] = 4;
        array[3][1] = 2;

        displayArray(array);

        std::cout << "When two tiles with the same number touch, they merge and double in number!\n";
        std::cout << "Enter any input to continue.\n";
        getch();

        system("cls");

        array[0][1] = 4;
        array[0][2] = 4;
        array[3][1] = 0;

        displayArray(array);

        std::cout << "Get a tile to 2048 to win!\n";

        std::cout << "Enter any input to return to main menu.\n";
        getch();
    }

    //  else if user wishes to quit game
    else if(input == "Q" or input == "q"){
        std::cout << "Thank you for playing, Goodbye\n";

        return false;
    }

    //  else user input is invalid
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
    int score = 0;
    bool win = false;           //  flag for if user has won
    
    srand(time(NULL));

    //  populate random array locations
    array[rand() % 4][rand() % 4] = 2;
    array[rand() % 4][rand() % 4] = 2; 

   while(true){
        //  clear consle and print array
        system("cls");
        displayArray(array);
        std::cout << "Score = " << score << std::endl;

        std::cout << "Waiting for move. (q - Exit game) \n";
        input = getch();

        //  if input is valid, move array
        if(moveArray(array, input, score)){
            system("cls");
            displayArray(array);

            if(!win and getScore(array)){
                std::cout << "Congradulations, you win!\n";
                std::cout << "Quit game? (q)\nPress any input to continue game.\n";

                input = getch();
                if(input == QUIT)  
                    break;
                else 
                    win = true;
            }

            //  check if there are any valid moves left, if so, populate a new tile
            if(checkValidMoves(array) and !isFull(array)){
                randX = rand() % 4;
                randY = rand() % 4;

                while(array[randX][randY] != 0){
                    randX = rand() % 4;
                    randY = rand() % 4;
                }
                
                int r = rand() % 10;

                //  set new tile to 2 if random number is less than 9, else set to 4
                if(r < 9)
                    array[randX][randY] = 2;
                else 
                    array[randX][randY] = 4;
            }
        }

        //  else end game if there are no valid moves left
        else if(!checkValidMoves(array)){
            std::cout << "Score = " << score << std::endl;
            std::cout << "Game Over\n";
            break;
        }

        //  else if input is quit, ask for confirmation then quit
        else if(input == QUIT){
            std::cout << "Quit game? (q)\nPress any input to cancel.\n";

            input = getch();
            if(input == QUIT)  
                break;
        }
    } 
}

bool moveArray(int array[4][4], int move, int & score){
    int lastMerge = 0;
    int prevPos = 0;
    int nextPos = 0;
    bool swapped = false;

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
                        swapped = true;
                    }
                    
                    //  combine matching tiles
                    else if(array[prevPos][j] == array[i][j]){
                        array[prevPos][j] *= 2;
                        array[i][j] = 0;

                        score += array[prevPos][j];
                        
                        lastMerge = prevPos + 1;
                        swapped = true;
                    }
                    
                    //  move to next tile
                    else if(array[prevPos][j] != array[i][j] and prevPos + 1 != i){
                        array[prevPos + 1][j] = array[i][j];
                        swapped = true;
                    }

                    if(prevPos + 1 != i or array[i][j] == array[prevPos][j]){
                        array[i][j] = 0; 
                        swapped = true;
                    }
                }
            }
        }
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
                        swapped = true;
                    }

                    //  merge matching tiles
                    else if(array[nextPos][j] == array[i][j]){
                        array[nextPos][j] *= 2;
                        array[i][j] = 0;
                        lastMerge = nextPos - 1;
                        swapped = true;

                        score += array[nextPos][j];
                    }

                    //  move to next tile
                    else if(array[nextPos][j] != array[i][j] and nextPos - 1 != i){ 
                        array[nextPos - 1][j] = array[i][j];
                        swapped = true;
                    }

                    if(nextPos - 1 != i or array[i][j] == array[nextPos][j]){
                        swapped = true;
                        array[i][j] = 0;
                    }
                }
            }
        }
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
                        swapped = true;
                    }

                    //  combine matching tile
                    else if(array[i][prevPos] == array[i][j]){
                        array[i][prevPos] *= 2;
                        array[i][j] = 0;
                        lastMerge = prevPos + 1;
                        swapped = true;

                        score += array[i][prevPos];
                    }

                    //  move to next position
                    else if(array[i][prevPos] != array[i][j] and prevPos + 1 != j){
                        array[i][prevPos + 1] = array[i][j];
                        swapped = true;
                    }

                    if(prevPos + 1 != j or array[i][j] == array[i][prevPos]){
                        array[i][j] = 0;
                        swapped = true;
                    }
                }
            }
        }
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
                        swapped = true;
                    }

                    //  combine matching tile
                    else if(array[i][nextPos] == array[i][j]){
                        array[i][nextPos] *= 2;
                        array[i][j] = 0;
                        lastMerge = nextPos - 1;
                        swapped = true;

                        score += array[i][nextPos];
                    }

                    //  move to next position
                    else if(array[i][nextPos] != array[i][j] and nextPos - 1 != j){
                        array[i][nextPos - 1] = array[i][j];
                        swapped = true;
                    }

                    if(nextPos - 1 != j or array[i][j] == array[i][nextPos]){
                        array[i][j] = 0;
                        swapped = true;
                    }
                }
            }
        }
    }

    return swapped;
}

bool checkValidMoves(int array[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            //  check if tile is empty, alo check above, below, left, and right for 
            //      valid moves, return true if there are any
            if(array[i][j] == 0)
                return true;
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
    std::cout << "------------------------------------------\n";

    for(int i = 0; i < 4; i++){
        std::cout << "|";

        for(int j = 0; j < 4; j++){
            switch(array[i][j]){
                case 2:     std::cout << "\033[0;47;33m"; break; // white background yellow text
                case 4:     std::cout << "\033[0;42;31m"; break; // green background red text
                case 8:     std::cout << "\033[0;43;32m"; break; // yellow background green text
                case 16:    std::cout << "\033[0;44;34m"; break; // blue background blue text
                case 32:    std::cout << "\033[0;45;32m"; break; // purple background green text
                case 64:    std::cout << "\033[0;46;33m"; break; // cyan background yellow text
                case 128:   std::cout << "\033[0;42;34m"; break; // green background blue text
                case 256:   std::cout << "\033[0;102;33m"; break; // high green background yellow text
                case 512:   std::cout << "\033[0;103;31m"; break; // high yellow background red text
                case 1024:  std::cout << "\033[0;106;33m"; break; // high cyan background yellow text
                case 2048:  std::cout << "\033[0;41;33m"; break; // red background yellow text
                case 4096:  std::cout << "\033[0;41;30m"; break; // black background yellow text

                // Add more cases if needed
                default:    std::cout << "\033[0m";  break; // Reset
            }
            std::cout << std::setfill(' ') << std::setw(5) << array[i][j] << "    \033[0m "; //  |";
        }
        std::cout << "|\n------------------------------------------\n";

    }

}

bool getScore(int array[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] == 2048)
                return true;
        }
    }

    return false;
}