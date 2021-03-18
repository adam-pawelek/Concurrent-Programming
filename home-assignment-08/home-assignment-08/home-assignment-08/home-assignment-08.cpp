// home-assignment-08.cpp : This file contains the 'main' function. Program execution begins and ends there.

//


/*
Source - > https://en.cppreference.com/w/cpp/thread/launch

launch::async	a new thread is launched to execute the task asynchronously

launch::deferred	the task is executed on the calling thread the first time its result is requested (lazy evaluation)

 My answer: 
In second function small task are running in deferred and big tasks in async. In first function all tasks are running in async.
Second function is faster because create and run new thread takes more time than running small tasks sequentially.



*/





#include <iostream>
#include <string>
#include <chrono>
#include <time.h>

#include <future>




using namespace std;
using namespace std::chrono;





int tab[100];


class Application

{

public:

	int typeOfTask; // 0 light 1 heavy



	int numberOpperations;

	Application(){//int typeOfTask) {
	

	}

	void helpSet(int number) {
		
		this->typeOfTask = number % 2;
	//	cout << typeOfTask << "\n";

		if (typeOfTask == 0) {
			this->numberOpperations = 100;
		}
		else
		{
			this->numberOpperations = 10000000;
		}
	}

	int generate() {

		srand(time(NULL));
		for (int i = 0; i < this->numberOpperations; i++) {
			int pom = rand();
		}
		return 0;
	}




};











int  fun1() {
	Application ArrayofApp[100];
	future<int> MyArray[100];

	Application app2;

	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		ArrayofApp[i].helpSet(tab[i]);
	}




	//auto f = std::async(&Application::generate, &app2,100);
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	for (int i = 0; i < 100; i++) {

			MyArray[i] = async(launch::async, &Application::generate, &ArrayofApp[i]);
		
	}


	for (int i = 0; i < 100; i++) {
		int helpStore = MyArray[i].get();
	}

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout << "Execution time fun1: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

	return chrono::duration_cast<chrono::milliseconds>(end - begin).count();


}

int fun2() {
	Application ArrayofApp[100];
	future<int> MyArray[100];

	Application app2;



	
	for (int i = 0; i < 100; i++) {
		ArrayofApp[i].helpSet(tab[i]);
	}



	//auto f = std::async(&Application::generate, &app2,100);
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	for (int i = 0; i < 100; i++) {

		if (ArrayofApp[i].typeOfTask == 0) {
			MyArray[i] = async(launch::deferred, &Application::generate, &ArrayofApp[i]);
		}
		else {
			MyArray[i] = async(launch::async, &Application::generate, &ArrayofApp[i]);
		}
	}

	for (int i = 0; i < 100; i++) {
		int helpStore = MyArray[i].get();
	}

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout << "Execution time fun2: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;
	return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
}








int main()

{
	
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		tab[i] = rand();
	}


	int time1 = fun1();
	int time2 = fun2();


	cout << "Execution time difference " << time1 - time2<< "[ms]" << endl;

}

