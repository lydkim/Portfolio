//  Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
//
//  project4.cpp
//  EECS281 Project 4
//
//  Created by Lydia Kim on 3/31/23.
//

#include "project4.hpp"
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vertex {
    int x;
    int y;
    char terrain; //w, c, l
    //TODO: keep track of water, coast, land
};

struct Prims {
    double minEdgeWeight = numeric_limits<double>::infinity();
    size_t parent;
    bool visited = false;
};

class Poke {
public:
    double totalWeight = 0; //running total
    double estimate = 0; //estimate the remaining branch
    string mode = "";
    vector<Vertex> coordinate;
    vector<Prims> primMST; //MST
    vector<size_t> partialTour; //FASTTSP
    vector<size_t> bestPath; //OPTTSP
    //vector<vector<double>> matrix;
    
    void getMode(int argc, char *argv[]);
    void readData();
    void MSTMode();
    double distance(size_t a, size_t b);
    void FASTTSPMode();
    bool promising(size_t permLength);
    void genPerms(size_t permLength);
    void OPTTSPMode();
    double miniMST(size_t permLength);
};


void Poke::getMode(int argc, char *argv[]) {
    opterr = false;
    int gotopt = 0;
    int option_index = 0;
    option long_opts[] = {
        { "mode", required_argument, nullptr, 'm' },
        { "help", no_argument, nullptr, 'h' },
        { nullptr, 0, nullptr, '\0' },
    }; //long_options[]
    
    while((gotopt = getopt_long(argc, argv, "m:h", long_opts, &option_index)) != -1) {
        switch (gotopt) {
            case 'm':
                mode = optarg;
                if (mode != "MST" && mode != "FASTTSP" && mode != "OPTTSP") {
                    cerr << "Error: Invalid mode \n";
                    exit(1);
                }
                break;
            case 'h':
                exit(0);
            default:
                cout << "Error: command line option\n";
                exit(1);
        } //switch ..choice
    } //while
} //getMode

void Poke::readData() {
    int vertices;
    int xCoordinate;
    int yCoordinate;
    Vertex temp;
    cin >> vertices;
    coordinate.resize(vertices);
    for (int i = 0; i < vertices; ++i) {
        cin >> xCoordinate >> yCoordinate;
        temp.x = xCoordinate;
        temp.y = yCoordinate;
        if ((yCoordinate == 0 && xCoordinate <= 0) || (xCoordinate == 0 && yCoordinate <= 0)) {
            temp.terrain = 'c';
        } // if coast
        else if (xCoordinate < 0 && yCoordinate < 0) {
            temp.terrain = 'w';
        } // else if water
        else {
            temp.terrain = 'l';
        } // else land
        coordinate[i] = temp;
    } //for loop
} //readData

double Poke::distance(size_t a, size_t b) {
    double xTemp = coordinate[a].x - coordinate[b].x;
    double yTemp = coordinate[a].y - coordinate[b].y;
    return sqrt((xTemp * xTemp) + (yTemp * yTemp));
}

void Poke::MSTMode() {
    double dist = 0;
    //double total = 0;
    primMST.resize(coordinate.size());
    primMST[0].minEdgeWeight = 0;

    for (size_t i = 0; i < coordinate.size(); ++i) {
        size_t tempIdx = i;
        double tempMin = numeric_limits<double>::infinity();
        for (size_t j = 0; j < coordinate.size(); ++j) {
            if (!primMST[j].visited && primMST[j].minEdgeWeight < tempMin) {
                tempIdx = j;
                tempMin = primMST[j].minEdgeWeight;
            }
        } //first for j
        
        primMST[tempIdx].visited = true;
        totalWeight += primMST[tempIdx].minEdgeWeight;
        
        for (size_t j = 0; j < primMST.size(); ++j) {
            if (primMST[j].visited) {
                continue;
            }
            if ((coordinate[tempIdx].terrain == 'l' && coordinate[j].terrain == 'w') || (coordinate[tempIdx].terrain == 'w' && coordinate[j].terrain == 'l')) {
                dist = numeric_limits<double>::infinity();
            }
            else {
                dist = distance(tempIdx, j);
            }
            if (dist < primMST[j].minEdgeWeight) {
                primMST[j].parent = tempIdx;
                primMST[j].minEdgeWeight = dist;
            }
        } // second for j
    } //for i
    
    if (totalWeight == numeric_limits<double>::infinity()) {
        cerr << "Cannot construct MST\n";
        exit(1);
    }
} // MSTMode

