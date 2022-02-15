//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"
#include "time.h"
#include "assert.h"
#include <fstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// compile:		g++ main.cpp -o main.out
// run:			./main.out data.csv
bool timeUnitTests();
int main(int argc, char* argv[]){
    assert(timeUnitTests());
}

bool timeUnitTests(){
    //create new time objects
    Time t("11:14:30");
    assert(t.getHour() == 11); // check hour
    assert(t.getMin() == 14); // check hour
    assert(t.getMinSec() == 14.5); // check hour
}


/*
Read stations
Make station vec

Read line data
Construct line
Add 






A
1
Schedule
42
Schedule
end

B
3
95



*/