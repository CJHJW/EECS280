#include <cassert>
#include "Image.hpp"

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  assert(0 < width && 0 < height);
  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  std::string file_type;
  int width, height, max_val;

  is >> file_type;
  assert(file_type == "P3");

  is >> width >> height >> max_val;
  assert(max_val == MAX_INTENSITY);

  // Initializes the width and height in img 
  // and also the red, green and blue channels
  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);

  // Reading pixel values
  for (int row = 0; row < height; ++row)
  {
    for(int col = 0; col < width; ++col)
    {
      // Do we need to use the Pixel struct here?
      int red_val, green_val, blue_val;
      is >> red_val >> green_val >> blue_val;

      *Matrix_at(&img->red_channel, row, col) = red_val;
      *Matrix_at(&img->green_channel, row, col) = green_val;
      *Matrix_at(&img->blue_channel, row, col) = blue_val;
    }
  }

}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3" << std::endl;
  os << img-> width << " " << img->height << std::endl;
  os << MAX_INTENSITY << std::endl;

  for (int row = 0; row < img->height; ++row)
  {
    for (int col = 0; col < img->width; ++col)
    {
      // Print int for the red component followed by a space
      os << *Matrix_at(&img->red_channel, row, col) << " ";
      // Print int for the green component followed by a space
      os << *Matrix_at(&img->green_channel, row, col) << " ";
      // Print int for the blue component followed by a space
      os << *Matrix_at(&img->blue_channel, row, col) << " ";
    }

    os << std::endl;
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  // POD so it is acceptable to access members directly
  Pixel p;
  p.r = *Matrix_at(&img->red_channel, row, column);
  p.g = *Matrix_at(&img->green_channel, row, column);
  p.b = *Matrix_at(&img->blue_channel, row, column);

  return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));

  // Finds the element in the rgb channels and changes the value
  // to the one specified by the color passed as an argument
  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  for (int row = 0; row < img->height; ++row)
  {
    for (int col = 0; col < img->width; ++col)
    {
      Image_set_pixel(img, row, col, color);
    }
  }
}
