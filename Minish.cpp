// The MINImal SHell
// First let's import everything we need.
// This *should* be platform independent, so no <windows.h> or <unistd.h>.
#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// Now we're done importing, let's define macros that are important for our shell.
#define DEFAULT_DIR "C:/Users/USER" // NOTE: This as you might already realize, is for Windows, so modify to your liking for Linux.

using namespace std;
namespace fs = std::filesystem;


string cmd;

string current_dir = DEFAULT_DIR;

string cmd_val;

string val;

void start();

void get_command(string cmd);

void help();

void cd();

void file();

void cat();

void exit();

int main (int argc, char *argv[]) {
	cout << "MINISH V1\n";
	while (true)
	{
		start();
		cin.ignore();
	}

	return 0;
}

void start()
{
	// This is the start.
	cout << current_dir << "> ";
	cout.flush();
	getline(cin, cmd);
	get_command(cmd);

}
void get_command(string cmd)
{
	size_t FindSpacePos = cmd.find(" "); // Find the space in the command
	cmd_val = cmd.substr(0, FindSpacePos); // Find the command, so we can run corresponding function, or throw an error for an unrecognized command.
	val = cmd.substr(FindSpacePos + 1);
	if (cmd_val == "cd")
	{
		cd();
	} else if (cmd_val == "file")
	{
		file();
	} else if(cmd_val == "cat")
	{
		cat();
	} else if(cmd_val == "help")
	{
		help();
	} else if (cmd_val == "exit")
	{
		exit();
	} else {
		cout << "msh: Command not found\n";
		start();
	}
}

void cd()
{
	// Let's check if the folder exists first.
	bool exists = fs::exists(current_dir + "/" + val); //&& fs::is_directory(current_dir + val);

	if (exists)
	{
		current_dir = current_dir + "/" + val;
	} else {
		cout << "cd: directory not found\n";
	}
	start();
}

void file()
{
	ofstream file(current_dir + "/" + val); // Creates a file in the current directory.
	file.close();
	start();
}

void cat()
{
	ifstream file(current_dir + "/" + val);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			cout << line << endl;
		}
	} else {
		cout << "cat: File not found\n";
		start();
	}
	file.close();
	start();
}

void help()
{
	cout << "The MINImal SHell.\n"
		"Here's a rundown of the recognized commands\n"
		"cd - changes directory.\n"
		"file - creates a new file\n"
		"cat - reads a file\n"
		"help - displays this\n";

	start();
}

void exit()
{
	exit(0);
}
