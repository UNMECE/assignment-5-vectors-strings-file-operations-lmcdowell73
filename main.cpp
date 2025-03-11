#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list) {
    float total_r = 0.0f, total_g = 0.0f, total_b = 0.0f;

 	for (size_t i =0; i < pixel_list.size(); ++i) {
	const Pixel &p = pixel_list[i];
        total_r += p.r;
        total_g += p.g;
        total_b += p.b;
    }

    size_t num_pixels = pixel_list.size();

    float avg_r = total_r / num_pixels;
    float avg_g = total_g / num_pixels;
    float avg_b = total_b / num_pixels;
    
    std::cout << "Average Red: " << avg_r << std::endl;
    std::cout << "Average Green: " << avg_g << std::endl;
    std::cout << "Average Blue: " << avg_b << std::endl;
}


void flip_vertically(std::vector<Pixel> &pixel_list) {

int width = 512;  
int height = pixel_list.size() / width;

for (int x = 0; x < width; ++x) {
	for (int y = 0; y < height / 2; ++y) {
        	int top_index = y * width + x;
                int bottom_index = (height - 1 - y) * width + x;
                std::swap(pixel_list[top_index], pixel_list[bottom_index]);
        }
    }
}
int main(int argc, char *argv[]) 
{
if(argc < 2){
	std::cerr <<"Usage:" << argv[0] << "<filename>\n";
	return 1;
}


std::vector<Pixel> pixel_list;
std::ifstream file(argv[1]);
std::string line;

while (std::getline(file, line)) {
	Pixel p;
	

	size_t pos = line.find(',');	
	p.x = std::stoi(line.substr(0,pos));
	
	size_t prev_pos = pos + 1;
	pos = line.find(',', prev_pos);
	p.y = std::stoi(line.substr(prev_pos, pos - prev_pos));


	prev_pos = pos + 1;
	pos = line.find(',', prev_pos);
	p.r = std::stof(line.substr(prev_pos, pos - prev_pos));


	prev_pos = pos + 1;
	pos = line.find(',', prev_pos);
	p.g = std::stof(line.substr(prev_pos, pos - prev_pos));


	prev_pos = pos + 1;
	pos = line.find(',', prev_pos);
	p.b = std::stof(line.substr(prev_pos, pos - prev_pos));
	pixel_list.push_back(p);
	}	

file.close();


average_colors(pixel_list);
flip_vertically(pixel_list);

std::ofstream outfile("flipped.dat");
for (size_t i =0; i < pixel_list.size(); ++i) {
	const Pixel &p = pixel_list[i];
	 outfile << p.x << "," << p.y << ","
	<< p.r << "," << p.g << "," << p.b << "\n";
    }

outfile.close();

printf("File flipped.dat created and saved.");


return 0;
}
