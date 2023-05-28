// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.

//global variables
const Pixel red = {255, 0, 0};
const Pixel green = {0, 255, 0};
const Pixel blue = {0, 0, 255};
const Pixel black = {0, 0, 0};
const Pixel white = {255, 255, 255};
const Pixel gray = {100, 100, 100};
const Pixel agua = {101, 151, 183};
const Pixel brown = {124, 63, 63};
const Pixel purple = {163, 73, 164};


TEST(test_print_basic) {
  Image *img = new Image; 

  Image_init(img, 2, 2);

  ASSERT_EQUAL(Image_width(img), 2);
  ASSERT_EQUAL(Image_height(img), 2);
  
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  Pixel first = Image_get_pixel(img, 0, 0);
  ASSERT_EQUAL(first.r, 255);
  ASSERT_EQUAL(first.g, 0);
  ASSERT_EQUAL(first.b, 0);
  Pixel second = Image_get_pixel(img, 0, 1);
  ASSERT_EQUAL(second.r, 0);
  ASSERT_EQUAL(second.g, 255);
  ASSERT_EQUAL(second.b, 0);
  Pixel third = Image_get_pixel(img, 1, 0);
  ASSERT_EQUAL(third.r, 0);
  ASSERT_EQUAL(third.g, 0);
  ASSERT_EQUAL(third.b, 255);
  Pixel fourth = Image_get_pixel(img, 1, 1);
  ASSERT_EQUAL(fourth.r, 255);
  ASSERT_EQUAL(fourth.g, 255);
  ASSERT_EQUAL(fourth.b, 255);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  // always prints P3, new line, width and heigh separated by whitespace, 255
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//using only one color
// Sets various pixels in a 3x3 Image and checks
// that Image_print produces the correct output.
TEST(one_color) {
  Image *img = new Image;

  Image_init(img, 3, 3);

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 3);

  Image_set_pixel(img, 0, 0, agua);
  Image_set_pixel(img, 0, 1, agua);
  Image_set_pixel(img, 0, 2, agua);
  Image_set_pixel(img, 1, 0, agua);
  Image_set_pixel(img, 1, 1, agua);
  Image_set_pixel(img, 1, 2, agua);
  Image_set_pixel(img, 2, 0, agua);
  Image_set_pixel(img, 2, 1, agua);
  Image_set_pixel(img, 2, 2, agua);

  Pixel first = Image_get_pixel(img, 0, 0);
  ASSERT_EQUAL(first.r, 101);
  ASSERT_EQUAL(first.g, 151);
  ASSERT_EQUAL(first.b, 183);
  Pixel second = Image_get_pixel(img, 0, 1);
  ASSERT_EQUAL(second.r, 101);
  ASSERT_EQUAL(second.g, 151);
  ASSERT_EQUAL(second.b, 183);
  Pixel third = Image_get_pixel(img, 0, 2);
  ASSERT_EQUAL(third.r, 101);
  ASSERT_EQUAL(third.g, 151);
  ASSERT_EQUAL(third.b, 183);
  Pixel fourth = Image_get_pixel(img, 1, 0);
  ASSERT_EQUAL(fourth.r, 101);
  ASSERT_EQUAL(fourth.g, 151);
  ASSERT_EQUAL(fourth.b, 183);
  Pixel fifth = Image_get_pixel(img, 1, 1);
  ASSERT_EQUAL(fifth.r, 101);
  ASSERT_EQUAL(fifth.g, 151);
  ASSERT_EQUAL(fifth.b, 183);
  Pixel sixth = Image_get_pixel(img, 1, 2);
  ASSERT_EQUAL(sixth.r, 101);
  ASSERT_EQUAL(sixth.g, 151);
  ASSERT_EQUAL(sixth.b, 183);
  Pixel seventh = Image_get_pixel(img, 2, 0);
  ASSERT_EQUAL(seventh.r, 101);
  ASSERT_EQUAL(seventh.g, 151);
  ASSERT_EQUAL(seventh.b, 183);
  Pixel eigth = Image_get_pixel(img, 2, 1);
  ASSERT_EQUAL(eigth.r, 101);
  ASSERT_EQUAL(eigth.g, 151);
  ASSERT_EQUAL(eigth.b, 183);
  Pixel ninth = Image_get_pixel(img, 2, 2);
  ASSERT_EQUAL(ninth.r, 101);
  ASSERT_EQUAL(ninth.g, 151);
  ASSERT_EQUAL(ninth.b, 183);

  ostringstream p;
  Image_print(img, p);

  ostringstream correct;

  correct << "P3\n3 3\n255\n";
  correct << "101 151 183 101 151 183 101 151 183 \n";
  correct << "101 151 183 101 151 183 101 151 183 \n";
  correct << "101 151 183 101 151 183 101 151 183 \n";
  ASSERT_EQUAL(p.str(), correct.str());

  delete img;
}

