#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <string>
#include <Windows.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;

	CascadeClassifier haar_cascade;
	haar_cascade.load("C:/opencv/data/haarcascades/haarcascade_frontalface_alt.xml");
		
	Mat frame;
	int picN = 0, i = 0, prePic = 1;
	string picpath = "C:/Users/LenovoS510p/Documents/Semester1_2016/Computer_Engineering_Design3/Face_Recognition/MyfaceBase/S";
	string picdir;
	Mat dst;

	for (;;)
	{
		cap >> frame;
		// Clone the current frame:
		Mat original = frame.clone();
		// Convert the current frame to grayscale:
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);
		// Find the faces in the frame:
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces);
		// At this point you have the position of the faces in
		// faces. Now we'll get the faces, make a prediction and
		// annotate it in the video. Cool or what?
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PXM_BINARY);
		compression_params.push_back(1);

		for (int i = 0; i < faces.size(); i++) {
			// Process face by face:
			Rect face_i = faces[i];
			Mat face = gray(face_i);

			if (picN != prePic) {
				picdir = picpath + to_string(1) + "/" + to_string(picN) + ".pgm";
				resize(face, dst, Size(50, 50), 0, 0, INTER_CUBIC);
				imwrite(picdir, dst, compression_params);
				prePic = picN;
			}

			rectangle(original, face_i, CV_RGB(0, 255, 0), 1);
		}
		// Show the result:
		imshow("face_recognizer", original);
		// And display it:

		if (i == 10){
			i = 0;
			picN++;}

		if (picN == 12) break;
		i++;
		char key = (char)waitKey(20);
		// Exit this loop on escape:
		if (key == 27)
			break;
	}
}