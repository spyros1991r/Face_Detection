
#include "Draw3.h"
#include "Make_log1.h"

void Draw3(int height,int width,std::vector <std::vector <int> > pos, int pos_counter,std::string name_of_image,std::vector <std::vector <pixels1> > pixels2,int frame_counter){

	cv::Mat to_screen(height,width, CV_8UC3);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			to_screen.at<cv::Vec3b>(i, j)[0] = -1;
			to_screen.at<cv::Vec3b>(i, j)[0] = -1;
			to_screen.at<cv::Vec3b>(i, j)[0] = -1;
		}
	}

	for(int i = 0;i < pos_counter; i++) {
		if(pos[i][0] == -1){ //that square has been taken out by the Formula_Impl2
			continue;
		}
		for(int temp300 = pos[i][0];temp300 <= pos[i][1];temp300++){ //paint the square green
			if(temp300 == pos[i][0] || temp300 == pos[i][1]){ //if we are on the first line or the last line of the square
				for(int temp400 = pos[i][2]; temp400 <= pos[i][3]; temp400++){
					to_screen.at<cv::Vec3b>(temp300, temp400)[0] = 0;
					to_screen.at<cv::Vec3b>(temp300, temp400)[1] = 204;
					to_screen.at<cv::Vec3b>(temp300, temp400)[2] = 102;
				}
			}
			else{
				to_screen.at<cv::Vec3b>(temp300,  pos[i][2])[0] = 0;
				to_screen.at<cv::Vec3b>(temp300,  pos[i][2])[1] = 204;
				to_screen.at<cv::Vec3b>(temp300,  pos[i][2])[2] = 102;

				to_screen.at<cv::Vec3b>(temp300, pos[i][3])[0] = 0;
				to_screen.at<cv::Vec3b>(temp300, pos[i][3])[1] = 204;
				to_screen.at<cv::Vec3b>(temp300, pos[i][3])[2] = 102;

			}
		}
	}

	int kalimera = 5;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(to_screen.at<cv::Vec3b>(i,j)[0] != 0 && to_screen.at<cv::Vec3b>(i,j)[1] != 204 && to_screen.at<cv::Vec3b>(i,j)[2] != 102){ // if it has not already been painted as square pixel
				to_screen.at<cv::Vec3b>(i, j)[0] =  pixels2[i][j].get_b();
				to_screen.at<cv::Vec3b>(i, j)[1] = pixels2[i][j].get_g();
				to_screen.at<cv::Vec3b>(i, j)[2] = pixels2[i][j].get_r();
			}
		}
	}
	cv::imwrite(name_of_image,to_screen); //save the testing image
	Make_log1(frame_counter,pos,pos_counter);

}