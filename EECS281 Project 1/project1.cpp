// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

//  project1.cpp
//  EECS281 Project 1
//
//  Created by Lydia Kim on 1/13/23.
//

#include "project1.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <getopt.h>
#include <stack>
#include "xcode_redirect.hpp"
using namespace std;


class Station {
public:
    //function for command line
    void getMode(int argc, char *argv[]);
    void readData();
    void searching(bool stackMode);
    void backTracing();
    void printOutput(string output, bool solution);

    struct squareCoordinate {
        char squareType;
        bool discovered = false;
        char pred; //where it came from
    };
    
    struct dequeCoordinates {
        uint32_t level = 0;
        uint32_t row = 0;
        uint32_t column = 0;
    };
    
    struct backwards {
        uint32_t level = 0;
        uint32_t row = 0;
        uint32_t column = 0;
        //char type;
    };

    //search container that is either stack or queue
    deque<dequeCoordinates> searchContainer;
    stack<backwards> mapOutput;
    bool stackMode;
    char mode;
    string output = "M";
    string outFormat = "M";
    bool solution = false;
    
private:
    //variables from the command line
    //how many places discovered
    uint32_t numDiscovered = 0;
    //bool list = false;
    uint32_t totalFloors = 0;
    uint32_t size = 0;
    vector<vector<vector< squareCoordinate>>> threeD;
    dequeCoordinates start; //saving the starting coordinates
    backwards end;
    int numModes = 0;
};

//command line
void Station::getMode(int argc, char *argv[]) {
    opterr = false;
    int gotopt = 0;
    int option_index = 0;
    option long_opts[] ={
        { "stack", no_argument, nullptr, 's' },
        { "queue", no_argument, nullptr, 'q' },
        { "output", required_argument, nullptr, 'o' },
        { "help", no_argument, nullptr, 'h' },
        { nullptr, 0, nullptr, '\0' },
    }; //long_options[]
    
    while((gotopt = getopt_long(argc, argv, "sqo:h", long_opts, &option_index)) != -1) {
        switch (gotopt) {
            case 's':
                numModes++;
                stackMode = true;
                break;
            case 'q':
                numModes++;
                stackMode = false;
                break;
            case 'o':{
                output = optarg;
                if (output != "M" && output != "L") {
                    cerr << "Error: Invalid output mode specified \n";
                    exit(1);
                }
                outFormat = mode;
                break;
            } // case o
            case 'h':
                exit(0);
                
            default:
                cerr << "Error: invalid option \n";
                exit(1);
        } //switch ..choice
    } //while
    if (numModes != 1) {
        cerr << "Error: Multiple routing modes specified or No routing mode specified \n";
        exit (1);
    }
}

void Station::readData() {
    //square is the struct each input into the vector
    string comments;
    char first;
    //first read in the mode type (map or list)
    cin >> mode;
    //second read in the number of levels
    cin >> totalFloors;
    //third real in the size of each level
    cin >> size;
    //use the index for going through the 3d vector
    
    if (mode == 'M') {
        //resizing the entire vector
        threeD.resize(totalFloors, vector<vector<squareCoordinate>>(size, vector<squareCoordinate>(size)));
        for (uint32_t i = 0; i < totalFloors; ++i) {
            for (uint32_t j = 0; j < size; ++j) {
                for (uint32_t k = 0; k < size; ++k) {
                    cin >> first;
                    if (first == '/') {
                        getline(cin, comments);
                        --k;
                        continue;
                    }
                    if (first != 'S' && first != 'H' && first != '.' && first != '#' && first != 'E') {
                        cerr << "Invalid map character \n";
                        exit(1);
                    }
                    threeD[i][j][k].squareType = first;
                    if (first == 'S') {
                        start.level = i;
                        start.row = j;
                        start.column = k;
                        threeD[i][j][k].discovered = true;
                        searchContainer.push_back(start);
                    }

                }
                getline(cin, comments);
            }
        }
    } //mode is map
    
    else { //mode == 'L'
        //trying to read in the entire file
        //need to fill in the entire vector with all .
        squareCoordinate period;
        period.squareType = '.';
        period.discovered = false;
        period.pred = ' ';
        char comma;
        uint32_t localLevel = 0;
        uint32_t localRow = 0;
        uint32_t localColumn = 0;
        char localType;
        //filling entire vector with .
        threeD.resize(totalFloors, vector<vector<squareCoordinate>>(size, vector<squareCoordinate>(size, period)));
        
        while (cin >> first) {
            if (first == '/') {
                getline(cin, comments);
            } //line is comment
            else {
                //change
                cin >> localLevel >> comma >> localRow >> comma >> localColumn >> comma >> localType;
                getline(cin, comments);
                if (localLevel > totalFloors - 1) {
                    cerr << "Invalid map level \n";
                    exit(1);
                }
                if (localRow > size - 1) {
                    cerr << "Invalid map row \n";
                    exit(1);
                }
                if (localColumn > size - 1) {
                    cerr << "Invalid map column \n";
                    exit(1);
                }
                threeD[localLevel][localRow][localColumn].squareType = localType;
                
                if (localType == 'S') {
                    start.level = localLevel;
                    start.row = localRow;
                    start.column = localColumn;
                    //marking the start discovered
                    threeD[start.level][start.row][start.column].discovered = true;
                    searchContainer.push_back(start);
                } // saving the start
                if (localType != '.' && localType != '#' && localType != 'S' && localType != 'E' && localType != 'H') {
                    cerr << "Error: Invalid map character \n";
                    exit(1);
                }
                
            } //square information
        } //while statement
    } //mode is list
    
} //readData function


