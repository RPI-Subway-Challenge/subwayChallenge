# NYC Subway Challenge - NOT YET FINISHED

## Finds fastest path through all 472 NYC subway stations for the [NYC Subway Challenge](https://en.wikipedia.org/wiki/Subway_Challenge).
Uses A* to find optimal path through representation of New York City subway system. Data provided by MTA & webscraped from Google Maps. Written in C++ and Python. The current apporach is to start at the previous record holder's([Matthew Ahn](https://en.wikipedia.org/wiki/Matthew_Ahn)) start location and time; Far Rockaway-Mott Ave at 2am on a Sunday - there may be a better starting location.


* Compile:
	* Download dependency: Boost (https://www.boost.org)
	* If you are on Windows, you may need to install a build system to be a cmake generator (see list of generators https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html). Ninja recommended due to its speed.
	* Configure
		* for debug: cmake -Bbuild -DBoost_ROOT={YOUR BOOST ROOT DIRECTORY}
		* for release: cmake -Bbuild -DBoost_ROOT={YOUR BOOST ROOT DIRECTORY} -DCMAKE_BUILD_TYPE=Release
	* Build: cmake --build build -j

	* Note: -DBoost_ROOT is only required for the first time you configure, unless you delete the build folder. This argument is also not needed if Boost_ROOT is added to CMAKE_PREFIX_PATH or the environment variable.

* Run:
	* ./main data.txt lineData.txt


## Notes:

* There are 4 "TimesSq" stations within a block from eachother with distinct services. They are treated as distinct stations but could be treated as one and just and walked between.
* In my lineData file S signage has been replaced by S1, S2, or S3 depending on the shuttle line.

* Lines indexed 83, 98, 104, 192, 196, 459, 460 and 465 have MTA buses that have been ignored.



## Data from:

https://data.cityofnewyork.us/Transportation/Subway-Stations/arq3-7z49#Discuss

https://new.mta.info/schedules/subway
