#ifdef LINUX
	#include <filesystem>
#else
	#include <__fs/filesystem>
	namespace std::filesystem = std::__fs::filesystem;
#endif

#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <signal.h>


#define SERVICE_PID_FILE	"SafeBoardScanner/pid"
#define SERVICE_DATA_FILE	"SafeBoardScanner/target"
#define SERVICE_REPORT_FILE	"SafeBoardScanner/report"


bool argument_exists(const char* arg)
{
	return std::filesystem::exists(std::filesystem::path(arg));
}


void write_argument(const char* target)
{
	if(argument_exists(SERVICE_PID_FILE) == false)
		return;
	std::ofstream out(SERVICE_DATA_FILE);
	out << target << ' ' << getpid();
	out.close();
	return;
}


void send_signal(pid_t pid)
{
	kill(pid, SIGUSR1);
	return;
}


pid_t get_service_pid()
{
	if(argument_exists(SERVICE_PID_FILE) == false)
		return -1;
	int pid;
	std::ifstream in(SERVICE_PID_FILE);
	in >> pid;
	in.close();
	return (pid_t)pid;
}


void signal_handler(int signal)
{
	if(signal == SIGUSR1)
	{
		std::ifstream in(SERVICE_REPORT_FILE);
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		std::string contents(size, ' ');
		in.seekg(0);
		in.read(&contents[0], size);
		in.close();
		std::cout << contents.c_str() << '\n';
		exit(0);
	}
	return;
}


int main(int argc, char** argv)
{
	if(argc == 1 || argc > 2)
		return 0;
	chdir(getenv("HOME"));
	pid_t pid = get_service_pid();
	write_argument(argv[1]);
	send_signal(pid);
	signal(SIGUSR1, signal_handler);
	for(;;)
		pause();
	return 0;
}
