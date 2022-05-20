#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include "Utilities.h"
//for the clear console command
#include <cstdlib>
//#include "opencv2/video.hpp"
// for measuring speed of execution
#include <time.h>


using namespace std;
using namespace cv;

void vegetalDetect(Mat rawFrame, Mat& resultFrame)
{
	for (int row = 0; row < resultFrame.rows; row++)
	{
		uchar* value = rawFrame.ptr<uchar>(row);
		uchar* check = rawFrame.ptr<uchar>(row);
		uchar* result_value = resultFrame.ptr<uchar>(row);
		for (int column = 0; column < resultFrame.cols; column++)
		{
			//*result_value++;
			//*value++;
			bool isGreen = false;
			// dominant green condition
			if (*(check + 1) > *check && *(check + 1) > *(check + 2))
			//if (rawFrame.at<Vec3b>(row, column)[1] > rawFrame.at<Vec3b>(row, column)[0] && rawFrame.at<Vec3b>(row, column)[1] > rawFrame.at<Vec3b>(row, column)[2])
				isGreen = true;
			// too bright (white clouds) condition
			if (*(check + 1) + *check + *(check + 2) > 550)
			//if (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[0] + rawFrame.at<Vec3b>(row, column)[2] > 550)
				isGreen = false;
			*check++; *check++; *check++;
			if (isGreen == true)
					{
						//B
						*result_value++ = 0; 
						*value++;
						//*result_value++ = rawFrame.at<Vec3b>(row, column)[1];
						//G
						*result_value++ = *value++;
						//R
						*result_value++ = 0;
						*value++;
						//resultFrame.at<Vec3b>(row, column)[0] = 0;
						//resultFrame.at<Vec3b>(row, column)[1] = rawFrame.at<Vec3b>(row, column)[1];
						//resultFrame.at<Vec3b>(row, column)[2] = 0;
					}
			else//not vegetal, set to black
					{
						*result_value++ = 0; 
						*value++;
						*result_value++ = 0; 
						*value++;
						*result_value++ = 0;
						*value++;
						/*resultFrame.at<Vec3b>(row, column)[0] = 0;
						resultFrame.at<Vec3b>(row, column)[1] = 0;
						resultFrame.at<Vec3b>(row, column)[2] = 0;*/
					}
		}
	}
}


void greenYellowDiff(Mat greenFrame, Mat yellowFrame, Mat& resultFrame)
{
	for (int row = 0; row < resultFrame.rows; row++)
	{
		uchar* value = yellowFrame.ptr<uchar>(row);
		uchar* check = greenFrame.ptr<uchar>(row);
		uchar* result_value = resultFrame.ptr<uchar>(row);
		for (int column = 0; column < resultFrame.cols; column++)
		{
			if (*(check+1) == 0)//greenFrame.at<Vec3b>(row, column)[1] == 0)
			{
				/*resultFrame.at<Vec3b>(y, x)[0] = 0;
				resultFrame.at<Vec3b>(y, x)[1] = 0;
				resultFrame.at<Vec3b>(y, x)[2] = 0;*/
				*result_value++; 
				*value++;
				*result_value++;
				*value++;
				*result_value++;
				*value++;
				*check++; *check++; *check++;
			}
			else
			{
				
				*result_value++ = *value++;
				*result_value++ = *value++;
				*result_value++ = *value++;
				*check++; *check++; *check++;
				//*result_value++ = yellowFrame.at<Vec3b>(row, column)[0];
				//*result_value++ = yellowFrame.at<Vec3b>(row, column)[1];
				//*result_value++ = yellowFrame.at<Vec3b>(row, column)[2];
				/*resultFrame.at<Vec3b>(row, column)[0] = yellowFrame.at<Vec3b>(row, column)[0];
				resultFrame.at<Vec3b>(row, column)[1] = yellowFrame.at<Vec3b>(row, column)[1];
				resultFrame.at<Vec3b>(row, column)[2] = yellowFrame.at<Vec3b>(row, column)[2];*/
			}
		}
	}
}