//function for adding vectors to the deque
//this function will be looped through in main so only need to make one object
void Station::searching(bool stackMode) {
    while (searchContainer.empty() ==  false) {
        dequeCoordinates square;
        if (stackMode == false) {
            square = searchContainer.front();
            searchContainer.pop_front();
        } //queue
        else {
            square = searchContainer.back();
            searchContainer.pop_back();
        } //stack
        if (threeD[square.level][square.row][square.column].squareType != 'H') {
            
            //going north
            if (square.row >= 1) {
                if (threeD[square.level][square.row - 1][square.column].discovered == false) {
                    if (threeD[square.level][square.row - 1][square.column].squareType != '#') {
                        dequeCoordinates searching;
                        searching.level = square.level;
                        searching.row = square.row - 1;
                        searching.column = square.column;
                        threeD[square.level][square.row - 1][square.column].discovered = true;
                        searchContainer.push_back(searching);
                        threeD[square.level][square.row - 1][square.column].pred = 'n';
                        if (threeD[searching.level][searching.row][searching.column].squareType == 'H') {
                            solution = true;
                            end.level = searching.level;
                            end.row = searching.row;
                            end.column = searching.column;
                            //end.type = 'n';
                            mapOutput.push(end);

                            break;
                        }
                    }
                }
            } //north
            
            //east
            if (square.column + 1 < size) {
                if (threeD[square.level][square.row][square.column + 1].discovered == false) {
                    if (threeD[square.level][square.row][square.column + 1].squareType != '#') {
                        dequeCoordinates searching;
                        searching.level = square.level;
                        searching.row = square.row;
                        searching.column = square.column + 1;
                        threeD[square.level][square.row][square.column + 1].discovered = true;
                        searchContainer.push_back(searching);
                        threeD[square.level][square.row][square.column + 1].pred = 'e';
                        if (threeD[searching.level][searching.row][searching.column].squareType == 'H') {
                            solution = true;
                            end.level = searching.level;
                            end.row = searching.row;
                            end.column = searching.column;
                            //end.type = 'e';
                            mapOutput.push(end);

                            break;
                        }
                    }
                }
            } //east
            
            //south
            if (square.row + 1 < size) {
                if (threeD[square.level][square.row + 1][square.column].discovered == false) {
                    if (threeD[square.level][square.row + 1][square.column].squareType != '#') {
                        dequeCoordinates searching;
                        searching.level = square.level;
                        searching.row = square.row + 1;
                        searching.column = square.column;
                        threeD[square.level][square.row + 1][square.column].discovered = true;
                        searchContainer.push_back(searching);
                        threeD[square.level][square.row + 1][square.column].pred = 's';
                        if (threeD[searching.level][searching.row][searching.column].squareType == 'H') {
                            solution = true;
                            end.level = searching.level;
                            end.row = searching.row;
                            end.column = searching.column;
                            //end.type = 's';
                            mapOutput.push(end);
                            break;
                        }
                    }
                }
            } // south
            
            //west
            //square.column > 0
            if (square.column >= 1) {
                if (threeD[square.level][square.row][square.column - 1].discovered == false) {
                    if (threeD[square.level][square.row][square.column - 1].squareType != '#') {
                        dequeCoordinates searching;
                        searching.level = square.level;
                        searching.row = square.row;
                        searching.column = square.column - 1;
                        threeD[square.level][square.row][square.column - 1].discovered = true;
                        searchContainer.push_back(searching);
                        threeD[square.level][square.row][square.column - 1].pred = 'w';
                        if (threeD[searching.level][searching.row][searching.column].squareType == 'H') {
                            solution = true;
                            end.level = searching.level;
                            end.row = searching.row;
                            end.column = searching.column;
                            //end.type = 'w';
                            mapOutput.push(end);
                            break;
                        }
                    }
                }
            } // west
            
            //elevator
            if (threeD[square.level][square.row][square.column].squareType == 'E') {
                //going through floor 0 to highest
                for (uint32_t i = 0; i < totalFloors; ++i) {
                    //if elevator and not discovered
                    //pred is the level that is came from
                    if ((threeD[i][square.row][square.column].squareType == 'E') && (threeD[i][square.row][square.column].discovered == false)) {
                        dequeCoordinates searching;
                        searching.level = i;
                        searching.row = square.row;
                        searching.column = square.column;
                        threeD[i][square.row][square.column].discovered = true;
                        searchContainer.push_back(searching);
                        threeD[i][square.row][square.column].pred = static_cast<char>('0' + square.level);
                    } 
                }
            } // if elevator
        } //if it is not a hanger
    } //while deque is not empty

}
//the square is at the top

