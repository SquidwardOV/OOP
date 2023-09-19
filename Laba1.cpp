Time.h
#include <string>

class Time {
private:
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
public:
	int getHour() const { return int(hour); }
	int getMinute() const { return int(minute); }
	int getSecond() const { return int(second); }
	void setHour(int& hour) { this->hour = hour; }
	void setMinite(int& minute) { this->minute = minute; }
	void setSecond(int& second) { this->second = second; }
	Time();
	Time(const unsigned char hour, const unsigned char minute, const unsigned char second);
	Time(std::string time);
	Time(int second);
	Time(const Time& time);
	int TimeDif(const Time& time);
	void TimeAdd(int second);
	void TimeSub(int second);
	void Show();
	int ToSecond();
	int ToMinute();
	bool TimeComp(const Time& time);
	std::string toString();
};


function.cpp

	
#include "Time.h"
#include <iostream>

Time::Time() {
	this->hour = 0;
	this->minute = 0;
	this->second = 0;
}

Time::Time(const unsigned char hour, const unsigned char minute, const unsigned char second) {
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	if (secIn > 86400) {
		this->hour = 23;
		this->minute = 59;
		this->second = 59;
	}
}

Time::Time(std::string time) {
	if (time.size() < 8) {
		throw;
	}
	hour = (int(time[0]) - 48) * 10 + (int(time[1]) - 48);
	minute = (int(time[3]) - 48) * 10 + (int(time[4]) - 48);
	second = (int(time[6]) - 48) * 10 + (int(time[7]) - 48);
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	if (secIn > 86400) {
		this->hour = 23;
		this->minute = 59;
		this->second = 59;
	}

}

Time::Time(int second) {
	if (second > 86400) {
		this->hour = 23;
		this->minute = 59;
		this->second = 59;
	}
	this->hour = second / 3600;
	second %= 3600;
	this->minute = 0;
	this->second = 0;
	
	while (second >= 60) {
		minute += 1;
		second -= 60;
	}
	this->second = second;
}

Time::Time(const Time& time) {
	this->hour = time.hour;
	this->minute = time.minute;
	this->second = time.second;
}

void Time::TimeAdd(int second) {
	if (second > 86400) {
		second %= 86400;
	}
	int secIn = hour * 3600 + minute * 60 + this->second;
	secIn += second;
	if (secIn >= 86400) {
		secIn %= 86400;
	}
	hour = secIn / 3600;
	minute = (secIn % 3600) / 60;
	this->second = secIn % 60;
}

int Time::TimeDif(const Time& time) {
	int secOut = int(time.hour) * 3600 + int(time.minute) * 60 + int(time.second);
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	return abs(secOut - secIn);
}

void Time::TimeSub(int second) {
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	secIn -= second;
	if (secIn < 0) {
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
	}
	else {
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		while (secIn >= 3600) {
			hour += 1;
			secIn -= 3600;
		}
		while (secIn >= 60) {
			minute += 1;
			secIn -= 60;
		}
		this->second = secIn;
	}
}

int Time::ToSecond() {
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	return secIn;
}
int Time::ToMinute() {
	int minIn = int(this->hour) * 60 + int(this->minute);
	return minIn;
}

bool Time::TimeComp(const Time& time) {
	int secOut = int(time.hour) * 3600 + int(time.minute) * 60 + int(time.second);
	int secIn = int(this->hour) * 3600 + int(this->minute) * 60 + int(this->second);
	if (secIn > secOut) {
		return true;
	}
	else {
		return false;
	}
}

std::string Time::toString() {
	std::string timeString = "";
	if (int(hour) > 9) {
		timeString += std::to_string(int(hour));
	}
	else {
		timeString += '0' + std::to_string(int(hour));
	}
	timeString += ':';
	if (int(minute) > 9) {
		timeString += std::to_string(int(minute));
	}
	else {
		timeString += '0' + std::to_string(int(minute));
	}
	timeString += ':';
	if (int(second) > 9) {
		timeString += std::to_string(int(second));
	}
	else {
		timeString += '0' + std::to_string(int(second));
	}
	return timeString;
}


main.cpp

	
#include "Time.h"
#include <iostream>



int main() {
    Time clocked;
    Time clock2(86399);

    Time clock3(clock2);
    Time clock4("20:00:42");

    clock2.TimeAdd(543);

    std::cout << clock2.toString() << std::endl;

    clock3.TimeSub(450);

  

    clock4.ToSecond();


    clock2.getMinute();

  

}
