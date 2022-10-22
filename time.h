#ifndef time_h_
#define time_h_

#include <string>
#include <iostream>


class Time{
public:

	// default constructor
	Time() = default;

	// constructor
	Time(unsigned inputDay, unsigned inputHour, double inputMin);

    // string constructor
    Time(const std::string& inputDay, const std::string& inputHour, const std::string& inputMin);
    Time(const std::string& input);

	// setters
	void setDay(unsigned int inputDay)		{day = inputDay;}
    void setHour(unsigned int inputHour)	{hour = inputHour;}
    void setMin(double inputMin)			{min = inputMin;}

	// getters
	unsigned int getDay()	const {return day;}
    unsigned int getHour()	const {return hour;}
    unsigned int getMin()	const {return (int)min;}
    double getMinSec() 		const {return min;}
	bool isWeekday()		const {return (day <= 4);}
	bool isWeekend()		const {return !(day > 4);}		

	// operators
	bool operator==(const Time& xTime) const;

private:
	unsigned int day{};	// 0-6 representing Sun-Sat	
	unsigned int hour{};	// 24 hour format
    double min{};
};

// operators
Time operator+(const Time &, const Time &);
Time operator-(const Time &, const Time &);
bool operator>(const Time &, const Time &);
bool operator<(const Time &, const Time &);

#endif