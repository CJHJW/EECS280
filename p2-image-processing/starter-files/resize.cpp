#include "processing.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  Image img;
//   Error Checking https://eecs280staff.github.io/image-processing/#error-checking
//   bool check_1;
//   bool check_2;
//   bool check_3;
//   bool check_4;
//   if (check_1 || check_2 || check_3 || check_4) {

//   }
  std::ifstream inFile(argv[1]);
  std::ofstream outFile(argv[2]);
  Image_init(&img, inFile);
  int new_width = std::stoi(argv[3]);
  int new_height = std::stoi(argv[4]);
  seam_carve(&img, new_width, new_height);
  Image_print(&img, outFile);
}