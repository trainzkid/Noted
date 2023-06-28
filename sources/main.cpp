#include <chrono>
#include <iostream>
#include <format>
#include <stdlib.h>
#include <termcolor/termcolor.hpp>
#include <filesystem>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <fstream>
#include <limits>
#include <sstream>
#include <note.h>

int main(int argc,char* argv[],char* env[]) {
	std::unordered_map<std::string,std::string> envVars;
	for(char** envp = env;*envp!=0;envp++) {		// see https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c
		std::string element = *envp;
		envVars[element.substr(0,element.find("="))] = element.substr(element.find("=")+1,element.length());
	}
	const std::vector<std::string_view> args(argv,argv+argc);

	//for(const auto& [key, value] : envVars)
	//	std::cout<<"["<<key<<"] = "<<value<<std::endl;

	const auto start = std::chrono::zoned_time{std::chrono::current_zone(),std::chrono::system_clock::now()}.get_local_time();
	const auto date = std::format("{:%m-%d-%Y %H%M}",start);		// see https://hackingcpp.com/cpp/libs/fmt.html
#ifdef _WIN32
	system("CLS");
#elif defined(__unix__)
	system("clear");
#endif
	std::cout<<termcolor::green<<date<<termcolor::reset<<std::endl;
	const std::filesystem::path notesDir = "Notes";
	if(!std::filesystem::exists(notesDir)) {
		std::filesystem::create_directory(notesDir);
		std::clog<<"Created folder called 'Notes'"<<std::endl;
	} else
		std::clog<<"'Notes' folder already exists... Continuing"<<std::endl;
	std::cout<<"Enter your notes, and hit <ENTER> for a new line."<<std::endl
		<<"Type 'q' or 'exit' and <ENTER> to quit"<<std::endl;
	
	std::filesystem::path notesFilename = notesDir/(envVars["USER"]+" Notes - "+date+".txt");
	std::ofstream notesFile(notesFilename);
	notesFile<<"("<<std::format("{:%m-%d-%Y}",start)<<")"<<std::endl;

	while(true) {
		Noted::Note note{};
		std::cout<<"Enter your note: ";
		std::getline(std::cin,note.contents);
		if(note.contents.compare("q")==0||note.contents.compare("exit")==0)
			break;
		notesFile<<std::format("{:%I:%M %p}",std::chrono::zoned_time{std::chrono::current_zone(),note.created_at}.get_local_time())<<" CST - "<<note.contents<<std::endl;		// using %Z in std::format with a local_time causes std::format to throw a std::format_error, see https://en.cppreference.com/w/cpp/chrono/local_t/formatter
	}

	const auto end = std::chrono::zoned_time{std::chrono::current_zone(),std::chrono::system_clock::now()}.get_local_time();
	const auto duration = end-start;
	notesFile<<"\n\n"<<"=============== End of Notes! ==============="<<"\n\n"
		<<"Start time: "<<std::format("{:%m-%d-%Y %I:%M %p}",start)<<"\n"<<"End time: "<<std::format("{:%m-%d-%Y %I:%M %p}",end)
		<<"\n\n"<<"Duration is "<<std::chrono::duration_cast<std::chrono::hours>(duration).count()<<" hours, "
		<<std::chrono::duration_cast<std::chrono::minutes>(duration).count()<<" minutes"<<std::endl;
	std::cout<<"Notes stored at "<<notesFilename<<std::endl;

	return 0;
}
