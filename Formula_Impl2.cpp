
#include "Formula_Impl2.h"
#include "Draw3.h"
#include "Formulas.h"
#include <iostream>

void Formula_Impl2(int height,int width,std::vector< std::vector<int> > pos,std::vector <std::vector <pixels1> > pixels3,std::string s1,int frame_counter,int pos_counter){ 

	int start_h;
	int end_h;
	int start_w;
	int end_w;
	int distance; // how many pixels will our y_table have for dct
	double value1 = 0.0;
	double value2 = 0.0;
	double value3 = 0.0;
	double value4 = 0.0;
	double div_value;
	cv::Mat dct1;

	for(int i = 0; i < pos_counter; i++){ // loop pos table 
		cv::Mat y_values;
		start_h = pos[i][0];
		end_h = pos[i][1];
		start_w = pos[i][2];
		end_w = pos[i][3];

		if((end_h - start_h) == 160 && (end_w - start_w) == 100){ // if the first template was used
			distance = 100; //dct must have even value arrays so the biggest possible number is 100
		}
		int temp_counter_x = 0;
		int temp_counter_y = 0;

		for(int i = start_h; i < (start_h + distance);i++){
			for(int j = start_w; j < start_w + distance;j++){
				y_values.push_back(pixels3[i][j].get_y());
			}
		}
		y_values.convertTo(y_values, CV_32F);
		cv::dct(y_values,dct1);
		dct1 = dct1.reshape(1,distance);

		value1 = formulas1::E1(distance,distance,dct1);
		value2 = formulas1::E_DC(8,8,dct1,value1);
		value3 = formulas1::E_H(8,8,dct1,value1);
		value4 = formulas1::E_V(8,8,dct1,value1);

		if(value4 == 0.0){
			div_value = 0.0;
		}
		else if(value3 == 0){
			div_value = 800; //just a big value, can be made into anything useful
		}
		else{
			div_value = value4 / value3;
		}

		if(value2 > 0.0062 || div_value < 0.0){ 
			for(int i = start_h; i < pos_counter; i++){ //put 0's in that region of cause it was false alarm
				for(int j = start_w; j < pos_counter; j++){
					pos[i][j] = -1;
				}
			}
		}
		Draw3(height,width,pos,pos_counter,s1,pixels3,frame_counter);
	}
}