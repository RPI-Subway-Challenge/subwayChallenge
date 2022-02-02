NOT YET FINISHED



Finds fastest path through all 472 NYC subway stations for the [NYC Subway Challenge](https://en.wikipedia.org/wiki/Subway_Challenge).

Uses a semi-greedy AI agent to find optimal path through representation of New York City subway system. Data provided by MTA & webscraped from Google Maps. Written in C++ and Python.


Should be compiled with g++ and run in a linux terminal as following:

g++ main.cpp -o main.out

./main.out data.csv



Down with Matthew Ahn.



Data from:

https://data.cityofnewyork.us/Transportation/Subway-Stations/arq3-7z49#Discuss

https://new.mta.info/schedules/subway



Notes:

I have choosen to start at Far Rockaway-Mott Ave at 2am on a Sunday. I just took this from the previous record holder, [Matthew Ahn](https://en.wikipedia.org/wiki/Matthew_Ahn). There may be a better starting point.

In my lineData file S signage has been replaced by S1, S2, or S3 depending on the shuttle line.

Lines indexed 83, 98, 104, 192, 196, 459, 460 and 465 have MTA buses that have been ignored.

There are 4 "TimesSq" stations within a block from eachother with distinct services. They are treated as distinct stations but could be treated as one and just and walked between.
