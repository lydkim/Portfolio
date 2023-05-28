// Project UID af1f95f547e44c8ea88730dfb185559d

#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Image.h"
#include "Matrix.h"
#include "processing.h"

using namespace std;


int main(int argc, char *argv[]) {
    string input = argv[1];
    string output = argv[2];
    int width = atoi(argv[3]);
    int height;
    Image *img = new Image;
    

    ifstream fin(input);
    ofstream fout(output);

    Image_init(img, fin);

    //checking arguments
    if (argc < 4 || argc > 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
    }
    //checking width
    int original_width = Image_width(img);
    if (width < 0 || width > original_width) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
    }
    //height 
    int original_height = Image_height(img);
    if (argc == 5) {
        height = atoi(argv[4]);
    }
    else { // argc == 4
        height = Image_height(img);
    }
    if (height < 0 || height > original_height) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
    }

    if (!fin.is_open()) {
        cout << "Error opening file: " << input << endl;
        return 1;
    }
    if (!fout.is_open()) {
        cout << "Error opening file: " << output << endl;
        return 1;
    }
    //input seam carve
    //output print image
    seam_carve(img, width, height);

    Image_print(img, fout);
    
    fin.close();
    fout.close();
    delete img;
}