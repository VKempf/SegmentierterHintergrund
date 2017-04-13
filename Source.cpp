#include "opencv2/opencv.hpp"
#include<iostream>

using namespace cv;
using namespace std;

Mat frame;
Mat mask;
Mat dest;


int const max_value = 255*3;
int thresholdn = 120;

const char* trackbar_value = "Value";


int main(int, char**)
{
	VideoCapture cap(0); 
	if (!cap.isOpened())  
		return -1;
	
	
	namedWindow("Orginal", 1);
	namedWindow("Mask", 1);
	namedWindow("dest", 1);

	

	cap >> dest;
	
	for (;;)
	{
		
		cap >> frame; 
		

		//zufälligen Hintrgrund erstellen 
		for (int x = 0; x < dest.rows; x++) {
			for (int y = 0; y < dest.cols; y++) {
					
					dest.at<Vec3b>(x, y) = Vec3b(rand() % 255, rand() % 255, rand() % 255);
			
			}
		}
		
		//orgianlBild in Graustufen umwandeln
		cvtColor(frame, mask, CV_BGR2GRAY);
		//aus Graustufen binäre Maske erstellen
		threshold(mask, mask, 80, 255, THRESH_BINARY);

		//Maske anwenden um orginalBild auf den Hintergrund zu kopieren
		frame.copyTo(dest, mask);
		

		imshow("Orginal", frame);
		imshow("Mask", mask);
		imshow("dest", dest);
		waitKey(20);
	}
	

	return 0;
}
