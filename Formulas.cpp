#include "Formulas.h"

namespace formulas1{
	int H1[8][8]; // the table H from the pdf
	int V1[8][8]; // the table V from the pdf


	void Formulas(){ //fill up H,V tables from the pdf

		for(int i = 0;i <= 7; i++){
			for(int j = 0;j <= 7; j++){
				if((i == 1 || i == 2) && j >= 2){
					H1[i][j] = 1;
				}
				else{
					H1[i][j] = 0;
				}
				if(i >= 2 && (j == 0 || j == 1)){
					V1[i][j] = 1;
				}
				else{
					V1[i][j] = 0;
				}
			}
		}
	}

	double E1(int M, int N,cv::Mat dct1) {

		double  value = 0;
		for(int i = 0; i <= (M * N * 4) - 1; i++){
			for(int m = 0; m <= 7; m++){
				for(int n = 0; n <= 7; n++){
					value += std::pow(dct1.at<float>(m,n),2);			
				}
			}
		}
		return value;
	}

	double E_DC(int M, int N,cv::Mat dct1,double E) {

		double value = 0.0;

		for(int i = 0; i <= (M * N * 4) - 1; i++){
			value += std::pow(dct1.at<float>(0,0),2);
		}
		return (value = value / E);
	}

	double E_H(int M, int N, cv::Mat dct1 ,double E) {

		double value = 0.0;

		for(int i = 0; i <= (M * N * 4) - 1; i++){
			for(int m = 0; m <= 7; m++){
				for(int n = 0; n <= 7; n++){
					value += pow(dct1.at<float>(m,n) * H1[m][n],2);
				}
			}
		}
		return (value = value / E);
	}

	double E_V(int M, int N, cv::Mat dct1, double E) {

		double value = 0.0;

		for(int i = 0; i <= (M * N * 4) - 1; i++){
			for(int m = 0; m <= 7; m++){
				for(int n = 0; n <= 7; n++){
					value += pow(dct1.at<float>(m,n) * V1[m][n],2);
				}
			}
		}
		return (value = value / E);
	}
}