//those are threshold values for green, yellow, and red areas in the dryness image.
int minT = 140;
int maxT = 170;
void dryDetect(Mat& rawFrame, Mat& resultFrame, int blur_value)
{
	blur(rawFrame, rawFrame, Size(blur_value, blur_value));
	for (int row = 0; row < resultFrame.rows; row++)
	{
		uchar* check = rawFrame.ptr<uchar>(row);
		uchar* result_value1 = resultFrame.ptr<uchar>(row);
		uchar* result_value2 = resultFrame.ptr<uchar>(row);
		uchar* result_value3 = resultFrame.ptr<uchar>(row);
		for (int column = 0; column < resultFrame.cols; column++)
		{
			
			*result_value1++ = (*(check + 1) + *(check + 2)) / 2;
			*result_value1++ = (*(check + 1) + *(check + 2)) / 2;
			*result_value1++ = (*(check + 1) + *(check + 2)) / 2;

			/**result_value1++ = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;
			*result_value1++ = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;
			*result_value1++ = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;*/
			//*value++;
			//*value++;
			//*value++;
			/*resultFrame.at<Vec3b>(row, column)[0] = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;
			resultFrame.at<Vec3b>(row, column)[1] = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;
			resultFrame.at<Vec3b>(row, column)[2] = (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[2]) / 2;*/

			if (*(check + 1) + *check + *(check + 2) > 550)
			//if (rawFrame.at<Vec3b>(row, column)[1] + rawFrame.at<Vec3b>(row, column)[0] + rawFrame.at<Vec3b>(row, column)[2] > 550)
			{
				/*resultFrame.at<Vec3b>(row, column)[0] = 0;
				resultFrame.at<Vec3b>(row, column)[1] = 0;
				resultFrame.at<Vec3b>(row, column)[2] = 0;*/
				*result_value2++ = 0;
				*result_value2++ = 0;
				*result_value2++ = 0;
			}
			else
			{
				*result_value2++;
				*result_value2++;
				*result_value2++;
			}
			//those value have been put as a global variable to be alterable by a mouse event
			//int min = 140;
			//int max = 170;
			if (*(check + 1) > maxT)
			//if (rawFrame.at<Vec3b>(row, column)[1] > max)
			{
				*result_value3++ = 0;
				*result_value3++ = 0;
				*result_value3++;
				/*resultFrame.at<Vec3b>(row, column)[0] = 0;
				resultFrame.at<Vec3b>(row, column)[1] = 0;*/
				//resultFrame.at<Vec3b>(y, x)[2] = 255;
			}
			if (*(check + 1) < minT)
			//if (rawFrame.at<Vec3b>(row, column)[1] < min)
			{
				*result_value3++ = 0;
				*result_value3++;
				*result_value3++ = 0;
				////resultFrame.at<Vec3b>(row, column)[0] = 0;
				//resultFrame.at<Vec3b>(y, x)[1] = 255;
				////resultFrame.at<Vec3b>(row, column)[2] = 0;
			}
			if (*(check + 1) >= minT && *(check + 1) <= maxT)
			//if (rawFrame.at<Vec3b>(row, column)[1] >= min && rawFrame.at<Vec3b>(row, column)[1] <= max)
			{
				*result_value3++ = 0;
				*result_value3++;
				*result_value3++;
				////resultFrame.at<Vec3b>(row, column)[0] = 0;
				//resultFrame.at<Vec3b>(y, x)[1] = 255;
				//resultFrame.at<Vec3b>(y, x)[2] = 255;
			}
			*check++; *check++; *check++;
		}
	}
	
}

Rect buttonArea;
Mat canardInterface = imread("C:\\Users\\User\\Desktop\\agri- dryness &paths detect 1.0\\media\\interface.jpg");
int blurValue = 1;
void alterBlur()
{
	switch (blurValue)
	{
		case 1:
		{
			blurValue = 3;
			break;
		}
		case 3:
		{
			blurValue = 5;
			break;
		}
		case 5:
		{
			blurValue = 10;
			break;
		}
		case 10:
		{
			blurValue = 50;
			break;
		}
		case 50:
		{
			blurValue = 100;
			break;
		}
		case 100:
		{
			blurValue = 1;
			break;
		}
	}
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	cout << "!";
	if (event == EVENT_LBUTTONDOWN)
	{
		if (buttonArea.contains(Point(x, y)))
		{
			cout << "Clicked!" << endl;
			//rectangle(canard, button, Scalar(0, 0, 255), 2);
			Point circleCenter;
			circleCenter.x = 10;
			circleCenter.y = 10;
			circle(canardInterface, circleCenter, 5, Scalar(0, 0, 255), 1);
			imshow("interface", canardInterface);
			alterBlur();
		}
	}
	if (event == EVENT_LBUTTONUP)
	{
		canardInterface = imread("C:\\Users\\User\\Desktop\\agri- dryness &paths detect 1.0\\media\\interface.jpg");
	}
	imshow("interface", canardInterface);
	waitKey(1);
}

