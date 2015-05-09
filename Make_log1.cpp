#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "Calculate_dimens.h";

void Make_log1(int frame_counter,std::vector <std::vector <int> > pos,int pos_counter){

	std::ofstream fout("log1.txt",std::ios_base::app); //write
	std::fstream myfile1("log1.txt",std::ios_base::in); //read
	std::string read1;
	int value;
	bool has_non_absolute = false; //check if each centre has a non-absolute value, if not then put -1 into its position except the first frame
	std::vector< std::vector<int> > log1_(2, std::vector<int>(10));
	int log1_counter = 0;
	int value1 = 0;
	int value2 = 0;

	for(int i = 0; i <= pos_counter - 1;i++){
		log1_ = Calculate_dimens(pos[i][0],pos[i][1],pos[i][2],pos[i][3],log1_,log1_counter);
		log1_counter += 2;
	}

	int kalimera = 5;
	if(fout.is_open()){
		if(frame_counter == 1){ //first frame
			int i = 0;
			while(i < log1_counter){
				fout << log1_[1][i++];
				fout << " ";
				fout << log1_[1][i++];
				fout << " ";
			}
			fout << "|";
			fout << " ";
			fout << "|";
			fout << " ";
		}
		else{ //rest of the frames
			int counter1 = 1;
			int counter2 = 1;
			int position1 = 0;
			while(true){
				myfile1 >> read1;
				if(read1.compare("|") != 0 && counter2 == frame_counter - 1){ //in the absolute position values in one frame before the one that we are now
					value = std::stoi(read1);
					log1_[0][position1++] = value; 
				}
				else if(read1.compare("|") == 0 && counter2 == frame_counter){ //if it is a bracket and we one frame before the one that we are now
					break;
				}
				else if(read1.compare("|") == 0){ //we are not on the one frame before the last
					if(counter1 > counter2){
						counter2++;
					}
					else{
						counter1++;
					}
				}
			}
			int i = 0;
			if(log1_counter > 0){
				while(i < log1_counter){ //put the new absolute values to txt
					fout <<  log1_[1][i++];
					fout << " ";
					fout <<  log1_[1][i++];
					fout << " ";
				}
			}
			fout << "|";
			fout << " ";
			for(int i = 0;i < log1_counter;i++){ //find if two centres are closer than 5 pixel in x axis
				for(int j = 0;j < position1;j++){
					value1 = log1_[1][i];
					value2 = log1_[0][j];

					if(i % 2 == 0 || i == 0){ // if we are on a x-axis position
						if(j % 2 == 0 || j == 0){
							if(value1 >  value2){ //check so that we don't have to check between positive and negative numbers
								int temp = value1 -  value2;
								int bla = 5;
								if(temp < 10){
									fout << temp;
									fout << " ";
									has_non_absolute = true;
									break;
								}
							}
							else if(value1 <  value2){
								int temp = value2 -  value1;
								int bla = 5;
								if(temp < 10){
									fout << temp;
									fout << " ";
									has_non_absolute = true;
									break;
								}
							}
							else{
								continue;
							}
						}
					}
					else if (i % 2 == 1){
						if(j % 2 == 1){
							if(value1 >  value2){ //check so that we don't have to check between positive and negative numbers
								int temp = value1 -  value2;
								if(temp < 10){
									fout << temp;
									fout << " ";
									has_non_absolute = true;
									break;
								}
							}
							else if(value1 <  value2){
								int temp = value2 -  value1;
								int bla = 5;
								if(temp < 10){
									fout << temp;
									fout << " ";
									has_non_absolute = true;
									break;
								}
							}
							else{
								continue;
							}
						}
					}
				}
				if(has_non_absolute == false){ //if a centre has no non-absolute values then put -1 except first frame
					fout << 0;
					fout << " ";
				}
				else{
					has_non_absolute = false;
				}
				value1 = 0;
				value2 = 0;
			}
			fout << "|";
			fout << " ";
		}
	}
}