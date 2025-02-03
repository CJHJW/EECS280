#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}



// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

// Fills a 3x5 Matrix with 2 values and checks
// that Matrix_print prints the Matrix as expected
TEST(test_print_basic) {
  Matrix mat;


  Matrix_init(&mat, 2, 2);

  *Matrix_at(&mat, 0, 0) = 70;
  *Matrix_at(&mat, 1, 1) = 35;
  ostringstream expected;
  expected << "2 2\n" 
           << "70 0 \n"
           << "0 35 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  

}

// Creates a 3x5 Matrix and fills it with 2 values and checks
// if the correct value is accessed using the Matrix_at function
TEST(test_at_basic)
{
  Matrix mat;

  Matrix_init(&mat, 3, 5);

  *Matrix_at(&mat, 0, 0) = 70;

  *Matrix_at(&mat, 2, 1) = 87; 

  // Pass the matrix as a const pointer to test the const version of Matrix_at
  const Matrix* const_mat = &mat;


  ASSERT_EQUAL(*Matrix_at(const_mat, 0, 0), 70);
  ASSERT_EQUAL(*Matrix_at(const_mat, 2, 1), 87);


  ASSERT_EQUAL(*Matrix_at(const_mat, 0, 1), 0);
  ASSERT_EQUAL(*Matrix_at(const_mat, 1, 2), 0); 
}

// Creates a small 1x1 matrix and checks if the fill
// function correctly changes all the values of the matrix
TEST(test_fill_small)
{
  Matrix mat;
  const int value = 42;
  Matrix_init(&mat, 1, 1);
  Matrix_fill(&mat, value);

      ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), value);

}

// Creates a 3x5 matrix and checks if the fill
// function correctly changes all the values of the matrix
TEST(test_fill_medium)
{
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  *Matrix_at(&mat, 2, 1) = 2;
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// Creates a small 1x1 matrix and checks if the fill border
// function correctly changes the correct values
TEST(test_fill_border_small)
{
  Matrix mat;
  const int value = 2;
  Matrix_init(&mat, 1, 1);

  Matrix_fill_border(&mat, value);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), value);
}

// Creates a 2x2 matrix and checks if the fill border
// function correctly changes the correct values
TEST(test_fill_border_medium)
{
  Matrix mat;
  const int value = 5;
  Matrix_init(&mat, 2, 2);

  Matrix_fill_border(&mat, value);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), value);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), value);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), value);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), value);
}

// Creates a 3x5 matrix and checks if the fill border
// function correctly changes border values
TEST(test_fill_border_rect)
{
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 5;
  Matrix_init(&mat, 3, 5);

  Matrix_fill_border(&mat, value);

  // Check the first and last row to see if correct value
  // is there
  for (int i = 0; i < width; ++i) {
    // First row
    ASSERT_EQUAL(*Matrix_at(&mat, 0, i), value); 
    // Last row
    ASSERT_EQUAL(*Matrix_at(&mat, height - 1, i), value); 
  }

  // Check the first and last column to see if correct value 
  // is there
  for (int i = 0; i < height; ++i) {
    ASSERT_EQUAL(*Matrix_at(&mat, i, 0), value); // First column
    ASSERT_EQUAL(*Matrix_at(&mat, i, width - 1), value); // Last column
  }

  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 1), 0);


}

// Creates a 3x5 matrix with various positive int values
// and checks if correct max is found
TEST(test_max_positive)
{
Matrix mat;
Matrix_init(&mat, 3, 5);

Matrix_fill(&mat, 8);
*Matrix_at(&mat, 3, 2) = 10;
ASSERT_EQUAL(Matrix_max(&mat), 10);

}

// Creates a 3x5 matrix with various positive int values
// and checks if correct max is found
TEST(test_max_negative)
{
Matrix mat;
Matrix_init(&mat, 3, 5);

Matrix_fill(&mat, -100);
*Matrix_at(&mat, 3, 1) = -10;
ASSERT_EQUAL(Matrix_max(&mat), -10);

}

// Creates a 3x5 matrix and checks the first row 
// for the correct column of the min
TEST(test_column_of_min_in_row_multiple_min)
{
  Matrix mat;
  Matrix_init(&mat, 3, 5);

  Matrix_fill_border(&mat, -1);
  *Matrix_at(&mat, 0, 0) = 10;
  int col = Matrix_column_of_min_value_in_row(&mat, 0, 0, 2);
  ASSERT_EQUAL(col, 1);
}

// Creates a 10x10 matrix and checks the 6th row 
// for the correct column of the min value when 
// it is on the start_col

TEST(test_column_of_min_in_row_on_start_col)
{
  Matrix mat;
  Matrix_init(&mat, 10, 10);

  Matrix_fill(&mat, -10);
  *Matrix_at(&mat, 5, 5) = -93;
  int col = Matrix_column_of_min_value_in_row(&mat, 5, 5, 9);
  ASSERT_EQUAL(col, 5);

}

// Creates a 10x10 matrix and checks the 6th row 
// for the correct column of the min value when 
// it is on the end_col (end_col is exclusive)
TEST(test_column_of_min_in_row_on_end_col)
{
  Matrix mat;
  Matrix_init(&mat, 10, 10);

  Matrix_fill(&mat, -10);
  *Matrix_at(&mat, 5, 9) = -93;
  int col = Matrix_column_of_min_value_in_row(&mat, 5, 0, 9);
  ASSERT_EQUAL(col, 0);

}

// Creates a 3x5 and checks if the correct min value
// for the row is returned when it is on the 
// start_col of the row (start_col is inclusive)
TEST(test_min_value_in_row_min_on_start)
{
  Matrix mat;
  Matrix_init(&mat, 3, 5);

  Matrix_fill_border(&mat, -1);
  *Matrix_at(&mat, 0, 0) = -5;
  *Matrix_at(&mat, 0, 1) = 10;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 2), -5);
}

// Creates a 3x5 and checks if the correct min value
// for the row is returned when it is on the 
// end_col of the row (end_col is inclusive)
TEST(test_min_value_in_row_min_on_end)
{
  Matrix mat;
  Matrix_init(&mat, 3, 5);


  Matrix_fill_border(&mat, -1);
  *Matrix_at(&mat, 0, 2) = -5;
  *Matrix_at(&mat, 0, 1) = 10;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 2), -1);
}




TEST_MAIN() // Do NOT put a semicolon here
