// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

//filling 3 x 5 rectangle 
TEST(test_fill) {
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 3;
  const int value = 123;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat;
}

TEST(one_square) {
  Matrix *mat = new Matrix;

  //const int width = 1;
  //const int height = 1;
  const int value = 0;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);
  
  ASSERT_EQUAL(Matrix_width(mat), 1);
  ASSERT_EQUAL(Matrix_height(mat), 1);


  int *ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat,ptr), 0);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 10;

  const int *cptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(*cptr, 10);

  Matrix_fill_border(mat, 16);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 16);

  ASSERT_EQUAL(Matrix_max(mat), 16);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 0), 16);

  delete mat;
}

//one square test
TEST(one) {
  Matrix *mat = new Matrix;
  const int width = 1;
  const int height = 1;
  const int value = -1;
  Matrix_init(mat, 1, 1);

  Matrix_fill_border(mat, -1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), -1);

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  ostringstream output;
  Matrix_print(mat, output);
  string correctoutput = "1 1\n-1 \n";
  ASSERT_EQUAL(output.str(), correctoutput);

  delete mat;

}

TEST(one_again) {
  Matrix *mat = new Matrix;
  const int width = 1;
  const int height = 1;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 10);
  Matrix_fill_border(mat, 0);

  ASSERT_EQUAL((*Matrix_at(mat, 0, 0)), 0);

  delete mat;
}

TEST(nothing) {
  Matrix *mat = new Matrix;

  const int width = 0;
  const int height = 0;
  const int value = 10;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  delete mat;
    
}

TEST(rectangle) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  ASSERT_EQUAL(Matrix_width(mat), 3);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, 22);
  Matrix_fill_border(mat, 111);

  int *ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

  const int *cptr = Matrix_at(mat, 1, 2);
  ASSERT_EQUAL(Matrix_row(mat, cptr), 1);
  ASSERT_EQUAL(Matrix_column(mat, cptr), 2);

  ASSERT_EQUAL(Matrix_max(mat), 111);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), 111);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), 22);

  delete mat;
}

TEST(other_rectangle) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 3);
  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 3);

  Matrix_fill(mat, -123);
  Matrix_fill_border(mat, 0);

  int *ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

  const int *cptr = Matrix_at(mat, 1, 2);
  ASSERT_EQUAL(Matrix_row(mat, cptr), 1);
  ASSERT_EQUAL(Matrix_column(mat, cptr), 2);

  ASSERT_EQUAL(Matrix_max(mat), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 5), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), -123);

  delete mat;
}


TEST(square) {
  Matrix *mat = new Matrix;

  //const int width = 5;
  //const int height = 5;
  const int value = 100;
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, value);

  int *ptr = (Matrix_at(mat, 2, 3));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  ASSERT_EQUAL(*ptr, 100);
  *ptr = 10;

  const int *cptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(*cptr, 10);

  Matrix_fill_border(mat, 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 1);

  ASSERT_EQUAL(Matrix_max(mat), 100);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 5), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), 1);

  delete mat; 

}

TEST(square_even) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, -66);

  ASSERT_EQUAL(Matrix_width(mat), 4);
  ASSERT_EQUAL(Matrix_height(mat), 4);

  Matrix_fill_border(mat, 66);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 66);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 3), 66);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 66);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 66);

  ASSERT_EQUAL(Matrix_max(mat), 66);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 4), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 66);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 4), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 4), -66);

  delete mat;
}

TEST(one_row) {
  Matrix *mat = new Matrix;

  //const int width = 5;
  //const int height = 1;
  const int value = 1;
  Matrix_init(mat, 5, 1);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 1);

  Matrix_fill(mat, value);

  int *ptr = (Matrix_at(mat, 0, 4));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
  ASSERT_EQUAL(*ptr, 1);
  *ptr = 88;

  const int *cptr = Matrix_at(mat, 0, 4);
  ASSERT_EQUAL(*cptr, 88);

//filling the border with the same number as the fill value
  Matrix_fill_border(mat, 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 1);
  
  //would it be 88 when the value of the pointer changes but then the border changes it
  ASSERT_EQUAL(Matrix_max(mat), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 4), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 1);

  delete mat; // delete the Matrix

}

TEST(one_column) {
  Matrix *mat = new Matrix;

  //const int width = 1;
  //const int height = 5;
  const int value = 0;
  Matrix_init(mat, 1, 5);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_width(mat), 1);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, value);

  int *ptr = (Matrix_at(mat, 4, 0));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 17;

  const int *cptr = (Matrix_at(mat, 4, 0));
  ASSERT_EQUAL(*cptr, 17);

  Matrix_fill_border(mat, 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 4, 0), 100);

  ASSERT_EQUAL(Matrix_max(mat), 100);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 4, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, 0), 100);

  delete mat; // delete the Matrix

}

TEST(maximum_width) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, MAX_MATRIX_WIDTH, 1);
  ASSERT_EQUAL(Matrix_width(mat), MAX_MATRIX_WIDTH);
  ASSERT_EQUAL(Matrix_height(mat), 1);
  Matrix_fill(mat, 0);

  for(int r = 0; r < Matrix_height(mat); ++r){
    for(int c = 0; c < Matrix_width(mat); ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
    }
  }

  delete mat; // delete the Matrix

}

TEST(maximum_height) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, MAX_MATRIX_HEIGHT);
  ASSERT_EQUAL(Matrix_width(mat), 1);
  ASSERT_EQUAL(Matrix_height(mat), MAX_MATRIX_HEIGHT);
  Matrix_fill(mat, 0);

  for(int r = 0; r < Matrix_height(mat); ++r){
    for(int c = 0; c < Matrix_width(mat); ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
    }
  }

  delete mat; // delete the Matrix

}

