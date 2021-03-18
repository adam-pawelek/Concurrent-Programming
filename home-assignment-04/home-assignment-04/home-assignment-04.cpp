// home-assignment-04.cpp : This file contains the 'main' function. Program execution begins and ends there.

//



#include <iostream>

#include <thread>

#include <mutex>

#include <time.h>

#include <random>







using namespace std;





mutex lockOpperation;





class Application

{

public:



	mutex lockMoney;

	int amountOfMoney;

	Application(int amountOfMoney) {

		this->amountOfMoney = amountOfMoney;



	}



	int balance() { // ile pieniêdzy

		lockMoney.lock();

		int helpp = amountOfMoney;

		lockMoney.unlock();

		return helpp;



	}



	void deposit(int quantity) {  //wp³aty

		lockMoney.lock();

		amountOfMoney = amountOfMoney + quantity;

		lockMoney.unlock();

	}



	void withdraw(int quantity) { // wyp³aty

		lockMoney.lock();

		amountOfMoney = amountOfMoney - quantity;

		lockMoney.unlock();

	}





private:



};





void depositThread1(Application& app1, Application& app2) {

	srand(time(NULL));

	for (int i = 0; i < 10000000; i++)

	{

		int quantity = (rand() % 10);

		int tellWhich = (rand() % 2);

		if (tellWhich == 0) {

			lockOpperation.lock();

			if (app2.balance() - quantity > 0) {



				app1.deposit(quantity);

				app2.withdraw(quantity);

			}

			lockOpperation.unlock();

		}

		else

		{

			lockOpperation.lock();

			if (app1.balance() - quantity > 0) {

				app2.deposit(quantity);

				app1.withdraw(quantity);

			}

			lockOpperation.unlock();

		}





	}



}















int main()

{

	Application app1(1000000);

	Application app2(1000000);



	thread thread1(depositThread1, ref(app1), ref(app2));

	thread thread2(depositThread1, ref(app1), ref(app2));

	thread thread3(depositThread1, ref(app1), ref(app2));

	thread thread4(depositThread1, ref(app1), ref(app2));





	thread1.join();

	thread2.join();

	thread3.join();

	thread4.join();



	cout << app1.balance() << "\n";

	cout << app2.balance() << "\n";



}

