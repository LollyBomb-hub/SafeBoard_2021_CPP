#include "include/time.hpp"


static chrono::time_point<chrono::high_resolution_clock> begin;
static chrono::time_point<chrono::high_resolution_clock> end;


void start_time()
{
	begin = chrono::high_resolution_clock::now();
	return;
}


void stop_time()
{
	end = chrono::high_resolution_clock::now();
	return;
}


long int get_seconds()
{
	return TIME_CAST(SECONDS_CAST, end - begin).count();
}


std::string get_time_string()
{
	long int milliseconds = get_seconds();
	long int hours = milliseconds / 3600000;
	milliseconds -= hours * 3600000;
	long int minutes = milliseconds / 60000;
	milliseconds -= minutes * 60000;
	long int seconds = milliseconds / 1000;
	milliseconds -= seconds * 1000;
	char buffer[64];
	buffer[63] = '\0';
	sprintf((char*)buffer, "%.2ld:%.2ld:%.2ld:%.2ld", hours, minutes, seconds, milliseconds);
	return std::string((char*)buffer);
}
