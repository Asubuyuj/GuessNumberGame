/*
    GuessNumberGame
    This will use a random number generator to get number that user will try to guess
    This will have specific difficulties from easy to hard

    Author:
        Alex Subuyuj - January 2026

*/
#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

//enum for difficulties
enum DIFFICULTIES {EASY=2, MED, HARD};

//Function prototypes
pair<int, int> RandomNumber(int); //Generates random number using mt19937 engine + random_device
void MainMenu(); //Main menu where user will interact with options
void PlayGame(int); //Logic to play game
//int main(); //Main function of program
void ClearBuffer(); //Clears the buffer when user enters an invalid response
int Difficulties(); //Create Easy, Medium and Hard difficulties
bool UserNumberCheck(string); //will ensure user does not enter the same number within the same play
bool PrevEntryCheck(vector<string> his, string); //will check if user has already entered current number
void DisplayHistory(vector<string>);

int Difficulties (){
    int diffChoice;
    cout << endl;
    cout << "Please choose a difficulty\n";
    cout << endl;
    cout << "\t--------------Easy--------------\n\tRange: 1-5, Attempts: 2\n";
    cout << endl;
    cout << "\t--------------Medium--------------\n\tRange: 1-10, Attempts: 3\n";
    cout << endl;
    cout << "\t--------------Hard--------------\n\tRange: 1-15, Attempts: 4\n";
    cout << endl;
    cout << "1: Easy\n2: Medium\n3: Hard\n";
    while (true) {
        cout << "Choice: ";
        cin >> diffChoice;
        if (cin){
            switch (diffChoice)
            {
            case 1:
                return EASY;
                cout << "You chose Easy, good luck!\n"; 
                break;
            case 2:
                return MED;
                break;
            case 3:
                return HARD;
                break;
            default:
                cout << "Please enter a valid choice (1-3)\n";
                break;
            }
        } else {
            cout << "Please enter a numerical value\n";
            ClearBuffer();
            cout << endl;
        }
    }
}
pair<int, int> RandomNumber(int diff){
    int endRange;
    //getting random number from hardware to use as a seed
    random_device rd;

    //using mersenne_twister_engine to generate a random number
    mt19937 gen(rd());

    //if statement to determine range based on user entered difficulty level
    if (diff == EASY)
    {
        endRange = 5;
    } else if (diff == MED)
    {
        endRange = 10;
    } else if (diff == HARD)
    {
        endRange = 15;
    }
    
    
    //setting a distribution within the range of 1- to user selected range
    uniform_int_distribution range(1,endRange);
    //returning a pair with random number and current range (based on difficulty)
    return make_pair(range(gen), endRange);
}

//Validate if user entry is an int
bool UserNumberCheck(string curr){
    for (size_t i = 0; i < curr.length(); i++){
        if (!isdigit(curr[i])){
            return false;
        }
    }
    return true;
}

void PlayGame(int diff) {
    //Variables
    auto [cpuNum, range] = RandomNumber(diff);
    int numAttempts;
    int count = 1;
    int sizeCounter = 0;
    string userNum;
    vector<string> userHistory;
    //string userHistory[numAttempts];
    int prevNum = 0;
    bool userCheck;
    //if statement to determine range based on user entered difficulty level
    if (diff == EASY)
    {
        numAttempts = EASY;
    } else if (diff == MED)
    {
        numAttempts = MED;
    } else if (diff == HARD)
    {
        numAttempts = HARD;
    }


    //asking user for entry
    cout << "You have " << numAttempts << " attempt(s) to guess the correct number!\nGood Luck!\n";
    cout << endl;

    do {
        //displaying current attemp number
        if (count < numAttempts){
            cout << "---------- Attempt #" << count << "----------\n";
        } else {
            cout << "---------- Attempt #" << count << " Final Attempt!----------\n";
        }

        cout << "\n";
        cout << "Please enter a number: ";
        cin >> userNum;
        userCheck = UserNumberCheck(userNum);

        //runs after user entry has been validated
        if (!userCheck){
            cout << userNum << " is NOT a valid entry!\n";
            ClearBuffer();
        } else {
            //checks if user entry is within difficulty range
            if (stoi(userNum) < 1 || stoi(userNum) > range){
                cout << "Please choose a number from 1 - " << range << "\n";
                cout << "\n";
            } else {
                if (PrevEntryCheck(userHistory, userNum)){
                    cout << "\nAlready entered " << userNum << "\nPlease enter a different number\n";
                    cout << "\n";
                } else {
                    //breaks loop if user guessed number correctly
                    if (cpuNum == stoi(userNum)){
                        cout << "\n----------------- Winner! -----------------\n";// << cpuNum << "\n";

                        //adding correct entry into user entry history
                        //userHistory[sizeCounter++] = userNum;
                        userHistory.push_back(userNum);
                        break;
                    } else {
                        //if sizeCounter is less than numAttempts, will add userNum into array
                        if (sizeCounter < numAttempts){
                           userHistory.push_back(userNum);
                        }
                        cout << "Wrong number, try again!\n";
                        count++;
                    }
                }
            }
        }

    } while (count < (numAttempts+1));
    cout << "Correct number was: " << cpuNum << "\n";
    cout << "Would you like to play again?\n";
    DisplayHistory(userHistory);
    cout << "\n";

}

//Function to check previous user entry
bool PrevEntryCheck(vector<string> his, string currNum){
    for (string prevNums : his){
        if (prevNums == currNum){
            return true;
        }
    }
    return false;
}

//function to display the users play history
void DisplayHistory(vector<string> userHis){
    cout << "All attempted entries\n";
    for (string numbers : userHis){
        cout << numbers << " ";
    }
}
void MainMenu() {
    int choice;
    int userDiffChoice;
    bool play = true;
    cout << endl << endl;
    cout << "--------------------------- Welcome to Guess The Number ---------------------------\n";
    cout << endl;
    cout << "\t\t\t----------- Instructions -----------\n";
    cout << "\t\tAttempt to guess the correct number generated by the CPU!\n" << endl;
    cout << "\t\t\t----------- How to play -----------\n";
    cout << "\t\t1: Enter a number within the specified range\n\t\t2: Try to guess the correct number in 3 attempts\n";
    cout << endl;

    //while loop to have player end game
    while (play){
        cout << "Enter 1 to play the game or 2 to end game: ";
        cin >> choice;

        if (cin) {

            switch (choice)
            {
            case 1:
                cout << endl;
                userDiffChoice = Difficulties();
                PlayGame(userDiffChoice);
                break;
            case 2:
                play = false;
                break;
            default:
                cout << "Enter a valid choice\n";
            }
        } else {
            cout << "Please enter a numerical value\n";
            ClearBuffer();
            cout << endl;
        }
    }
}

void ClearBuffer(){
    cin.clear();
    cin.ignore(1000, '\n');
}


int main(){
    MainMenu();
    return 0;
}