#include <iostream>

#include <thread>

#include <mutex>

#include <vector>

#include <random>

using namespace std;



mutex m;

int quantity = 0;

vector <int> dataa;

vector<int>::iterator it;

void addNumber() {

	srand(time(NULL));

	for (int i = 0; i < 1000000; i++)

	{

		m.lock();

		if (quantity > 100) {

			m.unlock();

		}

		else {

			quantity++;

			dataa.push_back(rand());

			m.unlock();

		}





	}

}



void removeNumber() {

	for (int i = 0; i < 10000000; i++)

	{

		m.lock();

		if (quantity <= 5) {

			m.unlock();

		}

		else {

			it = dataa.begin();

			dataa.erase(it);

			quantity = quantity - 1;

			m.unlock();



		}

	}

}







int main()

{

	thread thread2(removeNumber);

	thread thread1(addNumber);







	thread1.join();

	thread2.join();



	for (int i = 0; i < quantity; i++) {

		cout << dataa[i] << "\n";

	}

	cout << "quantity " << quantity;



}

