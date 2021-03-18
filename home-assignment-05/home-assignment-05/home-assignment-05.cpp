#include <iostream>

#include <thread>

#include <mutex>

#include <condition_variable>

#include <functional>







using namespace std;



condition_variable cv1;

condition_variable cv2;

condition_variable cv3;

condition_variable cv4;

condition_variable cv5;



mutex m_mutex;

class Application

{

public:

	Application() {



	}



	void timeWaster() {

		for (int j = 0; j < 5; j++) {

			for (long long i = 0; i < 1000000000; i++) {

				long long pom = i;

			}

			switch (j)

			{

			case 0:

				cv1.notify_one();

			case 1:

				cv2.notify_one();

			case 2:

				cv3.notify_one();

			case 3:

				cv4.notify_one();

			case 4:

				cv5.notify_one();

			}





		}

	}



private:



};







int main()

{

	Application app;

	thread thread1(&Application::timeWaster, &app);

	unique_lock<mutex> mlock(m_mutex);



	cv1.wait(mlock);

	cout << "20% \n";



	cv2.wait(mlock);

	cout << "40% \n";



	cv3.wait(mlock);

	cout << "60% \n";



	cv4.wait(mlock);

	cout << "80% \n";





	cv5.wait(mlock);

	cout << "100% \n";

	thread1.join();









}