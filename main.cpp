//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"
#include "time.h"
#include "assert.h"
#include <fstream>
// #include <istream>
#include <string>
// #include <vector>
#include <iostream>
#include <sstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// compile:		g++ main.cpp -o main.out
// run:			./main.out data.csv

std::vector<Station> stations;
int main(int argc, char* argv[]) {

    // check for 4 arguments
    if (argc != 2) {
        std::cerr << "You provided " << argc << "arguments intead of 2.\n";
        exit(1);
    }


    // Read in the data via a .txt file
    // 	Reading in from a CSV is garbage if you ever want to use commas anywhere else
    //	So we will be using a raw text file copy and pasted from the master CSV
    std::fstream file;
    file.open(argv[1], std::ios::in);


    int id = 0;
    if (file.is_open()) {
        // This string will hold each entire line
        std::string timetable;
        while (getline(file, timetable)) {

            // Convert the whole line to a stream so we can use getline()
            std::stringstream ss(timetable);

            std::string stationName;
            std::string longitude;
            std::string latitude;

            // Getline will get parts of a string based on char seperators
            getline(ss, stationName, ',');
            getline(ss, longitude, ',');
            getline(ss, latitude, ',');

            // Erase extra garbage from our floats
            longitude.erase(0, 2);
            latitude.erase(0, 1);
            latitude.erase(latitude.size() - 2);

            // Print out all of our information
            std::cout << stationName << "\n";
            std::cout << longitude << "\n";
            std::cout << latitude << "\n";



            stations.push_back(Station(id, stationName,std::stod(longitude), std::stod(latitude)));
            id++;
        }
        file.close();
    }

    for(unsigned int i = 0; i < stations.size(); i++){
        std::cout <<std::endl<< stations[i];
    }
    std::cout << "COMPLETE\n";
    return 0;
}