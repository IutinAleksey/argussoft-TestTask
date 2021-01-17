#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

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
	cout << "            Show existing images" << endl;
	cout << endl;
}

int main()
{
	unordered_map<string, Mat> name_map;
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
					cout << it.first << endl;
				}
			}
			else
			if(command == "ld" || command == "load")
			{
				auto name = get_value(word_list, 1);
				auto filename = get_value(word_list, 2);
				name_map[name] = imread(filename, IMREAD_COLOR);
			}
			else
			if(command == "s" || command == "store")
			{
				auto name = get_value(word_list, 1);
				auto filename = get_value(word_list, 2);
				if(name_map.find(name) != name_map.end())
				{
					imwrite(filename, name_map.at(name));
				}
				else
				{
					cout << "image doesn`t exist" << endl;
				}
			}
			else
			if(command == "blur")
			{
				auto from_name = get_value(word_list, 1);
				auto to_name = get_value(word_list, 2);
				auto size = stoi(get_value(word_list, 3));

				if(name_map.find(from_name) == name_map.end())
				{
					cout << "image doesn`t exist" << endl;
					continue;
				}
				if(size <= 0)
				{
					cout << "size must be greater than 0" << endl;
					continue;
				}

				auto &src = name_map.at(from_name);
				name_map[to_name].create(src.size(), src.type());

				blur(src, name_map[to_name], Size(size, size));
			}
			else
			if(command == "resize")
			{
				auto from_name = get_value(word_list, 1);
				auto to_name = get_value(word_list, 2);
				auto new_width = stoi(get_value(word_list, 3));
				auto new_height = stoi(get_value(word_list, 4));
				if(name_map.find(from_name) == name_map.end())
				{
					cout << "image doesn`t exist" << endl;
					continue;
				}
				if(new_width <= 0 || new_height <= 0)
				{
					cout << "new_width or new_height must be greater than 0" << endl;
					continue;
				}

				resize(name_map.at(from_name), name_map[to_name], Size(new_width, new_height));
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
		}
	}

	return 0;
}
