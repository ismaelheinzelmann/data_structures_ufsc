#include <iostream>
using namespace std;
//easy way to find the name of the 
int sum1(int a, int b) {
    return a + b;
}

//uses the adresses of the variables as input
int sum2(int* a, int* b) {
    return *a + *b;
}

//pass the variables by reference
int sum3(int &a, int &b) {
    return a + b;
}

int* arrayOfInts(int N, int count){

    int* array = new int[N];
    for (int i = 0; i < N; i++) {
        array[i] = i + count * 100;
    }
    return array;
}

int main() {
    //pointer pointing to an variable test of type float
    float* test;

    //variable of type float with value 10.5
    float value = 10.5;

    //assigning the address of variable value to test
    test = &value;

    //*test shows the value at the address of test
    cout << *test;
    cout << "\n";

    //shows the address of value, which is stored in test
    cout << test;
    cout << "\n";

    int a = 10;
    int b = 25;

    cout << sum1(a, b);
    cout << "\n";
    cout << sum2(&a, &b);
    cout << "\n";
    cout << sum3(a, b);
    cout << "\n"; 

    //declare a pointer to an pointer of type int
    int **array;

    //allocate memory for 100 pointers of type int
    array = new int*[100];

    //create 100 arrays of 100 ints and assign them to the array
    for (int i = 0; i < 100; i++)
    {
        array[i] = arrayOfInts(100, i);
    }
    
    //print the array of pointers
    for (int i = 0; i < 100; i++)
    {
        //get the pointer at the current index
        int* temp = array[i];
        for(int j = 0; j < 100; j++){
            cout << temp[j] << " ";
        }
        cout << "\n";
    }

    //free the memory
    for (int i = 0; i < 100; i++)
    {
        delete[] array[i];
    }
    delete [] array;

    return 0;
}


