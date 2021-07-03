#include "include/main.hpp"
#include "include/stuff.hpp"
#include "include/time.hpp"


extern unsigned int errors;
extern unsigned int javascript_detects;
extern unsigned int macOS_detects;
extern unsigned int totally_processed;
extern unsigned int unix_detects;

// Stuffy help function

void print_help()
{
	std::cout << '\n';
	std::cout << "Scan utility, designed by Pesterev Artem\n";
	std::cout << "Version: " << VERSION << '\n';
	std::cout << "Usage: ./scan_util directory\n";
	std::cout << "Supported \'suspicious\' files:\n";
	std::cout << "\t* Js\n";
	std::cout << "\t* Unix shell-codes\n";
	std::cout << "\t* macOS shell-codes\n";
	std::cout << '\n';
	return;
}

// Stuffy to lower converter

void to_lower(std::string& arg)
{
	std::transform(arg.begin(), arg.end(), arg.begin(), [](char c){ return std::tolower(c); });
	return;
}

// Stuffy get extension function

std::string get_extension(const char* filename)
{
	return std::filesystem::path(filename).extension();
}

std::string get_extension(std::filesystem::path path_object)
{
	return path_object.extension();
}

// Stuffy existence check

bool argument_exists(const char* filename)
{
	return std::filesystem::exists(std::filesystem::path(filename));
}


void print_report()
{
	std::cout << DELIMITER << " Scan result " << DELIMITER << '\n';
	std::cout << "Processed files: " << totally_processed << '\n';
	std::cout << "JS detects: " << javascript_detects << '\n';
	std::cout << "Unix detects: " << unix_detects << '\n';
	std::cout << "macOS detects: " << macOS_detects << '\n';
	std::cout << "Errors: " << errors << '\n';
	std::cout << "Execution time: " << get_time_string() << '\n';
	std::cout << DELIMITER << DELIMITER << "=" << DELIMITER << DELIMITER << '\n';
	return;
}
