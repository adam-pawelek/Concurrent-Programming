#include <iostream>
#include <thread>
#include<mutex>
#include <time.h>
#include <chrono>
#include <vector>
#include <utility>
#include <future>
using namespace std;


int connect1 = 0;

/*
If you would like to test stop function you can remove comment in program function

*/


class Sensor {
public:
	
	Sensor(int &toSensor, vector<thread>& vec,mutex &mut,bool &readd, promise<int> &pr, int &stopSensor) {
		thread thread1(&Sensor::internallyThread, this, ref(toSensor),ref(mut), ref(readd),ref(pr),ref(stopSensor));
		vec.push_back(std::move(thread1));

		cout << " \n Czy to sie towrzy \n";
		
	}
	


	void internallyThread(int &connect1,mutex &mut, bool &readd,promise <int> &pr,int &stopSensor) {

		srand(time(NULL));
		while (stopSensor == 0)
		{
			mut.lock();
			if (readd == true) {
				
				connect1 = measurement();
				if (connect1 > 4000) {

					pr.set_value(connect1);

				}
				readd = false;
			}
			mut.unlock();

		}
	}
	int measurement() {
		
		return ((rand() % 4096));

	}


};






int xxx = 0;

class SensorReader
{
public:

	int stopSensor = 0;

	SensorReader(vector<thread>& vec) {
		thread mainThread(&SensorReader::program, this);
		vec.push_back(std::move(mainThread));
		for (int i = 0; i < 4; i++) {
			fut[i] = pr[i].get_future();
		}


		for (int i = 0; i < 4; i++) {
			this->read[i] = true;
		}
		for (int i = 0; i < 4; i++) {
			this->sens[i] = new Sensor(toSensor[i], vec, mutex[i], read[i],pr[i],stopSensor);
		}



	};



private:

	void program() {

		cout << "w programie"<<"\n";
		int countMe = 0;
		while (stopSensor == 0)
		{
			for (int i = 0; i < 4; i++) {
				mutex[i].lock();
				if (read[i] == false) {

					if (fut[i]._Is_ready())

					{
						cout << i << ": " << fut[i].get() << endl;
						pr[i] = std::promise<int>();
						fut[i] = pr[i].get_future();
					}
					read[i] = true;

				}
				mutex[i].unlock();
			}
			/*
			if (countMe > 1000 ) {
					stop();
			}
			countMe++;
			*/
		}
	}


	void stop() {
		stopSensor = 1;
	}




	int toSensor[4];

	bool read[4];

	mutex mutex[4];
	Sensor *sens[4];
	promise<int> pr[4];
	shared_future<int>fut[4];



};






int main()
{
	
	int n = 1;

	vector<thread> vec;
	mutex mut;
	bool cos = true;

	SensorReader alal(vec);
	
	int ale;

	
	for (int i = 0; i < vec.size(); i++) {
		vec[i].join();
	}
	

}

