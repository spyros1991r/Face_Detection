#include <cstdio>
#include <fstream>
#include "pixels1.h"
#include "Template_matching2.h"
#include "Mpeg_to_jpeg.h"
#include "Non_Training.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

void Non_Training(std::string s4,std::string s3){ //s4 the name of the video file,s3 the path to the video file

	int  max_frames = Mpeg_to_jpeg(s4,s3);

	Non_Training3("image",s3,max_frames);

}
void Non_Training3(std::string s4,std::string s3,int max_frames){ // s4 the name of the image, s3 the path to the image


	int red1,blue1,green1,y4,cb,cr;
	int count_height = 0;
	int count_width = 0;
	int temp_x1 = 0;
	int temp_y1 = 0;
	int temp_z1 = 0;
	int temp_red1;
	int temp_blue1;
	int temp_green1;
	double no_sample1[26][26][26];
	double sample1[26][26][26];
	double a1, a2;
	cv::Mat img1;
	cv::Vec3b intensity;





	std::string filename = "log1.txt";
	const char * c1 = filename.c_str(); //convert from string to const char *
	std::remove(c1); //delete file

	std::fstream myfile1("propabilites_no_sample.txt", std::ios_base::in); 
	std::fstream myfile2("propabilites_sample.txt", std::ios_base::in); 
	//std::fstream myfile3("propabilites1.txt", std::ios_base::in); 


	for(int i = 0; i <= 25; i++){ //pass the propability values to tables
		for(int u = 0; u <= 25; u++){
			for(int p = 0; p <= 25; p++){
				myfile1 >> a1;
				myfile2 >> a2;
				no_sample1[i][u][p] = a1;
				sample1[i][u][p] = a2;
			}
		}
	}
	std::string temp1 = s3;
	std::string temp2 = s4;
	int frame_counter = 0; //prepei na ksekinaei apo 0

	while(true) { //work for all frames of the video

		if(frame_counter == max_frames){
			std::cout << "All frames have been processed";
			exit(0);
		}
		s3 = temp1; //initialize again s3 so that it takes the right image name every time
		s4 = temp2;
		frame_counter++;
		//s2 = std::to_string(1);
		s3.append(s4);
		s4 = std::to_string(frame_counter);
		s3.append(s4);
		s3.append(".jpg");
		img1 = cv::imread(s3);

		std::cout << s3;


		if(img1.empty()){
			std::cout << "empty image";
			system("PAUSE");
			exit(1);
		}
		cv::Size s = img1.size();  //find the height and width of the image in jpeg format
		const  int height = s.height;
		const  int width  = s.width;
		std::vector< std::vector<pixels1> > pixels2(height, std::vector<pixels1>(width));
		std::vector< std::vector<int> > belongs1(height, std::vector<int>(width));

		for(int i = 0;i < height; i++){
			for(int j = 0;j < width; j++){
				intensity = img1.at<cv::Vec3b>(i,j); //read the pixel values
				blue1 = intensity[0];
				green1 = intensity[1];
				red1 = intensity[2];

				y4 = (0.299 * red1) + (0.587 * green1) + (0.114 * blue1);

				if(count_width >= width){ //if we are in the end of the line
					count_height++;
					count_width = 0;
					pixels2[i][j].set_y(y4);

					pixels2[i][j].set_r(red1);
					pixels2[i][j].set_g(green1);
					pixels2[i][j].set_b(blue1);
					count_width++;
				}
				else{
					pixels2[i][j].set_y(y4);

					pixels2[i][j].set_r(red1);
					pixels2[i][j].set_g(green1);
					pixels2[i][j].set_b(blue1);
					count_width++;
				}
			}
		} 
		int temp_counter = 0;
		for(int i = 0;i < height;i++){ // loop to fill the table belongs1
			for(int j = 0; j < width; j++){

				temp_red1 = pixels2[i][j].get_r();
				temp_green1 = pixels2[i][j].get_g();
				temp_blue1 = pixels2[i][j].get_b();

				int v_r = 9; //values to find the position to ++
				int v_g = 9;
				int v_b = 9;
				if(v_r <= temp_red1){ 
					while(true){ //find between which values v_r is
						v_r += 10;
						if(v_r >= temp_red1){
							break;
						}
					}
				}
				if(v_g <= temp_green1){
					while(true){ //find between which values v_g is
						v_g += 10;
						if(v_g >= temp_green1){
							break;
						}
					}
				}
				if(v_b <= temp_blue1){
					while(true){ //find between which values v_b is
						v_b += 10;
						if(v_b >= temp_blue1){
							break;
						}
					}
				} 
				if((no_sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)]) == 0 && sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)] != 0){ //check if the divider test_var2 is 0
					temp_counter++;
					float testing_var = float(sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)]);
					belongs1[i][j] = 1;
				}
				else if((no_sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)]) == 0 && sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)] == 0){
					belongs1[i][j] = 0;
				}
				else{ // if w0 has a propability of 0 that means that no pixels outside the face have these gray intensity so we take it a face region
					double test_var1 = double(sample1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)]);

					double test_var2 = double(no_sample1[int(v_r/ 10)][int(v_g / 10)][int(v_b / 10)]); 		
					double value1 = test_var1 / test_var2;

					int test_kalimera =  5;

					if(value1 > 1.0){ //0.05 value for chinese man,1.0 for the mic man
						belongs1[i][j] = 1;
					}
					else{
						belongs1[i][j] = 0;
					}
				}
			}
		}
		/*	cv::Mat to_screen(height,width, CV_8UC3);
		for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
		if(belongs1[i][j] == 0){ // if it has not already been painted as square pixel
		to_screen.at<cv::Vec3b>(i, j)[0] =  pixels2[i][j].get_b();
		to_screen.at<cv::Vec3b>(i, j)[1] = pixels2[i][j].get_g();
		to_screen.at<cv::Vec3b>(i, j)[2] = pixels2[i][j].get_r();
		}
		else{
		to_screen.at<cv::Vec3b>(i, j)[0] =  0;
		to_screen.at<cv::Vec3b>(i, j)[1] = 204;
		to_screen.at<cv::Vec3b>(i, j)[2] = 102;
		}
		}
		}
		cv::imwrite("eikona1.jpeg",to_screen);*/
		Template_matching2(belongs1,height,width,pixels2,temp1,frame_counter);
	}
}