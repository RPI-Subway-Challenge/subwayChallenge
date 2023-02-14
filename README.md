# NYC Subway Challenge

Code from https://github.com/RPI-Subway-Challenge/subwayChallenge

## Finds fastest path through all 472 NYC subway stations for the [NYC Subway Challenge](https://en.wikipedia.org/wiki/Subway_Challenge).
Uses a greedy alg and a BFS search to find optimal path through representation of New York City subway system. Data provided by MTA & webscraped from Google Maps. Written in C++ and Python. The current apporach is to start at the previous record holder's([Matthew Ahn](https://en.wikipedia.org/wiki/Matthew_Ahn)) start location and time; Far Rockaway-Mott Ave at 2am on a Sunday - there may be a better starting location.


* Compile:
	* Release: g++ *.cpp -O2 -std=c++20 -o main.out
	* Debug: g++ *.cpp -g -std=c++2a -o main.out -Wall
* Run:
	* ./main.out data.txt lineData.txt


## Notes:

* Stations implemented with a matrix representation
* Walkable stations are manually connected with an edge
