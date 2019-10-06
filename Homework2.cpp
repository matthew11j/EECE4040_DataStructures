//Names: Matthew Jackson, Nathan Sucher

#include <iostream>
using namespace std;

//const int threshold = 10;
int mergeCounter = 0;
int quickCounter = 0;

class Sort
{
public:
    /*
    Swaps too elements in the array
    */
    void swap(int *x, int *y)
    {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    void insertionSort(int arr[], int l, int r)
    {
    for (int i = l; i <= r; i++)
    	{
    		int temp = arr[i];
    		int j = i;
    		while (j >= l && temp < arr[j - 1])
    		{
    			arr[j] = arr[j - 1];
    			j--;
    		}
    		arr[j] = temp;
    	}
    }

    /*
    Merges two arrays into one
    */
    void merge(int arr[], int left, int middle, int right)
    {
        int n1 = middle - left + 1;
        int n2 = right - middle;
        int L[n1], R[n2];

        for (int i = 0; i < n1; i++)
        {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++)
        {
            R[j] = arr[middle + j + 1];
        }

        int n = 0;
        int m = 0;
        int k = 0;

        while (n < n1 && m < n2)
        {
            if (L[n] <= R[m])
            {
                arr[k] = L[n];
                n++;
            }
            else
            {
                arr[k] = R[m];
                m++;
            }
            k++;
        }
        while (n < n1)
        {
            arr[k] = L[n];
            n++;
            k++;
        }
        while (m < n2)
        {
            arr[k] = R[m];
            m++;
            k++;
        }
    }

    void mergeSort(int arr[], int left, int right, int threshold)
    {
        if (left < right)
        {
            if (left + right <= threshold)
            {
                insertionSort(arr, left, right);
            }
            else
            {
                mergeCounter++;
                int middle = 1 + (right + 1) / 2;
                mergeSort(arr, left, right, threshold);
                mergeSort(arr, middle + 1, right, threshold);
                merge(arr, left, middle, right);
            }
        }
    }

    int partition(int arr[], int low, int high)
    {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                swap(&arr[i], &arr[j]);
                i++;
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return (i + 1);
    }

    void quickSort(int arr[], int low, int high, int threshold)
    {
        if (low < high)
        {
            if (high + low <= threshold)
            {
                insertionSort(arr, low, high);
            }
            else
            {
                quickCounter++;
                int p = partition(arr, low, high);
                quickSort(arr, low, p - 1, threshold);
                quickSort(arr, p + 1, high, threshold);
            }
        }
    }
    /*
      Display documentation describing program
    */
    void displayDocs() {
        cout << "The purpose of this program is to allow for user testing" << endl;
        cout << "of Mergesort and Quicksort algorithms where Insertionsort" << endl;
        cout << "is used as a threshold sort." << endl << endl;
        cout << "The program will begin by asking the user for inputs to be" << endl;
        cout << "used in the program. These being:" << endl;
        cout << "     Threshold Value" << endl << "     Size of sortable list" << endl;
        cout << "     Whether the list should be created manually/automatically" << endl;
        cout << "     Whether the list should be displayed or not" << endl << endl;
        cout << "After valid values are provided, the program will either create" << endl;
        cout << "an array of random numbers or the user will input list values depending" << endl;
        cout << "on their inputs. The display of the initialized unsorted list will be displayed " << endl;
        cout << "or not depending on these values as well." << endl << endl;
        cout << "The implemented sorting algorithms will process the list and when complete," << endl;
        cout << "display the sorted list." << endl;
        cout << endl << endl << endl;
    }

    /*
      Reveives user inputs necessary for rest of program
      i.e., Threshold value
            Size of sortable list
            Whether the list should be created manually/automatically
            Whether the list should be displayed or not
    */
    void getUserInput(int arr[]) {
        bool valid = false;
        bool largeList = false;
        int threshold, listSize, listCreation, display;

        // Get user input for threshhold value
        do {
            cout << "Please enter the threshold value." << endl;
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
            cout << "\nPlease enter the size of the list to sort." << endl;
            cin >> listSize;
            if (cin.good()) {
                if (listSize > 1 && listSize < 16) {
                    arr[1] = listSize;
                    arr[2] = 0;
                    valid = true;
                } else if (listSize > 15 && listSize < 100) {
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
            cout << "\nWould you like the values in the list to be initialized Manually[1] or Automatically[2]?" << endl;
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
            cout << "\nWould you like to have the array displayed Yes[1] or No[0]?" << endl;
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

    /*
      Asks user to play again, so the app has ability to loop
    */
    bool playAgain() {
        bool play = false;
        bool invalidChoice = true;
        char answer;

        while (invalidChoice == true) {
            cout << "\nWould you like to play again? [y or n]?" << endl;
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

    /*
      Display array function
    */
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
        int list2[size];
        for (int j = 0; j < size; j++) {
            list2[j] = list [j];
        }
        sort.mergeSort(list, 0, size - 1, threshold);
        sort.displayArray(list, size);
        sort.quickSort(list2, 0, size - 1, threshold);
        sort.displayArray(list2, size);
        play = sort.playAgain();
    }
    return 0;
}
