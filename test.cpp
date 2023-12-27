#include <iostream>
#include <ctime>
#include <cstdlib>

bool processInput(std::string);
void playGame();
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

    array[rand() % 4][rand() % 4] = 2;
    array[rand() % 4][rand() % 4] = 2; 

    displayArray(array);

    //  move up
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] != 0 and i != 0){
                if (array[0][j] == array[i][j] or array[0][j] == 0)
                   array[0][j] += array[i][j];
                else if(array[1][j] == array[i][j])  
                    array[1][j] += array[i][j];
                else if(array[2][j] == array[i][j])  
                    array[2][j] += array[i][j];
                else if(array[3][j] == array[i][j])  
                    array[3][j] += array[i][j];
                else   
                    continue;

                array[i][j] = 0;
            }
        }
    }

    displayArray(array);

    //  move down

    //  move left

    //  move right


    array[rand() % 4][rand() % 4] = 2; 
    
    displayArray(array);


    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] != 0 and i != 0){
                if (array[0][j] == array[i][j] or array[0][j] == 0)
                   array[0][j] += array[i][j];
                else if(array[1][j] == array[i][j] or array[1][j] == 0)  
                    array[1][j] += array[i][j];
                else if(array[2][j] == array[i][j] or array[2][j] == 0)  
                    array[2][j] += array[i][j];
                else if(array[3][j] == array[i][j] or array[3][j] == 0)  
                    array[3][j] += array[i][j];
                else   
                    noMoves = true;

                if(!noMoves)
                    array[i][j] = 0;
            }
        }
    }

    //  show array
    displayArray(array);

    //  create new numbers in array

    //  repeat
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