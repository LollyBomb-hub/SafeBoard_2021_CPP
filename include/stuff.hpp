#ifndef __STUFFY__

#define __STUFFY__


#include <algorithm>
#ifdef LINUX
	#include <filesystem>
#else
	#include <__fs/filesystem>
	namespace std::filesystem = std::__fs::filesystem
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVICE_FOLDER 		"SafeBoardScanner/"
#define SERVICE_PID_FILE	"SafeBoardScanner/pid"
#define SERVICE_DATA_FILE	"SafeBoardScanner/target"
#define SERVICE_REPORT_FILE	"SafeBoardScanner/report"

#define DELIMITER		"======\0"
#define VERSION			"1.0.0b (2021)\0"


bool argument_exists(const char* filename);
std::string get_extension(const char* filename);
std::string get_extension(std::filesystem::path path_object);
std::string read_argument(int& from_pid);
void write_pid(int pid);
void print_help();
void print_report();
void save_report();
void save_error(const char* error_folder);
void to_lower(std::string& arg);
void clear_variables();


#endif
