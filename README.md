NOT YET FINISHED



Finds fastest path through all 472 NYC subway stations for the [NYC Subway Challenge](https://en.wikipedia.org/wiki/Subway_Challenge).

Uses a greedy AI agent to find optimal path through representation of New York subway system. Data provided by MTA & webscraped from google maps. Written in C++ and python.


Should be compiled with g++ and run in a linux terminal as following:

g++ station.cpp line.cpp main.cpp -o main.out

./main.out stationData.txt lineData.txt output.txt



Down with Matthew Ahn.



Data from:

https://data.cityofnewyork.us/Transportation/Subway-Stations/arq3-7z49#Discuss

https://new.mta.info/schedules/subway



Notes:

I have choosen to start at Far Rockaway-Mott Ave at 2am on a Sunday. I just took this from the previous record holder, [Matthew Ahn](https://en.wikipedia.org/wiki/Matthew_Ahn). There may be a better starting point.

In my lineData file S signage has been replaced by S1, S2, or S3 depending on the shuttle line.

Lines indexed 83, 98, 104, 192, 196, 459, 460 and 465 have MTA buses that have been ignored.

There are 4 "TimesSq" stations within a block from eachother with distinct services. They are treated as distinct stations but could be treated as one and just and walked between.
