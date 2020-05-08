//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"

// constructor
Hashtable::Hashtable(int startDay, int startTime){
	day = startDay;
	time = startTime;
	size = 1000;
	occupancy = 0;
	maxProbe = 0;
	duration = 0;
	bestDuration = 2130;

	std::vector<Station> tempTable (size);
	table = tempTable;
}




// hash function
int Hashtable::hash(std::string &inputName){
	int hash;
	int probeCount = 0;

	for(int i = 0; i != inputName.size(); i++){
		hash = hash + int(inputName[i]);
	}

	// linear probing to insert
	while(table[hash].getName() != "NONE"){
		if(hash == size-1){
			hash = 0;
		}
		else{
			hash++;
		}
		probeCount++;
	}

	if(probeCount > maxProbe){probeCount == maxProbe;}

	return hash;
}




// find if station in table if so return hash
int Hashtable::findHash(std::string &inputName){
	int hash1 = 0;
	int probeCount = 0;	

	// linear prob till find station or probeMax hit
	while(table[hash1].getName() != inputName && probeCount != maxProbe){
		if(hash1 == size){
			hash1 = 0;
		}else{
			hash1++;
		}
		probeCount++;
	}

	// if not found return -1
	if(probeCount == probeCount){
		return -1;
	}

	// if found return hash
	return hash1;
}



// add station at hash index
void Hashtable::addStation(int inputHash, Station &inputStation){
		table[inputHash] = inputStation;
}



// recursive path finding algorithm
void Hashtable::findPath(Station* ptr, int visted){
	// base case
	if( (time >= ptr->getHours(day).first && time < ptr->getHours(day).second ) || duration > bestDuration ){			// end if station is closed
		return;
	}
}



// time addition operator to deal with base 60 and 24
//operator +~