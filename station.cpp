//																	D O W N    W I T H    M A T T H E W    A H N

Station::Station(std::string inputName, int inputHash, std::list<char> inputLines, std::vector<std::pair<int,int>> inputHours, std::list<Routes> inputRoutes){
	name = inputName;
	lines = inputLines;
	hours = inputHours;
	Routes = inputRoutes;
}
