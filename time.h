#ifndef time_h_
#define time_h_

#include <string>
#include <iostream>
#include <chrono>


class Time{
public:

	// constructors
	Time() = default;
    Time(const std::string& input);
	Time(std::chrono::weekday day, std::chrono::duration<unsigned> timeOfDay);

	// getters
	constexpr auto getDay()			const {return day;}
	constexpr auto getTimeOfDay() 	const {return timeOfDay;}
	constexpr auto dayCode() 		const {return day.c_encoding();}
	constexpr bool isWeekday()		const {return !isWeekend();}
	constexpr bool isWeekend()		const {
		return day == std::chrono::Sunday || day == std::chrono::Saturday;
	}

	// operators
	bool operator==(const Time &) const = default;

private:
	std::chrono::weekday day;
	std::chrono::duration<unsigned> timeOfDay;
};

// operator+ and operator- treats one of the arguments as a duration
// (both being time points does not make sense).
Time operator+(const Time &, const Time &);
Time operator-(const Time &, const Time &);
bool operator>(const Time &, const Time &);
bool operator<(const Time &, const Time &);

#endif