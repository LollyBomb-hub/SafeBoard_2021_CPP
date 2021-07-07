#include "include/main.hpp"
#include "include/stuff.hpp"
#include "include/time.hpp"


#ifdef DAEMON

	#include <assert.h>
	#include <signal.h>
	#include <sys/wait.h>
	#include <sys/resource.h>
	#include <sys/stat.h>
	#include <unistd.h>

	void signal_handler(int signum)
	{
		if(signum == SIGUSR1)
		{
			int from_pid;
			std::string folder = read_argument(from_pid);
			process_folder(folder.c_str());
			kill(from_pid, SIGUSR1);
		}
		return;
	}

#endif


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


void process_folder(const char* folder_name)
{
	if(argument_exists(folder_name))
	{
		start_time();
		for(auto& directory_entry: std::filesystem::directory_iterator(folder_name))
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
		#ifndef DAEMON
			std::cout << "Specified( " << folder_name << " ) folder doesn\'t exist.\n";
			std::cout << "Check arguments.\n";
		#else
			save_error(folder_name);
		#endif
		return;
	}
	#ifndef DAEMON
		print_report();
	#else
		save_report();
	#endif
	clear_variables();
	return;
}

#ifndef DAEMON
int main(int argc, char** argv)
{
	if(argc == 1 || argc > 2)
	{
		print_help();
		return 0;
	}
	process_folder(argv[1]);
#else
int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
		return -1;
	if(pid != 0)
	{
		exit(0);
	}
	setsid();
	umask(0);
	chdir(getenv("HOME"));
	write_pid((int)getpid());
	struct rlimit flim;
	getrlimit(RLIMIT_NOFILE, &flim);
	for(unsigned int fd = 0; fd < flim.rlim_max; fd++)
		close(fd);
	(void)signal(SIGUSR1, signal_handler);
	for(;;)
		pause();
#endif
	return 0;
}
