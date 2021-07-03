#include "include/main.hpp"
#include "include/stuff.hpp"
#include "include/time.hpp"


unsigned int errors			= 0;
unsigned int totally_processed		= 0;
unsigned int javascript_detects		= 0;
unsigned int unix_detects		= 0;
unsigned int macOS_detects		= 0;
std::string filename;

// Check Js files

bool check_javascript_file()
{
	std::ifstream file(filename.c_str());
	std::string file_contents;
	while(!file.eof())
	{
		char buffer[32];
		buffer[31] = '\0';
		file.read((char*)buffer, 31);
		file_contents += buffer;
	}
	return std::strstr(file_contents.c_str(), js_mark) != nullptr;
}


bool check_unix_file()
{
	std::ifstream file(filename.c_str());
	std::string file_contents;
	while(!file.eof())
	{
		char buffer[32];
		buffer[31] = '\0';
		file.read((char*)buffer, 31);
		file_contents += buffer;
	}
	return std::strstr(file_contents.c_str(), unix_mark) != nullptr;
}


bool check_macos_file()
{
	std::ifstream file(filename.c_str());
	std::string file_contents;
	while(!file.eof())
	{
		char buffer[65];
		buffer[64] = '\0';
		file.read((char*)buffer, 64);
		file_contents += buffer;
	}
	return std::strstr(file_contents.c_str(), macOS_mark) != nullptr;
}


int main(int argc, char** argv)
{
	if(argc == 1 || argc > 2)
	{
		print_help();
		return 0;
	}
	if(argument_exists((const char*)argv[1]))
	{
		start_time();
		for(auto& directory_entry: std::filesystem::directory_iterator(argv[1]))
		{
			if(std::filesystem::is_regular_file(directory_entry))
			{
				totally_processed++;
				filename = std::string(directory_entry.path().c_str());
				std::string extension = get_extension(filename);
				to_lower(extension);
				if(!std::ifstream(filename))
				{
					errors++;
				}
				else if(check_unix_file())
				{
					unix_detects++;
				}
				else if(check_macos_file())
				{
					macOS_detects++;
				}
				else if(extension == ".js")
				{
					if(check_javascript_file())
					{
						javascript_detects++;
					}
				}
			}
		}
		stop_time();
	}
	else
	{
		std::cout << "Specified( " << argv[1] << " ) folder doesn\'t exist.\n";
		std::cout << "Check arguments.\n";
		return 0;
	}
	print_report();
	return 0;
}
