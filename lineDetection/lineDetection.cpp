// lineDetection.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Roomba.h"
#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

// PLAN : 
// take image from cam
// make grayscale
// threshold to black and white 
// do canny
// do hough transform

//view logs on linux install: sudo apt-get install ubuntu-restricted-extras
// USER DEFINED FUNCTIONS
Point findNormal(Mat img, Point2f p1, Point2f p2);
void grid(Mat img);
void on_trackbar(int, void*);
string intToString(int number);
void createTrackbars();
void drawObject(vector<Roomba> theRoombas, Mat &frame);
void morphOps(Mat &thresh);
void trackFilteredObject(Mat threshold1, Mat HSV, Mat &cameraFeed);
void trackFilteredObject(Roomba theRoomba, Mat threshold1, Mat HSV, Mat &cameraFeed);

//MULTITRACKING CONSTANTS

//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 40 * 40;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";



float H = 1; // global variable to moniter height
int W = 1000; // width of gui
int gridM = 20; // size of grid in meters
Mat pos = Mat::zeros(W, W, CV_8UC3);
Point2f center = Point2f(640/2, 480/2);
int main()
{
	//establishing matrices and variables
	Mat cameraFeed, imgGray, imgBlack, canny, threshold1, HSV, eroded;
	int counter = 1;
	Point2f POS1;
	Point2f POS2;
	VideoCapture capture;
	capture.open(0);
	int smalldist = 800;
	vector<Vec4i> normalLines;
	Point2f pn;
	Point2f pns, pns2;
	vector<Point> pointListx;
	vector<Point> pointListy;
	float m;
	float mn;
	float rise;
	float run;
	bool align;


	//initialize logging 
	bool logging = false;
	//logging section
	VideoWriter videoSource("out.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(FRAME_WIDTH, FRAME_HEIGHT), true);
	VideoWriter videoProcessed("out2.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, Size(FRAME_WIDTH, FRAME_HEIGHT), true);

	//if we would like to calibrate our filter values, set to true.
	string onOff;
	cout << "calibrtion mode on or off (t/f)" << endl;
	cin >> onOff;
    for (int i=0;i<onOff.length();i++){ // input.length() gets the length of the string
         onOff[i]=tolower(onOff[i]); // convert every character of input to lowercase ( I think there are other methods to do this)
    }
	bool calibrationMode = true;	
	if( onOff != "f" && onOff != "t")
	{
		cout << "incorrect input" << onOff << endl;
		return 1;
	}
	if( onOff == "f")
	{
		calibrationMode = false; 
	}


	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
			
//BEGINS CAMERA LOOP
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
			//all of our operations will be performed within this loop

	while (1)
	{

		capture.read(cameraFeed);
		
		if (!cameraFeed.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			system("pause");
			return -1;
		}

			//if we would like to calibrate our filter values, set to true.
			bool calibrationMode = false;
			//open capture object at location zero (default location for webcam)
			//set height and width of capture frame
			
			//COLOR DETECTION PART
			////\\\\\\\\\\\\\\\\\\\////////////////////////////////////////////////////////////
			//convert frame from BGR to HSV colorspace, writes it to HSV
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			if (calibrationMode == true) {
			//if in calibration mode, we track objects based on the HSV slider values.
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold1);
				morphOps(threshold1);
				imshow(windowName2, threshold1);
				trackFilteredObject(threshold1, HSV, cameraFeed);
				// 103 = g for green
				switch(waitKey(30))
				{
					// g set for green
					case 103:
					{
						ofstream config;
					    config.open ("greenRoomba.txt");
					    config.seekp(0,std::ios::end); //to ensure the put pointer is at the end
						config<<H_MIN<<" "<<S_MIN<<" "<<V_MIN<<"\n"<<H_MAX<<" "<<S_MAX<<" "<<V_MAX;
						cout << "green roomba HSV min vals set to :"<<H_MIN<<" "<<S_MIN<<" "<<V_MIN<<endl;
						cout << "green roomba HSV max vals set to :"<<H_MAX<<" "<<S_MAX<<" "<<V_MAX<<endl;
					    config.close();
					}
					// r set for red
					case 114:
					{
						ofstream config;
					    config.open ("redRoomba.txt");
					    config.seekp(0,std::ios::end); //to ensure the put pointer is at the end
						config<<H_MIN<<" "<<S_MIN<<" "<<V_MIN<<"\n"<<H_MAX<<" "<<S_MAX<<" "<<V_MAX;
						cout << "red roomba HSV min vals set to :"<<H_MIN<<" "<<S_MIN<<" "<<V_MIN<<endl;
						cout << "red roomba HSV max vals set to :"<<H_MAX<<" "<<S_MAX<<" "<<V_MAX<<endl;
					    config.close();
					}
					// c for continue 
					case 99:
					{
						calibrationMode = false;
					}
					// esc end program 
					case 27:
					{
						return 1;
					}
					default:
						continue;
				}
			}

			if (calibrationMode == true) {
				createTrackbars();
				//if in calibration mode, we track objects based on the HSV slider values.
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold1);
				morphOps(threshold1);
				imshow(windowName2, threshold1);
			
				trackFilteredObject(threshold1, HSV, cameraFeed);
			}
			else {
					
				Roomba green("green roomba"), red("red roomba");
				
				//finds green roombas
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, green.getHSVMin(), green.getHSVMax(), threshold1);
				morphOps(threshold1);
				trackFilteredObject(green, threshold1, HSV, cameraFeed);
				//finds red roombas
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, red.getHSVMin(), red.getHSVMax(), threshold1);
				morphOps(threshold1);
				trackFilteredObject(red, threshold1, HSV, cameraFeed);
				/*
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, cherry.getHSVMin(), cherry.getHSVMax(), threshold);
				morphOps(threshold);
				trackFilteredObject(cherry, threshold, HSV, cameraFeed);
				*/
			}

				//show frames 
				//imshow(windowName2,threshold);


		// LINE DETECTION PART
		/////////\\\\\\\\\\\\\\\\\\\\\\///////////////\\\\\\\\\\\\
		// Binary Threshold -->imgGray
		cvtColor(cameraFeed, imgGray, CV_BGR2GRAY);
		// takes every pixle < 200 and makes it black (0);  >200 is white (1)
		threshold(imgGray, imgBlack, 190, 255, 0);
		int erosion_size = 3;
		//Mat eroded;
		Mat linesDetected = Mat::zeros(cameraFeed.rows, cameraFeed.cols, CV_8UC3);
		//erode(imgBlack, eroded, getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size)));
		Canny(imgBlack, canny, 30, 120, 3);
		vector<Vec4i> lines;
		HoughLinesP(canny, lines, 1, CV_PI / 180, 30, 30, 70);

