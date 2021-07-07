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


void clear_variables()
{
	errors = 0;
	totally_processed = 0;
	javascript_detects = 0;
	unix_detects = 0;
	macOS_detects = 0;
	return;
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


void save_report()
{
	if(argument_exists(SERVICE_FOLDER) == false)
		std::filesystem::create_directory(SERVICE_FOLDER);
	std::ofstream out(SERVICE_REPORT_FILE);
	out << DELIMITER << " Scan result " << DELIMITER << '\n';
	out << "Processed files: " << totally_processed << '\n';
	out << "JS detects: " << javascript_detects << '\n';
	out << "Unix detects: " << unix_detects << '\n';
	out << "macOS detects: " << macOS_detects << '\n';
	out << "Errors: " << errors << '\n';
	out << "Execution time: " << get_time_string() << '\n';
	out << DELIMITER << DELIMITER << "=" << DELIMITER << DELIMITER << '\n';
	out.close();
	return;
}


void save_error(const char* error_folder)
{
	if(argument_exists(SERVICE_FOLDER) == false)
		std::filesystem::create_directory(SERVICE_FOLDER);
	std::ofstream out(SERVICE_REPORT_FILE);
	out << "Specified( " << error_folder << " ) folder doesn\'t exist.\n";
	out << "Check arguments.\n";
	out.close();
	return;
}


void write_pid(int pid)
{
	if(argument_exists(SERVICE_FOLDER) == false)
		mkdir(SERVICE_FOLDER, 0777);
	std::ofstream out(SERVICE_PID_FILE);
	out << pid;
	out.close();
	int check;
	std::ifstream in(SERVICE_PID_FILE);
	in >> check;
	in.close();
	std::cout << pid << ' ' << check << '\n';
	return;
}


std::string read_argument(int& from_pid)
{
	if(argument_exists(SERVICE_DATA_FILE))
	{
		std::string result;
		std::ifstream input(SERVICE_DATA_FILE);
		input >> result >> from_pid;
		input.close();
		return result;
	}
	return NULL;
}
