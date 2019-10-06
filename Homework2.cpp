//Names: Matthew Jackson, Charlie Staich
//Tic Tac Toe Game
//2 player game, first player to get 3 in a row wins.

#include <iostream>
#include <iostream>
using namespace std;

// Returns true if s is a number else false

class Sort
{
public:
    void displayDocs() {
        cout << endl << "Player 1 (X) -- Player 2 (O)" << endl << endl;
        cout << "    |     |" << endl;
        cout << endl;
    }

    void getUserInput(int arr[]) {
        bool valid = false;
        bool largeList = false;
        int threshold, listSize, listCreation, display;

        // Get user input for threshhold value
        do {
            cout << "Please enter the threshold value.\n" << endl;
            cin >> threshold;
            if (cin.good()) {
                arr[0] = threshold;
                valid = true;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input" << endl;
            }
        } while (!valid);
        valid = false;

        // Get user input for size of the list to sort
        do {
            cout << "Please enter the size of the list to sort.\n" << endl;
            cin >> listSize;
            if (cin.good()) {
                if (listSize > 1 && listSize < 16) {
                    arr[1] = listSize;
                    arr[2] = 0;
                    valid = true;
                } else if (listSize > 15 && listSize < 40) {
                    arr[1] = listSize;
                    arr[2] = 1;
                    valid = true;
                    largeList = true;
                } else {
                    cout << "Invalid input. [2-40]" << endl;
                    valid = false;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. [2-40]" << endl;
            }
        } while (!valid);
        // If list size larger than 15, skip the next two steps.
        if (!largeList) {
          valid = false;
        }

        // Get user input for initialization type
        while (!valid) {
            cout << "Would you like the values in the list to be initialized Manually[1] or Automatically[2]?\n" << endl;
            cin >> listCreation;
            if (cin.good()) {
                if (listCreation == 1 || listCreation == 2) {
                  arr[3] = listCreation;
                  valid = true;
                } else {
                   cout << "Invalid input. [1] or [2]..." << endl;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. [1] or [2]..." << endl;
            }
        }
        // If list size larger than 15, skip the next two steps.
        if (!largeList) {
          valid = false;
        }

        // Get user input for whether or not to display array
        while (!valid) {
            cout << "Would you like to have the array displayed Yes[1] or No[0]?\n" << endl;
            cin >> display;
            if (cin.good()) {
                if (display == 1 || display == 0) {
                  arr[4] = display;
                  valid = true;
                } else {
                   cout << "Invalid input. [1] or [0]..." << endl;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input" << endl;
            }
        }
    }

    bool playAgain() {
        bool play = false;
        bool invalidChoice = true;
        char answer;

        while (invalidChoice == true) {
            cout << "Would you like to play again? [y or n]?\n" << endl;
            cin >> answer;

            if (answer == 'y') {
                invalidChoice = false;
                play = true;
            } else if (answer == 'n') {
                invalidChoice = false;
            } else {
                cout << "Please enter 'y' or 'n'. " << endl;
            }
        }
        return play;
    }

    void displayArray(int arr[], int size) {
        for (int i = 0; i < size; i++) {
            cout << "Value " << i << " is: " << arr[i] << endl;
        }
    }
};

int main() {
    int inputArray[5];
    int threshold, size, largeList, initializationType, display, random;
    srand (time(NULL));
    bool play = true;
    bool valid = false;
    Sort sort;
    sort.displayDocs();
    while (play == true) {
        sort.getUserInput(inputArray);
        threshold = inputArray[0];
        size = inputArray[1];
        int list[size];
        largeList = inputArray[2];
        if (largeList != 1) {
            initializationType = inputArray[3];
            display = inputArray[4];
        }
        if (largeList == 1 || initializationType == 2){
            for (int i = 0; i < size; i++) {
                list[i] = rand() % 20 + 1;
            }
        } else if (initializationType == 1) {
            // Get user input for each list value
            int val;
            for (int i = 0; i < size; i++) {
              do {
                  cout << "Please enter a value for the list. (int)" << endl;
                  cin >> val;
                  if (cin.good()) {
                      list[i] = val;
                      valid = true;
                  } else {
                      cin.clear();
                      cin.ignore(numeric_limits<streamsize>::max(), '\n');
                      cout << "Invalid input" << endl;
                  }
              } while (!valid);
            }
        }
        if (largeList == 1 || display == 1){
            cout << "Unsorted Array..." << endl;
            sort.displayArray(list, size);
        }

        play = sort.playAgain();
    }
    return 0;
}
