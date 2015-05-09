#include "Calculate_dimens.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::vector <std::vector <int> > Calculate_dimens(int i_start,int i_finish,int j_start,int j_finish,std::vector <std::vector <int> > log_1,int log1_counter){

	int surface_area;
	int side1;
	int side2;
	int centre1; //the x dim
	int centre2; //the y dim
	std::string s1;
	std::string s2;
	side1 = i_finish - i_start;
	side2 = j_finish - j_start;
	int perimeter = side1 * 2 + side2 * 2;

	if(side1 == side2){ // the box is a square
		surface_area = side1 * side1;
	}
	else{ // the box is not a square
		surface_area = (side2 * side1) / 2;
	}
	centre1 = i_start;
	centre2  = (j_start + j_finish) / 2;
	s1 = std::to_string(centre1);
	s2.append(" ");
	s2 = "The centre of the box is (";
	s2.append(s1);
	s2.append(",");
	s1 = std::to_string(centre2);
	s2.append(s1);
	s2.append(")");
	std::cout << s2;
	std::cout << "\n";

	log_1[1][log1_counter++] = centre1; //the x axis of the centre
	log_1[1][log1_counter] = centre2; // the y axis of the centre

	return log_1;

}