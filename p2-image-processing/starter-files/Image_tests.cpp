#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// Sets various pixels in a 2x2 Image and checks
// that Image_width and Image_height returns the correct value.
TEST(test_width_height) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Check the width
  ASSERT_EQUAL(Image_width(&img), 2);
  // Check the height
  ASSERT_EQUAL(Image_width(&img), 2);
}

// Sets various pixels in two 2x2 Images and checks
// that Image_fill correctly fill these Images.
TEST(test_fill_pixel_1) {
  Image img;
  Image img1;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  const Pixel new_color_1 = {10, 5, 0};

  Image_init(&img, 2, 2);
  Image_init(&img1, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);
  Image_set_pixel(&img1, 0, 0, white);
  Image_set_pixel(&img1, 0, 1, blue);
  Image_set_pixel(&img1, 1, 0, green);
  Image_set_pixel(&img1, 1, 1, red);

  Image_fill(&img, new_color_1);

  // Check each pixel
  for (int i = 0; i < Image_width(&img); i++) {
    for (int j = 0; j < Image_height(&img); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, i, j), new_color_1));
    }
  }


  Image_fill(&img1, new_color_1);

  // Check each pixel
  for (int i = 0; i < Image_width(&img1); i++) {
    for (int j = 0; j < Image_height(&img1); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img1, i, j), new_color_1));
    }
  }

  ASSERT_TRUE(Image_equal(&img, &img1));

}

// Sets various pixels in one 3x3 Image and checks
// that Image_fill correctly fill the Image.
TEST(test_fill_pixel_2) {
  Image img2;
  Image_init(&img2, 3, 3);

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  const Pixel new_color_2 = {1, 2, 3};

  Image_set_pixel(&img2, 0, 0, white);
  Image_set_pixel(&img2, 0, 1, blue);
  Image_set_pixel(&img2, 0, 2, blue);
  Image_set_pixel(&img2, 1, 0, green);
  Image_set_pixel(&img2, 1, 1, red);
  Image_set_pixel(&img2, 1, 2, blue);
  Image_set_pixel(&img2, 2, 0, green);
  Image_set_pixel(&img2, 2, 1, red);
  Image_set_pixel(&img2, 2, 2, blue);

  Image_fill(&img2, new_color_2);

  // Check each pixel
  for (int i = 0; i < Image_width(&img2); i++) {
    for (int j = 0; j < Image_height(&img2); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img2, i, j), new_color_2));
    }
  }

}

// Sets various pixels in one 1x1 Image and checks
// that Image_fill correctly fill the Image.
TEST(test_fill_pixel_3) {
  Image img;
  Image_init(&img, 1, 1);

  const Pixel red = {255, 0, 0};
  const Pixel new_color = {1, 2, 3};

  Image_set_pixel(&img, 0, 0, red);

  Image_fill(&img, new_color);

  // Check each pixel
  for (int i = 0; i < Image_width(&img); i++) {
    for (int j = 0; j < Image_height(&img); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, i, j), new_color));
    }
  }

}

// Sets various pixels in one 2x3 Image and checks
// that Image_fill correctly fill the Image.
TEST(test_fill_pixel_4) {
  Image img;
  Image_init(&img, 3, 2);

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel new_color = {1, 2, 3};

  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 0, 2, blue);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, red);
  Image_set_pixel(&img, 1, 2, green);

  Image_fill(&img, new_color);

  // Check each pixel
  for (int i = 0; i < Image_width(&img); i++) {
    for (int j = 0; j < Image_height(&img); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, j, i), new_color));
    }
  }

}

// Sets various pixels in a 5x3 image and checks
// that Image_fill correctly fills the Image.
TEST(test_fill_pixel_5)
{
  Image img;
  Image_init(&img, 5, 3);

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel new_color = {1, 2, 3};

  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 0, 2, blue);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 3, red);
  Image_set_pixel(&img, 1, 4, green);
  
  Image_set_pixel(&img, 2, 0, red);
  Image_set_pixel(&img, 2, 1, green);
  Image_set_pixel(&img, 2, 2, blue);
  Image_set_pixel(&img, 2, 3, blue);
  Image_set_pixel(&img, 2, 4, red);

  Image_fill(&img, new_color);

  // Check each pixel
  for (int i = 0; i < Image_width(&img); i++) {
    for (int j = 0; j < Image_height(&img); j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, j, i), new_color));
    }
  }

}

// Read dog.ppm file to initialize the Image.
// Print the Image to verify the result.
TEST(test_file_initialize) {
  Image img;
  std::ifstream inFile("dog.ppm");
  Image_init(&img, inFile);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n5 5\n255\n";
  correct << "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n";
  correct << "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n";
  correct << "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n"; 
  correct << "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n"; 
  correct << "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  
}



TEST_MAIN() // Do NOT put a semicolon here
