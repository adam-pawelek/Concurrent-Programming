// home-assignment-02.cpp : This file contains the 'main' function. Program execution begins and ends there.

//



#include <iostream>

#include <thread>

#include <random>



using namespace std;



void fillArray(int* data, int sizeOfArray) {





    srand(time(NULL));



    for (int i = 0; i < sizeOfArray; i++) {

        int pom = rand();

        // cout << pom<<" ";

        data[i] = pom;

    }

}





int main()

{

    int* data;

    cout << "how many numbers to allocate ";

    int sizeOfArray;

    cin >> sizeOfArray;

    data = new int[sizeOfArray];

    thread thread1(fillArray, data, sizeOfArray);

    thread1.join();

    for (int i = 0; i < sizeOfArray; i++) {

        cout << data[i] << "\n";

    }

}