//it will only enter the backtracing if the solution is found
void Station::backTracing(){
    //currently have the hanger at the bottom of the stack
    bool finished = false;
    while (finished == false) {
        backwards element = mapOutput.top();
        if ((element.level == start.level) && (element.row == start.row) && (element.column == start.column)) {
            mapOutput.push(element);
            finished = true;
            break;
        }
        
        if (threeD[element.level][element.row][element.column].pred == 'n') {
            threeD[element.level][element.row + 1][element.column].squareType = 'n';
            element.row += 1;
            //element.type = 'n';
        }
        
        //- column for e
        else if (threeD[element.level][element.row][element.column].pred == 'e') {
            threeD[element.level][element.row][element.column - 1].squareType = 'e';
            element.column -= 1;
            //element.type = 'e';
        }
        
        //-row for s
        else if (threeD[element.level][element.row][element.column].pred == 's') {
            threeD[element.level][element.row - 1][element.column].squareType = 's';
            element.row -= 1;
            //element.type = 's';
        }
        
        //+column for w
        else if (threeD[element.level][element.row][element.column].pred == 'w') {
            threeD[element.level][element.row][element.column + 1].squareType = 'w';
            element.column += 1;
            //element.type = 'w';
        }
            //set the currents spot to be equal to the previous level
        //else if ()
        //elevator
        else {
            uint32_t prevLevel = static_cast<uint32_t>(threeD[element.level][element.row][element.column].pred - '0');
            char temp = static_cast<char>('0'+element.level);
            threeD[prevLevel][element.row][element.column].squareType = temp;
            //element.type = static_cast<char>('0' + prevLevel);
            element.level = prevLevel;
        }
        mapOutput.push(element);
    }
    
}

void Station::printOutput(string output, bool solution) {
    //the mode of the input can be different than the mode of the output
    if (output == "M") {
        cout << "Start in level " << start.level << ", row " << start.row << ", column " << start.column << '\n';
        for (uint32_t i = 0; i < totalFloors; ++i) {
            cout << "//level " << i << endl;
            for (uint32_t j = 0; j < size; ++j) {
                for (uint32_t k = 0; k < size; ++k) {
                    cout << threeD[i][j][k].squareType;
                }
                cout << '\n';
            }
        }
    } // map mode
    else { //list mode
        if (solution == false) {
            cout << "//path taken" << endl;
        }
        else {
            cout << "//path taken" << endl;
            mapOutput.pop();
            //could be > 0
            while (mapOutput.size() > 1) {
                backwards printing = mapOutput.top();
                if (threeD[printing.level][printing.row][printing.column].squareType =='E') {
                    cout << "(" << printing.level << "," << printing.row << "," << printing.column << "," << threeD[printing.level][printing.row][printing.column].pred << ")" << "\n";
                }
                else {
                    cout << "(" << printing.level << "," << printing.row << "," << printing.column << "," << threeD[printing.level][printing.row][printing.column].squareType << ")" << '\n';
                }
                mapOutput.pop();
            }
        }
    } //list mode
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    Station game;
    game.getMode(argc, argv);
    game.readData();
    game.searching(game.stackMode);
    if (game.solution == true) {
        //if the output mode is map, just print the 3d map squaretype
        if (game.output == "M") { //map mode
            game.backTracing();
            game.printOutput(game.output, game.solution);
        }
        else { //list mode
            game.backTracing();
            game.printOutput(game.output, game.solution);
        }
    }
    else { //no solution found
        game.printOutput(game.output, game.solution);
    }
    return 0;
    
}
