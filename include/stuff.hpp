#ifndef __STUFFY__

#define __STUFFY__


#include <algorithm>
#ifdef LINUX
	#include <filesystem>
#else
	#include <__fs/filesystem>
	namespace std::filesystem = std::__fs::filesystem
#endif
#include <iostream>
#include <string>


#define DELIMITER	"======\0"
#define VERSION		"1.0.0b (2021)\0"


bool argument_exists(const char* filename);
std::string get_extension(const char* filename);
std::string get_extension(std::filesystem::path path_object);
void print_help();
void print_report();
void to_lower(std::string& arg);


#endif
