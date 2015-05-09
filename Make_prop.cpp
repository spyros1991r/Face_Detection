
#include <iostream>
#include <array>
#include <vector>
#include <cstdio>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

void Make_prop(std::string s5, std::string s4,int number_of_files){ //s5 the name of the images, s4 the txt file with the propabilites


	std::string s1;
	std::string s2;
	std::string s3;
	int red1, green1, blue1;
	int height; //the height and width of the image in bmp format
	int width;
	double count_pixels = 0.0;
	cv::Mat img1;
	cv::Vec3b intensity;
	//array2d<rgb_pixel> img;
	//array2d<rgb_pixel> img2;
	int values1[26][26][26];

	for(int i = 0; i <= 25; i++){
		for(int u = 0; i <= 25; i++){
			for(int p = 0; i <= 25; i++){
				values1[i][u][p] = 0;
			}
		}
	}

	for(int j = 1; j <= number_of_files; j++){ 
		if(j == 807){
			continue;
		}
		s1 = s5;
		s2 = std::to_string(j);
		s3 = ".jpg";
		s1.append(s2);
		s1.append(s3);
		std::cout << s1;
		img1 = cv::imread(s1);
		if(img1.empty()){
			exit(1);
		}
		cv::Size s = img1.size(); //find the height and width of the image in jpeg format
		height = s.height;
		width = s.width;
		std::cout << img1.size();
		cv::medianBlur(img1,img1,3); //Apply Median Filter


		for(int i = 0;i < height; i++){
			for(int j = 0;j < width; j++){
				intensity = img1.at<cv::Vec3b>(i,j);
				blue1 = intensity[0];
				green1 = intensity[1];
				red1 = intensity[2];
				if(red1 < 250 || green1 < 250 || blue1 < 250){

					count_pixels++;
					int v_r = 9; //values to find the position to ++
					int v_g = 9;
					int v_b = 9;
					if(v_r <= red1){ 
						while(true){ //find between which values temp_y is
							v_r += 10;
							if(v_r >= red1){
								break;
							}
						}
					}
					if(v_g <= green1){
						while(true){ //find between which values temp_cb is
							v_g += 10;
							if(v_g >= green1){
								break;
							}
						}
					}
					if(v_b <= blue1){
						while(true){ //find between which values temp_cr is
							v_b += 10;
							if(v_b >= blue1){
								break;
							}
						}
					}
					if(v_r / 10 == 25 && v_g / 10 == 25 && v_b / 10 == 25){
						std::cout << blue1;
						std::cout << "test1";

					}
					values1[int(v_r / 10)][int(v_g / 10)][int(v_b / 10)]++;
				}
			}
		}
	}


	std::ofstream fout(s4); 
	for(int j = 0; j <= 25; j++){ //write the probabilities to the txt file
		for(int u = 0; u <= 25; u++){
			for(int p = 0; p <= 25; p++){
				if(j == 25 && u == 25 && p == 25){
					std::cout << "testtt";
				}
				int testing_variable = values1[j][u][p];
				double a1 = values1[j][u][p] / count_pixels;
				fout << a1;
				fout << " ";
				//test_var2++;
			}
		}
	}
}