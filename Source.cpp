#include <iostream>
#include <ios>
#include <direct.h>
#include <experimental/filesystem>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>




const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string Temp{""};
	std::vector<std::string> Output;

	for (auto n : s)
	{
		if (n != c) Temp += n; else
			if (n == c && Temp != "") { Output.push_back(Temp); Temp = ""; }
	}
	if (Temp != "") Output.push_back(Temp);

	return Output;
}

std::ifstream::pos_type filesize(std::string Filename)
{
	std::ifstream inFile(Filename, std::ifstream::ate | std::ifstream::binary);
	return inFile.tellg();
}


int main()
{
	while (true)
	{


		std::string choise;
		std::cout << "Type archive to create an archive or split to split the files.  ";
		std::cin >> choise;
		std::cout << std::endl;
		if (choise == "archive")
		{




			//Takes the data from the files and combines it and throws an int on the start.
			std::ifstream inputData("Save.txt", std::ios::in);


			//This file contains the names of the files to open
			std::string FileNames;

			std::getline(inputData, FileNames);
			inputData.close();

			//Then a good idea would be to split the data
			std::vector<std::string> FileNameData = explode(FileNames, *",");


			int size = FileNameData.size();
			std::ofstream f("Data.ESCA", std::ios_base::binary | std::ios_base::out);
			f.clear();
			f.write(reinterpret_cast<const char*>((&size)), sizeof(int));
			for (size_t i = 0; i < FileNameData.size(); i++)
			{
				f.write(reinterpret_cast<const char*>((&(filesize((std::to_string(std::stoi(FileNameData[i], nullptr, 10) + 1)) + ".csd")))), sizeof(int));
			}
			f.close();



			std::ofstream of_a("Data.esca", std::ios_base::binary | std::ios_base::app);
			for (size_t i = 0; i < FileNameData.size(); i++)
			{


				std::ifstream if_b((std::to_string(std::stoi(FileNameData[i], nullptr, 10) + 1)) + ".csd", std::ios_base::binary);


				of_a.seekp(0, std::ios_base::end);
				of_a << if_b.rdbuf();
			}
			break;
		}
		if (choise == "split")
		{



			break;
		}
		else
		{
			std::cout << "Sorry, that is not a valid command." << std::endl;
		}
	}
	return 0;
}