TEST(maximum) {
  Matrix *mat = new Matrix;

  //const int width = MAX_MATRIX_WIDTH; = 500
  //const int height = MAX_MATRIX_HEIGHT; = 500
  const int value = 0;
  Matrix_init(mat, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_width(mat), 500);
  ASSERT_EQUAL(Matrix_height(mat), 500);

  Matrix_fill(mat, value);

  int *ptr = (Matrix_at(mat, 1, 399));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 1);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 399);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 20;

  const int *cptr = (Matrix_at(mat, 1, 399));
  ASSERT_EQUAL(*cptr, 20);

  Matrix_fill_border(mat, 1);
  ASSERT_EQUAL(*Matrix_at(mat, 499, 499), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 499), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 499, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 50), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 50, 0), 1);

  ASSERT_EQUAL(Matrix_max(mat), 20);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 399), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 399), 0);


  delete mat; // delete the Matrix

}
//various for one row
TEST(various) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 5, 1);
  int *ptr = (Matrix_at(mat, 0, 0));
  *ptr = 10;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 10);

  int *ptr1 = (Matrix_at(mat, 0, 1));
  *ptr1 = 1;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 1);

  int *ptr2 = (Matrix_at(mat, 0, 2));
  *ptr2 = 100;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 100);

  int *ptr3 = (Matrix_at(mat, 0, 3));
  *ptr3= 3;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 3);

  int *ptr4 = (Matrix_at(mat, 0, 4));
  *ptr4 = 2;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 2);

  ASSERT_EQUAL(Matrix_max(mat), 100);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 4), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 1);

  delete mat;
  
}

//various for one column
TEST(various_row){
  Matrix *mat = new Matrix;

  Matrix_init(mat, 1, 5);
  int *ptr = (Matrix_at(mat, 0, 0));
  *ptr = 1;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);

  int *ptr1 = (Matrix_at(mat, 1, 0));
  *ptr1 = 2;
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 2);

  int *ptr2 = (Matrix_at(mat, 2, 0));
  *ptr2 = 3;
  ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 3);

  int *ptr3 = (Matrix_at(mat, 3, 0));
  *ptr3 = 4;
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 4);

  int *ptr4 = (Matrix_at(mat, 4, 0));
  *ptr4 = 5;
  ASSERT_EQUAL(*Matrix_at(mat, 4, 0), 5);

  ASSERT_EQUAL(Matrix_max(mat), 5);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 0), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 0), 2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 0), 3);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 0), 4);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 4, 0, 0), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, 0), 5);

  delete mat;
}

//negative numbers as values
TEST(negative) {
  Matrix *mat = new Matrix;
  const int value = 0;
  const int width = 2;
  const int height = 2;

  Matrix_init(mat, 2, 2);

  Matrix_fill(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  Matrix_fill_border(mat, -100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), -100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), -100);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), -100);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), -100);

  delete mat;
}

//test where it only fills the border and checking various spots on the border
TEST(border) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 10, 10);
  const int value = 100;
  const int width = 10;
  const int height = 10;

  Matrix_fill_border(mat, value);
  //top row
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 5), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 6), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 7), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 8), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 9), 100);
  //bottom row
  ASSERT_EQUAL(*Matrix_at(mat, 9, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 1), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 2), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 3), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 4), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 5), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 6), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 7), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 8), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 9, 9), 100);
  //first row
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 4, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 5, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 6, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 7, 0), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 8, 0), 100);
  //last row
  ASSERT_EQUAL(*Matrix_at(mat, 1, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 4, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 5, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 6, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 7, 9), 100);
  ASSERT_EQUAL(*Matrix_at(mat, 8, 9), 100);

  Matrix_fill(mat, -100);
  //for loop
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), -100);
    }
  }

  delete mat;
}

TEST(edge_test_max) {
  Matrix *mat = new Matrix;
  const int width = 3;
  const int height = 5;
  const int max_value = 99;
  Matrix_init(mat, width, height);
  for (int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat, row, col) = row * width + col;
    }
  }
  *Matrix_at(mat, 4, 2) = max_value;
  ASSERT_EQUAL(Matrix_max(mat), max_value);
  delete mat;
}

TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1);

  string output_correct = "3 3\n1 1 1 \n1 0 1 \n1 1 1 \n";

  ostringstream ss_output;
  Matrix_print(mat, ss_output);
  ASSERT_EQUAL(ss_output.str(), output_correct);
  delete mat;
}

TEST(three) {
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 3;
  const int value = 27;

  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  Matrix_fill_border(mat, 0);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), value);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 0);

  delete mat;
}

TEST(another_rectangle) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 3);
  ASSERT_EQUAL(Matrix_width(mat), 2);
  ASSERT_EQUAL(Matrix_height(mat), 3);

  Matrix_fill(mat, 100);

  int *ptr = (Matrix_at(mat, 1, 1));
  *ptr = 1;
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 1);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 2), 1);

  delete mat;
}

TEST(final_rectangle) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 2);
  ASSERT_EQUAL(Matrix_width(mat), 3);
  ASSERT_EQUAL(Matrix_height(mat), 2);

  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1);

  int *ptr = (Matrix_at(mat, 0, 2));
  *ptr = 0;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 0);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3),2);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), 0);

  delete mat;
}

TEST(columns) {
  Matrix *mat = new Matrix;
  const int width = 7;
  const int height = 6;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 100);

  *Matrix_at(mat, 0, 0) = -10;
  *Matrix_at(mat, 0, 1) = 1;
  *Matrix_at(mat, 0, 2) = 0;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 1, 7), 2);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 1, 7), 0);

  delete mat;
}





// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
