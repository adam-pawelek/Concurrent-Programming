
/*
https://gitlab.labranet.jamk.fi/AA4917/concurrent-programming/-/tree/master/home-assignment-06
In folder Screenshots I have some test that show results 
with the comparison of the results from Excel
*/


#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <random>
#include <atomic>
#include <iomanip>


using namespace std;



atomic <int> countAcctions{ 0 };
atomic <int> countMe{ 0 };

atomic <int> countIn{ 0 };

class Application
{
public:

	int myAccuracy = 10000000;
	atomic <long long> amountOfMoney;
	Application(long long amountOfMoney) {
		this->amountOfMoney.store(amountOfMoney * myAccuracy);

	}

	long double balance() { // ile pieniêdzy
		
		long long currentBalance = amountOfMoney.load();
		long long pom = (currentBalance / myAccuracy);
		long double myRest = (long double)(currentBalance % myAccuracy)/ myAccuracy;
		long double myResult = (long double)(pom + myRest);
		return (myResult);

	}

	void deposit(int quantity) {  //wp³aty
		
		amountOfMoney += quantity * myAccuracy;
		
	}

	void withdraw(int quantity) { // wyp³aty
		
		amountOfMoney -= quantity * myAccuracy;
		
	}
	void addInterest () {
		long long storeData = amountOfMoney;
		//cout << storeData  << "\n";
		amountOfMoney.store(storeData + storeData * 0.0005);
	}


private:

};


void depositThread1(Application& app1, Application& app2) {
	
	srand(time(NULL));
	int storeHundred = 100;
	for (int i = 0; i < 1000;  i++)
	{

		do {
			long long quantity = (rand() % 10);
			long long tellWhich = (rand() % 2);
			storeHundred = 100;
			int wloz = countMe.load();
			if (wloz < 100) {
				/*
				if (tellWhich == 0 && app2.balance() < 0) {
					tellWhich = 1;
				}
				if (tellWhich == 1 && app1.balance() < 0) {
					tellWhich = 0;
				}
				*/
				countIn += 1;
				if (countMe.compare_exchange_strong(wloz, wloz + 1)) {
					
					
						if (tellWhich == 0) {



							app1.deposit(quantity);
							app2.withdraw(quantity);


						}
						else
						{


							app2.deposit(quantity);
							app1.withdraw(quantity);


						}
						countAcctions += 1;

					
				}
				countIn -= 1;
			}
			storeHundred = 100;
		} while (!countMe.compare_exchange_strong(storeHundred, 200));
		/*
		for (int i = 0; i < 10000; i++) {

		}
		*/
		while (countIn.load() > 0) {}
		app1.addInterest();
		app2.addInterest();
		//cout << setprecision(5) << fixed << (app1.balance() + app2.balance()) <<"\n";
		countMe.store(0);
		


	}

}







int main()
{
	setprecision(5);
	Application app1(100);
	Application app2(100);

	thread thread1(depositThread1, ref(app1), ref(app2));
	thread thread2(depositThread1, ref(app1), ref(app2));
	thread thread3(depositThread1, ref(app1), ref(app2));
	thread thread4(depositThread1, ref(app1), ref(app2));


	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	cout << "Current bank account balance"<<"\n";
	cout << setprecision(7) << fixed << app1.balance() << "\n";
	cout << setprecision(7) << fixed <<app2.balance() << "\n";

	cout << setprecision(7) << fixed << app2.balance() + app1.balance() << "\n";


	cout << "How many operations 1 Bank account did "<< countAcctions.load();

}

