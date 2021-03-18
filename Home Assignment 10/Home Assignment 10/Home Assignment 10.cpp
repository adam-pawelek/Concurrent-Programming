#include <iostream>

#include <chrono>

#include<thread>



using namespace std;



struct Pixel

{

    float red;

    float green;

    float blue;

};





void addPixelColors(const Pixel* image1, const Pixel* image2, Pixel* result, int imageSize)

{

    for (int i = 0; i < imageSize; i++)

    {

        result[i].red = image1[i].red + image2[i].red;

        if (result[i].red > 1.0f)

        {

            result[i].red = 1.0f;

        }



        result[i].green = image1[i].green + image2[i].green;

        if (result[i].green > 1.0f)

        {

            result[i].green = 1.0f;

        }



        result[i].blue = image1[i].blue + image2[i].blue;

        if (result[i].blue > 1.0f)

        {

            result[i].blue = 1.0f;

        }

    }

}















void createPixels(Pixel * image,int imageSize)

{

    //Pixel* image = new Pixel[imageSize];

    for (int i = 0; i < imageSize; i++)

    {

        image[i].red = (float(rand()) / float((RAND_MAX)));

        image[i].green = (float(rand()) / float((RAND_MAX)));

        image[i].blue = (float(rand()) / float((RAND_MAX)));

    }

    //return image;

}





Pixel* createPixelsOld(int imageSize)

{

    Pixel* image = new Pixel[imageSize];

    for (int i = 0; i < imageSize; i++)

    {

        image[i].red = (float(rand()) / float((RAND_MAX)));

        image[i].green = (float(rand()) / float((RAND_MAX)));

        image[i].blue = (float(rand()) / float((RAND_MAX)));

    }

    return image;

}









int fun1() {

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();



    constexpr int imageSize = 4096 * 4096;

    Pixel* image1 = new Pixel[imageSize]; // = createPixels(imageSize);

    Pixel* image2 = new Pixel[imageSize];; // = createPixels(imageSize);

    thread t1(createPixels, ref(image1), imageSize);

    thread t2(createPixels, ref(image2), imageSize);

    Pixel* result = new Pixel[imageSize];

    t1.join();

    t2.join();



    addPixelColors(image1, image2, result, imageSize);



    chrono::steady_clock::time_point end = chrono::steady_clock::now();



    cout << "Execution time parallel: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

    int time1 = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    delete[] result;

    delete[] image2;

    delete[] image1;

    return time1;

}







int fun2() {

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();



    constexpr int imageSize = 4096 * 4096;

    Pixel* image1 = createPixelsOld(imageSize);

    Pixel* image2 = createPixelsOld(imageSize);

    Pixel* result = new Pixel[imageSize];



    addPixelColors(image1, image2, result, imageSize);



    chrono::steady_clock::time_point end = chrono::steady_clock::now();



    cout << "Execution time sequential: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

    int time2 = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    delete[] result;

    delete[] image2;

    delete[] image1;

    return time2;



}



int main()

{

    int time1, time2;

    time1 = fun1();

    time2 = fun2();





    cout << "Time difference " << time2 - time1 << "[ms]" << endl;









}

