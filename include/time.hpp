#ifndef __TIME_MEASUREMENT__

#define __TIME_MEASUREMENT__

#include <chrono>
#include <string>


#define chrono			std::chrono
#define HOURS_CAST		chrono::hours
#define MINUTES_CAST		chrono::minutes
#define SECONDS_CAST		chrono::milliseconds


#define TIME_CAST(type, value)	chrono::duration_cast<type>(value)


void start_time();
void stop_time();


long int get_seconds();
std::string get_time_string();


#endif
