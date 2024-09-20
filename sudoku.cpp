#include <iostream>
#include <cstdlib> // for system(cls) - to clear screen
#include <vector>
#include <random> // to randomize numbers
#include <algorithm> // for shuffle()
#include <ctime> // for time()

using namespace std;

const int SIZE = 9;

// Check if number can be placed at given position
bool isValid(int board[SIZE][SIZE],int row,int col,int num){
    // check row
    for(int i=0;i<SIZE;i++){
        if(board[row][i] == num){
            return false;
        }
    }

    // check coloumn
    for(int i=0;i<SIZE;i++){
        if(board[i][col] == num){
            return false;
        }
    }

    // check 3x3 box
    int boxRow = row - (row%3);
    int boxCol = col - (col%3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[boxRow + i][boxCol + j] == num){
                return false;
            }
        }
    }

    return true;
}

// Generate a solved Sudoku board using Backtracking
bool generateBoard(int board[SIZE][SIZE]){
    random_device randev;
    mt19937 gen(randev() + time(0));
    vector <int> number = {1,2,3,4,5,6,7,8,9};
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(board[i][j] == 0) // checks if that cell is 0 or not
            {
                shuffle(number.begin(), number.end(), gen);
            for(int num : number){
                if(isValid(board,i,j,num)){ // check validation of the number in the current cell using the isValid() function 
                    board[i][j] = num;
                    if(generateBoard(board)) return true; // it recursively call the function to fill all the next cells then return true
                    board[i][j] = 0; // Backtrack - if the recursive call returns false, resets the cell to 0 and tries the loop.
                }
            }
            return false;
            }
        }
    }
    return true;
}

// Replace blanks(0) in place of numbers
void generateBlanks(int board[SIZE][SIZE],int difficulty){
    srand(time(0));
    int blanks = 0;
    while(blanks < difficulty){
        int row = rand()%8; // generate random number between 0 to 8
        int col = rand()%8;

        if(board[row][col] != 0){ // to ensure that it doesn't repeate in same place
            board[row][col] = 0;
            blanks++;
        }
    }
}

bool checkWin(int board[SIZE][SIZE]){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(board[i][j] == 0) return false;
        }
    }
    return true;
}

// Display the sudoku board in console
void printBoard(int board[SIZE][SIZE]){
    cout<<"    1 2 3   4 5 6   7 8 9"<<endl;
    cout<<"  -------------------------"<<endl;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(j == 0){
                cout<<char(i+65)<<" | ";
            }

            if(board[i][j] == 0){
                cout<<"_ ";
            } else {
                cout<<board[i][j]<<" ";
            }
            
            if((j+1)%3 == 0){
                cout<<"| ";
            }
        }
        if((i+1)%3 == 0 && i+1<SIZE){
            cout<<endl<<"  |-------|-------|-------|"<<endl;
        } else {
            cout<<endl;
        }
    }
    cout<<"  -------------------------"<<endl<<endl;
    cout<<"  C H O O S E : ";
}

// menu interface
void mainmenu(){
    cout<<"###########################################"<<endl;
    cout<<"################# M E N U #################"<<endl;
    cout<<"###########################################"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##     [1] P L A Y                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##     [2] H E L P                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"###########################################"<<endl<<endl;
    cout<<"       C H O I C E : ";
}

// describe the game to the user
void help(){
    cout<<"###########################################"<<endl;
    cout<<"################# H E L P #################"<<endl;
    cout<<"###########################################"<<endl;
    cout<<"##  A. To Enter a Number in a Cell :     ##"<<endl;
    cout<<"##     <row><column> <number>            ##"<<endl;
    cout<<"##     e.g : D6 9                        ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##  B. Enter Serial No. to choose        ##"<<endl;
    cout<<"##     from menus                        ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"###########################################"<<endl<<endl;
    cout<<"       [1] B A C K"<<endl<<endl;
    cout<<"       C H O I C E : ";
}

// difficulty choosing interface
int difficultymenu(){
    cout<<"###########################################"<<endl;
    cout<<"########### D I F F I C U L T Y ###########"<<endl;
    cout<<"###########################################"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##     [1] E A S Y                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##     [2] M E D I U M                   ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"##     [3] H A R D                       ##"<<endl;
    cout<<"##                                       ##"<<endl;
    cout<<"###########################################"<<endl<<endl;
    cout<<"       C H O I C E : ";


    int choice;
    cin>>choice;
    system("cls");
    switch (choice){
        case 1 : // easy

            return 25;
                
            case 2 : // medium
                return 35;
                
            case 3 : // hard
                return 45;
                
            default :
            cout<<"Invalid Difficulty! Setting difficulty to medium."<<endl;
                return 35;
        }
}

int main() {
    system("cls");
    int board[SIZE][SIZE] = {{0}};
    generateBoard(board);

    int menu,difficulty,helpchoice;
    int row,col,num;
    char chRow;

    do {
        mainmenu();
        cin>>menu;
        system("cls");

        if(menu == 1) {
            difficulty = difficultymenu(); // difficulty setting
            generateBlanks(board,difficulty);
            do {
                printBoard(board);
                cin.ignore(); // clear garbage value
                cin>>chRow>>col>>num;

                row = int(toupper(chRow) - 65);
                col--;

                if(isValid(board,row,col,num)){
                    board[row][col] = num;
                    system("cls");
                } else {
                    system("cls");
                    cout<<"Invalid Number.\n\n";
                }
                if(checkWin(board) == 1){
                    system("cls");
                    cout<<endl;
                    cout<<"###########################################"<<endl;
                    cout<<"##       CONGRATULATION! YOU WON.        ##"<<endl;
                    cout<<"###########################################"<<endl;
                    return 0;
                }
            } while(1);
        }
        else if(menu == 2) {
            help();
            cin>>helpchoice;
            if(helpchoice == 1){
                system("cls");
            }
        }
        else {
            cout<<"Invalid Choice!"<<endl;
            break;
        }
    } while(1);
}