void Poke::FASTTSPMode() {
    //TSP insertion method
    partialTour.reserve(coordinate.size() + 1);
    partialTour.emplace_back(0);
    partialTour.emplace_back(1);
    partialTour.emplace_back(0);
    //the graph will come back to the original
    totalWeight = distance(0, 1) + distance(1, 0);
    for (size_t i = 2; i < coordinate.size(); ++i) {
        double tempMin = numeric_limits<double>::infinity();
        size_t tempIdx = 0;
        for (size_t j = 0; j < partialTour.size() - 1; ++j) {
            //ik + kj - ij
            double minEdge = distance(partialTour[j], i) + distance(i, partialTour[j + 1]) - distance(partialTour[j], partialTour[j+1]);
            if (tempMin > minEdge) {
                tempIdx = j + 1;
                tempMin = minEdge;
            } // if statement
        } // inner for
        partialTour.insert(partialTour.begin() + tempIdx, i);
        totalWeight += tempMin;
    } //outer for
    partialTour.pop_back();
}

double Poke::miniMST(size_t permLength) {
    double mstWeight = 0;
    double dist = 0;
    
    vector<Prims> miniPrims;
    miniPrims.resize(partialTour.size() - permLength);
    miniPrims[0].minEdgeWeight = 0;
    miniPrims[0].parent = partialTour[permLength];
    
    for (size_t i = 0; i < miniPrims.size(); ++i) {
        size_t tempIdx = i;
        double tempMin = numeric_limits<double>::infinity();
        for (size_t j = 0; j < miniPrims.size(); ++j) {
            if (!miniPrims[j].visited && miniPrims[j].minEdgeWeight < tempMin) {
                tempIdx = j;
                tempMin = miniPrims[j].minEdgeWeight;
            }
        }
        
        miniPrims[tempIdx].visited = true;
        mstWeight += miniPrims[tempIdx].minEdgeWeight;
        
        for (size_t j = 0; j < miniPrims.size(); ++j) {
            if (miniPrims[j].visited) {
                continue;
            }
            dist = distance(partialTour[permLength + j], partialTour[permLength + tempIdx]);
            if (dist < miniPrims[j].minEdgeWeight) {
                miniPrims[j].parent = tempIdx;
                miniPrims[j].minEdgeWeight = dist;
            }
        }
    } // for i
    
    return mstWeight;
}

bool Poke::promising(size_t permLength) {
    if (partialTour.size() - permLength < 5) {
        return true;
    }
    
    double mstWeight = 0;
    
    double closestStart = numeric_limits<double>::infinity();
    double closestEnd = numeric_limits<double>::infinity();
    
    for (size_t i = permLength; i < partialTour.size(); ++i) {
        double tempFront = distance(partialTour[0], partialTour[i]);
        double tempEnd = distance(partialTour[i], partialTour[permLength-1]);
        if (tempFront < closestStart) {
            closestStart = tempFront;
        }
        if (tempEnd < closestEnd) {
            closestEnd = tempEnd;
        }
    }
    
    mstWeight = miniMST(permLength);
    
    if (totalWeight > estimate + mstWeight + closestStart + closestEnd) {
        return true;
    }
    
    return false;
}

void Poke::genPerms(size_t permLength) {
    if (permLength == partialTour.size()) {
        //double closingCost = matrix[partialTour[0]][partialTour[permLength - 1]];
        if (totalWeight > estimate + distance(partialTour[0], partialTour[permLength - 1])) {
            totalWeight = estimate + distance(partialTour[0], partialTour[permLength - 1]);
            bestPath = partialTour;
        }
        return;
    } // if ..complete path
    if (!promising(permLength)) {
        return;
    } // if ..not promising
    
    for (size_t i = permLength; i < partialTour.size(); ++i) {
        swap(partialTour[permLength], partialTour[i]);
        double connectingEdge = distance(partialTour[permLength - 1], partialTour[permLength]);
        estimate += connectingEdge;
        genPerms(permLength + 1);
        estimate -= connectingEdge;
        swap(partialTour[permLength], partialTour[i]);
    } // for ..unpermuted elements
} // genPerms()

void Poke::OPTTSPMode() {
    FASTTSPMode();
    bestPath = partialTour;
    genPerms(1);
}


int main (int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    cout << std::setprecision(2);
    cout << std::fixed;
    Poke pokemon;
    pokemon.getMode(argc, argv);
    pokemon.readData();
    
    if (pokemon.mode == "MST") {
        pokemon.MSTMode();
        cout << pokemon.totalWeight << "\n";
        for (size_t i = 1; i < pokemon.primMST.size(); ++i) {
            if (i < pokemon.primMST[i].parent) {
                cout << i << " " << pokemon.primMST[i].parent << "\n";
            }
            else {
                cout << pokemon.primMST[i].parent << " " << i << "\n";
            }
        }
    }
    else if (pokemon.mode == "FASTTSP") {
        pokemon.FASTTSPMode();
        cout << pokemon.totalWeight << "\n";
        for (auto i : pokemon.partialTour) {
            cout << i << " ";
        }
    }
    else if (pokemon.mode == "OPTTSP") {
        pokemon.OPTTSPMode();
        cout << pokemon.totalWeight << "\n";
        for (auto i : pokemon.bestPath) {
            cout << i << " ";
        }
    }
    
    return 0;
}
