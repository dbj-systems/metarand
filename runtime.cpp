#include <random>
#include <iostream>

// crt_localtime.cpp
// compile with: /W3
// This program uses _time64 to get the current time
// and then uses localtime64() to convert this time to a structure
// representing the local time. The program converts the result
// from a 24-hour clock to a 12-hour clock and determines the
// proper extension (AM or PM).

#include <stdio.h>
#include <string.h>
#include <time.h>

// Get time as 64-bit integer.
inline const __time64_t get_time_64() {
// __time64_t is actually long long aka _int64
	__time64_t long_time{};
	_time64(&long_time);
	return long_time;
}

// or?

struct my_time {
	inline static const __time64_t time_ = get_time_64() ;
};

extern "C" void test_constexpr_time ()
{
	// Get time as 64-bit integer.
	__time64_t long_time = my_time::time_ ;
   // Convert to local time.
	struct tm *newtime = _localtime64(&long_time); // C4996
	// Note: _localtime64 deprecated; consider _localetime64_s
#ifdef DBJ_WASP_TIME
	constexpr static char am_pm[] = "AM";
	if (newtime->tm_hour > 12)        // Set up extension.
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	if (newtime->tm_hour > 12)        // Convert from 24-hour
		newtime->tm_hour -= 12;        //   to 12-hour clock.
	if (newtime->tm_hour == 0)        // Set hour to 12 if midnight.
		newtime->tm_hour = 12;
	char buff[30];
	asctime_s(buff, sizeof(buff), newtime);
	printf("%.19s %s\n", buff, am_pm);
#else
	char buff[30];
	asctime_s(buff, sizeof(buff), newtime);
	printf("\nLocal time:\t %.19s \n", buff);
#endif
}

// runtime way of doing it
extern "C" void test_std_random_device ()
{
    // Seed with a real random value, if available
    std::random_device rd;
	printf("\nUsing std random device\t%s", typeid(std::random_device).name());

	std::random_device::result_type v1_ = rd();

    // Choose a random mean between 1 and 6
    //std::minstd_rand0 r(3);
    std::ranlux24_base r(3);

	printf("\nUsing std random generator\t%s\n", typeid(std::ranlux24_base).name());

    for(int i=0; i<10; ++i)
		printf("\nrnd val: %lu", r());
}