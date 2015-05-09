#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv\cv.h>
#include <opencv2/highgui/highgui.hpp>

int Mpeg_to_jpeg(std::string video_name,std::string export_path){ //mpeg video to jpeg frames

	std::vector<int> myvector(2); //first position max frames (counter), second position fps
	int counter = 1;
	std::string s1;
	std::string name; // the total name of the exported image
	cv::Mat image1; 	 
	cv::Mat gray_image;
	cv::VideoCapture new1;
	new1.cv::VideoCapture::open(video_name);	
	std::string temp_exp = export_path; 
	int fps;

	if(new1.cv::VideoCapture::isOpened()){
		fps = new1.get(CV_CAP_PROP_FPS);
		while(true){	
			if(new1.cv::VideoCapture::read(image1)){
				name = "image";
				name.append(std::to_string(counter));
				name.append(".jpg");
				temp_exp = "";
				temp_exp.append(name);
				cv::imwrite(temp_exp,image1); 
				counter++;
			}
			else{
				break;
			}
		}
	}
	else{
		std::cout << "The video could not be opened";
		exit(1);
	}
	return counter - 1;
}