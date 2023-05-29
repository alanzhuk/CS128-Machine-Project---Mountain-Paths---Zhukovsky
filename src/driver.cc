#include <string>
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <iostream>
void print(std::vector<std::vector<int>> input) {
    for(unsigned int i = 0; i < input.size(); i++) {
        for (unsigned int w = 0; w < input[i].size(); w++) {
            std::cout << input[i][w] << " ";
        }
        std::cout << std::endl;
    }
}
int main() {
    std::string file = "/home/vagrant/src/mp5-mountain-paths-alanzhuk/example-data/ex_input_data/all-tie-row1-2w-3h.dat";
    ElevationDataset elevation(file, 2, 3);
    print(elevation.GetData());
    GrayscaleImage gray(elevation);
    PathImage path(gray,elevation);
    for (unsigned int i = 0; i < path.GetPathImage().size(); i++) {
        for (unsigned int w = 0; w < path.GetPathImage()[i].size(); w++) {
            std::cout << " ";
            if (path.GetPathImage()[i][w].Blue() == 63 && path.GetPathImage()[i][w].Red() == 252 && path.GetPathImage()[i][w].Green() == 25) {
                std::cout << "rd";
            } else if (path.GetPathImage()[i][w].Blue() == 13 && path.GetPathImage()[i][w].Red() == 31 && path.GetPathImage()[i][w].Green() == 253) {
                std::cout << "gn";
            } else {
                std::cout << "gy";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}