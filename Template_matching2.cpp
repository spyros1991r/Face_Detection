#include "Template_matching2.h"
#include "Draw3.h"
#include <string>
#include "Formula_Impl2.h"



void Template_matching2(std::vector <std::vector <int> > belongs_after,int height,int width,std::vector <std::vector <pixels1> > pixels3,std::string temp1,int frame_counter){

	std::vector< std::vector<int> > belongs_after2(height, std::vector<int>(width)); // which pixels are still considered possible face regions after this stage
	std::vector< std::vector<int> > pos(height, std::vector<int>(width)); // positions of edges of the square as in each line: i_start,i_finish,j_start,j_finish
	int pos_counter = 0; //counter for pos vector
	int temp_start_w2;

	int pixel_counter_w = 0; // count the number of contiguous pixels found in width
	int pixel_counter_h = 0; // count the number of contiguous pixels found in height
	bool found_flag = false; // we found at least one contiguous area of pixels
	bool found_local = false; //flag to know when we can get out of the upper for loops
	bool flag_width = false; 
	bool flag_no_space = false; 
	bool flag_next_j = false; //just break from the very internal for loops (upper part) and continue with the j loop
	int start_w = 0; //start width
	int end_w = 0; //end width
	int start_h2 = 0; //start height
	int end_h = 0; //end height 
	int counter_outside = 0; // counter of the outside template 
	int counter_inside = 0; //counter of the inside template
	int pixels2 = 0; //pixels that exist in the current template - we don't always have 8x8 region


	int belongs_counter = 1; //an exoume squares pou pane na ginoun overlap tote sto belongs_after2 stin idia thesi tha einai != 0 

	std::string s1 = "apotelesmata"; // na figei
	std::string s2 = std::to_string(frame_counter);
	s1.append(s2);
	s1.append(".jpeg");


	while(true){
		for(int i = start_h2; i < height; i++){
			pixel_counter_w = 0;
			flag_width = false;
			start_w = 0;
			for(int j = start_w; j < width; j++){
				if(belongs_after[i][j] == 1 && pixel_counter_w < 100 && belongs_after2[i][j] == 0){
					if(flag_width == false){ //to start_h den xreiazetai na to ipologisoume giati theoroume oti ta pixels tou width den ksepernoun ti mia grammi
						temp_start_w2 = j;
						flag_width = true;
					}
					pixel_counter_w++;
				}
				else if(belongs_after[i][j] == 1 && pixel_counter_w >= 100  && belongs_after2[i][j] == 0){
					int kalimera = 5;

					if((j + 70) > width){ //den xoraei allo tetragono se auti ti seira
						break;
					}
					else if((i + 160) > height){ // an i > megalitero tou mirkoterou template tote telos
						if((i + 160) > height  && found_flag == false){
							std::cout << "No face regions found";
							return;
						}
						else if((i + 160) > height && found_flag == true){
							Formula_Impl2(height,width,pos,pixels3,s1,frame_counter,pos_counter);
							return;
						}
					}
					for(int k  = 0;k < pos_counter;k++){// check if height has 30 pixels that do not belong to other square for the first width pixel
						if((i > pos[k][0] && i < pos[k][1]) && ((j - 30) > pos[k][2] && (j - 30) < pos[k][3])){
							int square1_pixels = 0; //find which of the two squares has more '1' pixels
							int square2_pixels = 0;
							for(int z = i;z <= i + 160;z++){ 
								for(int t = temp_start_w2;t <= j + 70;t++){
									if(belongs_after[z][t] == 1){
										square2_pixels++; //how many '1' pixels the new square has
									}
								}
							}
							for(int z = pos[k][0];z <= pos[k][1];z++){ 
								for(int t =  pos[k][2];t <=  pos[k][3];t++){
									if(belongs_after[z][t] == 1){
										square1_pixels++; //how many '1' pixels the initial square has
									}
								}
							}
							if(square2_pixels > square1_pixels){ 
								for(int z = pos[k][0];z <= pos[k][1];z++){ //put 0 in the old square positions
									for(int t =  pos[k][2];t <=  pos[k][3];t++){
										belongs_after2[z][t] = 0;
									}
								}
								pos[pos_counter][0] = i; 
								pos[pos_counter][1] = i+160;
								pos[pos_counter][2] = temp_start_w2;
								pos[pos_counter++][3] = j + 70;

								for(int z = pos[k][0];z <= pos[k][1];z++){ 
									for(int t =  pos[k][2];t <=  pos[k][3];t++){
										belongs_after2[z][t] = k + 1;// bale stis theseis pou exei to neo square to frame_counter (k - 1) tou paliou square
									}
								}
							}
							else{
								pixel_counter_w = 0;
								flag_next_j = true;
								break;
							}
						}

					}
					if(flag_next_j == true){
						flag_next_j = false;
						break;
					}
					start_h2 = i;
					start_w = 0;
					pixel_counter_w = 0;
					found_local = true;
					found_flag = true;
					flag_width = false;
					break;
				}
				else if(((belongs_after[i][j] == 0 || belongs_after[i][j] == -1) && pixel_counter_w < 100) || belongs_after2[i][j] != 0){ // the area is not big enough to be a face
					if(pixel_counter_w > 0){
						j = j -(pixel_counter_w);
					}
					pixel_counter_w = 0;
					flag_width = false;
				}

				if((i + 160) > height  && found_flag == false){
					std::cout << "No face regions found";
					system("PAUSE");
					return;
				}
				else if((i + 160) > height && found_flag == true){
					Formula_Impl2(height,width,pos,pixels3,s1,frame_counter,pos_counter);
					return;
				}

			}
			if(found_local == true){
				found_local = false;
				break;
			}
		}

		pixel_counter_w = 0;
		if(start_h2 + 160 < height)
		{
			end_h = start_h2 + 160;
			end_w = temp_start_w2 + 100;
			for(int i = start_h2; i <= end_h; i++){
				for(int j = start_w; j <= end_w; j++){
					if(belongs_after[i][j] == 1 && ( j == start_w || i == start_h2 || j == end_w)){
						counter_outside++;
					}
					else if(belongs_after[i][j] == 1){
						counter_inside++;
						int k = 5;
					}
				}
			}
			pixels2 = (end_h - start_h2) * (end_w - temp_start_w2);

			if((counter_inside < pixels2 / 2)){
				int kalimera = 1; // na figei
				for(int i = start_h2; i <= end_h; i++){
					for(int j = start_w; j <= end_w; j++){
						belongs_after[i][j] = -1;
					}
				}
			}
			else{
				int kalimera = 1; // na figei
				for(int i = start_h2; i <= end_h; i++){
					for(int j = start_w; j <= end_w; j++){
						belongs_after2[i][j] = belongs_counter;
					}
				}
				belongs_counter++;

				pos[pos_counter][0] = start_h2; //na metaferthei sto formula_impl
				pos[pos_counter][1] = end_h;
				pos[pos_counter][2] = temp_start_w2;
				pos[pos_counter++][3] = end_w;
			}
			counter_inside = 0;
			counter_outside = 0;
		}
		else{
			if(found_flag == false){
				std::cout << "No face regions found";
				system("PAUSE");
			}
		}

	}
}
