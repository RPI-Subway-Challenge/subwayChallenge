# NYC Subway Challenge - NOT YET FINISHED

## Finds fastest path through all 472 NYC subway stations for the [NYC Subway Challenge](https://en.wikipedia.org/wiki/Subway_Challenge).
Uses A* to find optimal path through representation of New York City subway system. Data provided by MTA & webscraped from Google Maps. Written in C++ and Python. The current apporach is to start at the previous record holder's([Matthew Ahn](https://en.wikipedia.org/wiki/Matthew_Ahn)) start location and time; Far Rockaway-Mott Ave at 2am on a Sunday - there may be a better starting location.


* Compile:
	* Release: g++ *.cpp -O2 -std=c++20 -o main.out
	* Debug: g++ *.cpp -g -std=c++20 -o main.out -Wall
* Run:
	* ./main.out data.txt lineData.txt


## Notes:

* There are 4 "TimesSq" stations within a block from eachother with distinct services. They are treated as distinct stations but could be treated as one and just and walked between.
* In my lineData file S signage has been replaced by S1, S2, or S3 depending on the shuttle line.

* Lines indexed 83, 98, 104, 192, 196, 459, 460 and 465 have MTA buses that have been ignored.



## Data from:

https://data.cityofnewyork.us/Transportation/Subway-Stations/arq3-7z49#Discuss

https://new.mta.info/schedules/subway
