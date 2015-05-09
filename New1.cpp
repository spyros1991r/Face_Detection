#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cstdio>
#include "pixels1.h"
#include "Make_prop.h"
#include"Non_Training.h"

int main() 
{ 

	std::string user_input1;

	while(true){
		std::cout << "Please enter the name of the video or 0 to exit";
		std::cout << "\n";
		if(!getline(std::cin,user_input1)){
			return -1; //error
		}
		if(user_input1.empty()){
			std::cout << "The name of the video cannot be empty";
			std::cout << "\n";
		}
		else if(user_input1 == std::to_string(0)){
			break;
		}
		else{
			Non_Training(user_input1,"");
		}
	}

}