bool paths_OFF = true;
void composite_event(int event, int x, int y, int flags, void* userdata)
{
	cout << "?";
	if (event == EVENT_LBUTTONDOWN)
	{
			alterBlur();
	}
	if (event == EVENT_RBUTTONDOWN)
	{
		if (paths_OFF == true)
			paths_OFF = false;
		else
			paths_OFF = true;
		cout << paths_OFF;
	}
	int increment = 5;
	if (event == EVENT_MOUSEWHEEL)
	{
		cout << "->" << event;
		// 140 170
		minT += increment;
		if (minT > 180)
			minT = 140;
	}
	if (event == EVENT_MBUTTONDOWN)
	{
		cout << "->" << event;
		// 140 170
		maxT += increment;
		if (maxT > 220)
			maxT = 170;
	}
	waitKey(1);
}


int main(int argc, const char** argv)
{
		

		/*********************** pic loading ********************************/
		string name1 = "C:\\Users\\User\\Desktop\\agri- dryness &paths detect 1.0\\media\\j2.png";
		//default testing picture
		Mat canard = imread("c:\\canard.jpg");
		// current image is loaded
		Mat field = imread(name1);
		Mat result = field.clone();
		Mat Tgreen;
		int Xresize = 400;//218
		int Yresize = 300;//195
		resize(field, field, Size(Xresize, Yresize));

		VideoCapture* video = new VideoCapture[1];
		string filename = "C:\\Users\\User\\Desktop\\agri- dryness &paths detect 1.0\\media\\vid2.mp4";// 2.mp4";
		video[0].open(filename);
		//video[0].set(CV_CAP_PROP_POS_FRAMES, 1100);
		Mat current_frame;
		
		//test sur image fixe
		Mat greenResult = field.clone();
		vegetalDetect(field,greenResult);
		//imshow("vegetation", greenResult);

		Mat yellowResult = field.clone();
		dryDetect(field, yellowResult,5);
		//imshow("secheresse", yellowResult);
		imshow("un canard", canard);
		//imshow("un champ de mais", field);

		clock_t timer;


		/*buttonArea = Rect(0, 0, 50, 50);
		imshow("interface", canardInterface);
		moveWindow("interface",1020, 450);
		setMouseCallback("interface", callBackFunc);
		waitKey(5);*/
		


		//int blur = 5;
		//video
		//if (1==0)
		video[0] >> current_frame;
		//how many frames does this video have ?
		int nb_frames = video[0].get(CV_CAP_PROP_FRAME_COUNT);
		cout << nb_frames;

		int current_frame_counter = 0;
		while (!current_frame.empty() && current_frame_counter < nb_frames-1)//current_frame == empty)
		{
				current_frame_counter++;
				timer = clock();
				video[0] >> current_frame;

				int proportion = 3;
				resize(current_frame, current_frame, Size(current_frame.cols / proportion, current_frame.rows / proportion));
				imshow("raw video", current_frame);
				Mat greenFrame = current_frame.clone();
				vegetalDetect(current_frame, greenFrame);

				imshow("detection of vegetation", greenFrame);
				Mat dryFrame = current_frame.clone();

				Mat temp_current_frame = current_frame.clone();
				dryDetect(temp_current_frame, dryFrame, blurValue);
				imshow("detection of dryness", dryFrame);
				Mat composite = current_frame.clone();
				greenYellowDiff(greenFrame, dryFrame, composite);
				//resize(composite, composite, Size(current_frame.cols *4, current_frame.rows *4));

				setMouseCallback("composite", composite_event);
				if (paths_OFF == true)
					imshow("composite", composite);
				else
					imshow("composite", dryFrame);


				int x1 = 10;
				int y1 = 10;
				int x2 = 600;
				int y2 = 300;
				moveWindow("raw video", x1, y1);
				moveWindow("detection of vegetation", x1, y2);
				moveWindow("detection of dryness", x2, y1);
				moveWindow("composite", x2, y2);
				timer = clock() - timer;
				cout << (float)timer << "ms ";
				waitKey(1);
		}

		
		waitKey();

	return(0);
}