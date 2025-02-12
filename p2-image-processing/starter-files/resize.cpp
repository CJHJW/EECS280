#include "processing.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  
//   Error Checking https://eecs280staff.github.io/image-processing/#error-checking
  

  bool correct_arg_count = (argc == 4 || argc == 5);
  // Ensures correct number of arguments are inputted
  if (!correct_arg_count)
  {
    std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
    << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;

    return 1;
  }
  
  // Checks if input file could be opened
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cout << "Error opening file: " << argv[1] << std::endl;
    return 1;
  }

  // Checks if output file could be opened
  std::ofstream outFile(argv[2]);
  if (!outFile) {
    std::cout << "Error opening file: " << argv[2] << std::endl;
    return 1;
  }

  Image img;
  Image_init(&img, inFile);

  int new_width = std::stoi(argv[3]);
  int new_height;

  // If no desired height was inputted, new_height is set to
  // the original height of image. Else, inputted height is stored
  if (argc == 4)
  {
    new_height = Image_height(&img);
  }
  else
  {
    new_height = std::stoi(argv[4]);
  }
  

  bool correct_desired_width = (0 < new_width &&
   new_width <= Image_width(&img));
  bool correct_desired_height = (0 < new_height &&
   new_height <= Image_height(&img));

  // Checks if new_height and new_width are in the correct range
  if (!correct_desired_width|| !correct_desired_height) {
    std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
    << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;

    return 1;
  }


  seam_carve(&img, new_width, new_height);
  Image_print(&img, outFile);

  return 0;
}