//one box
// Sets one pixel in a 1x1 Image and checks
// that Image_print produces the correct output.
TEST(one_box) {
  Image *img = new Image;

  Image_init(img, 1, 1);
  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);

  Image_set_pixel(img, 0, 0, white);

  Pixel one = Image_get_pixel(img, 0, 0);
  ASSERT_EQUAL(one.r, 255);
  ASSERT_EQUAL(one.g, 255);
  ASSERT_EQUAL(one.b, 255);
  
  Pixel only = Image_get_pixel(img, 0, 0);
  ASSERT_EQUAL(only.r, 255);
  ASSERT_EQUAL(only.g, 255);
  ASSERT_EQUAL(only.b, 255);

  ostringstream q;
  Image_print(img, q);

  ostringstream correct;

  correct << "P3\n1 1\n255\n";
  correct << "255 255 255 \n";
  ASSERT_EQUAL(q.str(), correct.str());

  delete img;
}

TEST(colorful) {
  Image *img = new Image;

  Image_init(img, 3, 3);
  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 3);
  //row 0
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 0, 2, blue);
  //row 1
  Image_set_pixel(img, 1, 0, white);
  Image_set_pixel(img, 1, 1, black);
  Image_set_pixel(img, 1, 2, purple);
  //row 2
  Image_set_pixel(img, 2, 0, brown);
  Image_set_pixel(img, 2, 1, agua);
  Image_set_pixel(img, 2, 2, gray);

  ostringstream p;
  Image_print(img, p);

  ostringstream correct;

  correct << "P3\n3 3\n255\n";
  correct << "255 0 0 0 255 0 0 0 255 \n";
  correct << "255 255 255 0 0 0 163 73 164 \n";
  correct << "124 63 63 101 151 183 100 100 100 \n";
  ASSERT_EQUAL(p.str(), correct.str());

  delete img;
}

TEST(rectangle) {
  Image *img = new Image;

  Image_init(img, 3, 5);
  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 5);
  Image_fill(img, brown);

  ostringstream q;
  Image_print(img, q);

  ostringstream correct;
  correct << "P3\n3 5\n255\n";
  correct << "124 63 63 124 63 63 124 63 63 \n";
  correct << "124 63 63 124 63 63 124 63 63 \n";
  correct << "124 63 63 124 63 63 124 63 63 \n";
  correct << "124 63 63 124 63 63 124 63 63 \n";
  correct << "124 63 63 124 63 63 124 63 63 \n";
  ASSERT_EQUAL(q.str(), correct.str());

  delete img;
}

TEST(test_image_basic) {
  string input = "P3\n2 2\n255\n255 0 0 0 255 0 \n";
  input += "0 0 255 255 255 255 \n";

  istringstream ss_input(input);
  Image *img = new Image;
  Image_init(img, ss_input);

  ASSERT_EQUAL(Image_width(img), 2);
  Pixel red = {255, 0, 0};
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  delete img;
}

  
// }
// equal pixel function

//equal image function

// using dog, crabster, and horses ppm

// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
