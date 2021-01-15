#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string get_value(const vector<string> &value_list, unsigned int pos)
{
	if(pos >= value_list.size())
	{
		throw invalid_argument("Can not get value");
	}
	return value_list.at(pos);;
}

void print_help()
{
	cout << "[load | ld] <name> <filename>" << endl;
	cout << "            Load image in JPG format" << endl;
	cout << "            <name> - image name, by name you have access from other command" << endl;
	cout << "            <filename> - file name to loading" << endl;
	cout << endl;
	cout << "[store | s] <name> <filename>" << endl;
	cout << "            Store image in JPG format" << endl;
	cout << "            <name> - image name" << endl;
	cout << "            <filename> - file name to storing" << endl;
	cout << endl;
	cout << "blur <from_name> <to_name> <size>" << endl;
	cout << "            Anti-aliasing the image" << endl;
	cout << "            <from_name> - image name" << endl;
	cout << "            <to_name> - image name" << endl;
	cout << "            <size> - anti-aliasing area size" << endl;
	cout << endl;
	cout << "resize <from_name> <to_name> <new_width> <new_height>" << endl;
	cout << "            Change image size" << endl;
	cout << "            <from_name> - image name" << endl;
	cout << "            <to_name> - image name" << endl;
	cout << "            <new_width> - new width" << endl;
	cout << "            <new_height> - new height" << endl;
	cout << endl;
	cout << "[help | h]" << endl;
	cout << "            Show this text" << endl;
	cout << endl;
	cout << "[exit | quit | q]" << endl;
	cout << "            Stop commands interpretation and exit from program" << endl;
	cout << endl;
	cout << "ls" << endl;
	cout << "            Show image name to file name mapping" << endl;
	cout << endl;
}

int main()
{
	unordered_map<string, string> name_map;
	vector<string> exit_command{"exit", "quit", "q"};

	string line;
	vector<string> word_list;

	cout << "Test task" << endl;
	while(true)
	{
		cout << "> ";
		getline(cin, line);
		istringstream input(line);
		word_list.clear();
		for (string word; getline(input, word, ' '); ) {
			if(!word.empty())
			{
				word_list.push_back(word);
			}
		}

		try
		{
			auto command = get_value(word_list, 0);

			if(find(begin(exit_command), end(exit_command), command) != end(exit_command))
			{
				cout << "See you ;)" << endl;
				break;
			}
			else
			if(command == "ls")
			{
				for(const auto &it: name_map)
				{
					cout << "name: " << it.first << " file name: " << it.second << endl;
				}
			}
			else
			if(command == "ld" || command == "load")
			{
				cout << "Load command" << endl;
				auto name = get_value(word_list, 1);
				auto filename = get_value(word_list, 2);
				name_map[name] = filename;
			}
			else
			if(command == "s" || command == "store")
			{
				cout << "Store command" << endl;
				auto name = get_value(word_list, 1);
				auto filename = get_value(word_list, 2);
				name_map[name] = filename;
			}
			else
			if(command == "blur")
			{
				cout << "Blur command" << endl;
				auto from_name = get_value(word_list, 1);
				auto to_name = get_value(word_list, 2);
				auto size = stoi(get_value(word_list, 3));
			}
			else
			if(command == "resize")
			{
				cout << "Resize command" << endl;
				auto from_name = get_value(word_list, 1);
				auto to_name = get_value(word_list, 2);
				auto new_width = stoi(get_value(word_list, 3));
				auto new_height = stoi(get_value(word_list, 4));
			}
			else
			if(command == "h" || command == "help")
			{
				print_help();
			}
			else
			{
				print_help();
			}
		}
		catch(const exception & e)
		{
			cout << e.what() << endl;
			print_help();
		}
	}

	return 0;
}
