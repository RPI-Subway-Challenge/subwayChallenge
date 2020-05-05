//																	D O W N    W I T H    M A T T H E W    A H N

Hashtable::Hashtable(int startDay, int startTime){
	day = startDay;
	time = startTime;
	size = 1000;
	occupancy = 0;
	duration = 0;
	bestDuration = 2130;

	std::std::vector<Station> tempTable (size);
	table = tempTable;
}





int Hashtable::hash(*Station inputStation){





	return 0;
}






void Hashtable::findPath(*Station ptr, int visted){
	// base case
	if( (time >= ptr->getHours(day).first() && time < ptr->getHours(day).second() ) || duration > ){			// end if station is closed

	}
}




operator +~