//		int smalldist = 800;
//		vector<Vec4i> normalLines;
//		Point2f pn;
//		Point2f pns, pns2;
//		vector<Point> pointListx;
//		vector<Point> pointListy;
//		float m;
//		float mn;
//		float rise;
//		float run;
		align = false;
		//unpacks vectors of lines and sorts them into bins
		for (size_t i = 0; i < lines.size(); i++)
		{
			cout << "i= " << i << endl;
			Vec4i l = lines[i];
			line(linesDetected, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
			pn = findNormal(linesDetected, Point2f(l[0], l[1]), Point2f(l[2], l[3]));
			bool mtag = false, mntag = false;
			rise = pn.y - center.y;
			run = (pn.x - center.x);
			
			//if (rise < .001) { mtag = true; }
			if (abs(rise < .001)) { mtag = true; }
			else if ( abs(run < .001)) { mntag = true; }
			// finds what should be the slope of the normal lines 
			if (i == 0 )
			{
				if (mtag == true || mntag == true)
				{
					align = true;
				}
				if (align == false)
				{
					m = rise / run;
					mn = -1 / m;
				}

			}
			// sorts each line into 2 differnt arrays based off the simularity to the line slopes
			if (align == true)
			{
				if (mtag) {
					pointListx.push_back(pn);
					cout << "point group 1" << pn << endl;
				}
				else if (mntag) {
					cout << "point group 2" << pn << endl;
					pointListy.push_back(pn);
				}
			}
			if (align == false)
			{
				if (abs(((rise / run) - m) / m) < .05)
				{
					cout << "point group 1" << pn << endl;
					pointListx.push_back(pn);
				}
				if (abs(((rise / run) - mn) / mn) < .05)
				{
					cout << "point group 2" << pn << endl;
					pointListy.push_back(pn);
				}

			}
		}
		
		//find and draw normal lines 
		for (int i = 0; i < pointListx.size(); i++)
		{
			Point2f pTemp = pointListx[i];
			if (norm(center - pTemp) < smalldist)
			{
				pns = pTemp;
				smalldist = norm(center - pTemp);
			}
		}
		POS1.x = smalldist;
		line(linesDetected, center, pns, Scalar(0, 255, 255));
		smalldist = 800;
		for (int i = 0; i < pointListy.size(); i++)
		{
			Point2f pTemp = pointListy[i];
			if (norm(center - pTemp) < smalldist)
			{
				pns = pTemp;
				smalldist = norm(center - pTemp);
			}
		}
		POS1.y = smalldist;
		line(linesDetected, center, pns, Scalar(0, 255, 255));
		//putText(pos, to_string(center.x) + " " + to_string(center.y), center * (W / gridM) + Point2f(15, 15), 1, 1, Scalar(255, 0, 0));

		//OUTPUT
		cout << POS1 << endl;
		circle(linesDetected, center, 5, Scalar(255, 0, 0), -1);
		grid(pos);
		circle(pos, POS1 *(W/gridM)*.0011, 10, Scalar(255, 0, 0), -1);
		imshow("source", cameraFeed);
		imshow("black and white", imgBlack);
		imshow("canny", canny);
		imshow("detected Lines", linesDetected);
		imshow("position", pos);
		imshow(windowName, cameraFeed);
		//imshow(windowName1,HSV);


		counter++;

		//LOGGING
		if(logging == true)
		{
			videoSource.write(cameraFeed);
			videoProcessed.write(linesDetected);
		}
		
		//waitKey(30);

	}
    return 0;
}


Point findNormal(Mat img, Point2f p1, Point2f p2)
{
	// find normal lines 
	float x = 0;
	float y = 0;

	float ml = (p2.y - p1.y) / (p2.x - p1.x);
	float mn = -1 / ml;

	x = (-p1.y + center.y + ml*p1.x - mn*center.x) / (ml - mn);
	y = ml*(x - p1.x) + p1.y;
	if (p2.x - p1.x == 0)
	{
		y = center.y;
		x = p1.x;
	}
	if (ml == 0)
	{
		x = center.x;
		y = p1.y;
	}

	Point2f pn = Point2f(x, y);
	return pn;
}

void grid(Mat img)
{
	img = Mat::zeros(W, W, CV_8UC3);
	int pixPM = W / gridM;
	for (int i = 1; i < gridM; i++)
	{
		line(img, Point(1, i*(W / gridM)), Point(W, i*(W / gridM)), Scalar(0, 255, 255), 2, 8);
		line(img, Point(i*(W / gridM), 1), Point(i*(W / gridM), W), Scalar(0, 255, 255), 2, 8);
	}


}



//MULTI_TRACKING FUNCTIONS 

//Written by  Kyle Hounslow 2013

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//IN THE SOFTWARE.



void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed





}
string intToString(int number) {


	std::stringstream ss;
	ss << number;
	return ss.str();
}
void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	
	//char TrackbarName[50];
	// sprintf(TrackbarName, "H_MIN", H_MIN);
	// sprintf(TrackbarName, "H_MAX", H_MAX);
	// sprintf(TrackbarName, "S_MIN", S_MIN);
	// sprintf(TrackbarName, "S_MAX", S_MAX);
	// sprintf(TrackbarName, "V_MIN", V_MIN);
	// sprintf(TrackbarName, "V_MAX", V_MAX);

	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);


}
void drawObject(vector<Roomba> theRoombas, Mat &frame) {
	
	for (int i = 0; i < theRoombas.size(); i++)
	{
		cv::circle(frame, cv::Point(theRoombas.at(i).getXPos(), theRoombas.at(i).getYPos()), 10, cv::Scalar(0, 0, 255));
		cv::putText(frame, intToString(theRoombas.at(i).getXPos()) + " , " + intToString(theRoombas.at(i).getYPos()), cv::Point(theRoombas.at(i).getXPos(), theRoombas.at(i).getYPos() + 20), 1, 1, Scalar(0, 255, 0));
		cv::putText(frame, theRoombas.at(i).getType(), cv::Point(theRoombas.at(i).getXPos(), theRoombas.at(i).getYPos() - 30), 1, 2, theRoombas.at(i).getColor());
		circle(pos, cv::Point(theRoombas.at(i).getXPos(), theRoombas.at(i).getYPos()) *(W/gridM)*.0011, 10, Scalar(255, 255, 0), -1);
	}
}
void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);



}
void trackFilteredObject(Mat threshold1, Mat HSV, Mat &cameraFeed) {

	//vector<Fruit> apples;
	vector<Roomba> roombas;


	Mat temp;
	threshold1.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area>MIN_OBJECT_AREA) {
					//Fruit apple;
					Roomba green;
					green.setXPos(moment.m10 / area);
					green.setYPos(moment.m01 / area);

					//apples.push_back(apple);
					roombas.push_back(green);

					objectFound = true;

				}
				else objectFound = false;


			}
			//let user know you found an object
			if (objectFound == true) {
				//draw object location on screen
				drawObject(roombas, cameraFeed);
			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}
void trackFilteredObject(Roomba theRoomba, Mat threshold1, Mat HSV, Mat &cameraFeed) {

	vector<Roomba> roombas;


	Mat temp;
	threshold1.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area>MIN_OBJECT_AREA) {
					Roomba green;
					green.setXPos(moment.m10 / area);
					green.setYPos(moment.m01 / area);
					green.setType(theRoomba.getType());
					green.setColor(theRoomba.getColor());
					roombas.push_back(green);


					objectFound = true;

				}
				else objectFound = false;


			}
			//let user know you found an object
			if (objectFound == true) {
				//draw object location on screen
				drawObject(roombas, cameraFeed);
			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}


