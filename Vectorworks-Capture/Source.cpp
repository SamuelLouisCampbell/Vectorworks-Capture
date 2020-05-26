/*MIT License

Copyright(c)[2020][Samuel Louis Campbell]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>


std::fstream file;
std::vector<std::string> data;

int main()
{

	std::string fileName;
	std::string line;
	int headerCount = 0;
	bool countHeaders = true;
	bool fileRead_OK = false;
	std::cout << "Enter file name (+ path) for conversion >>> ";

	while (!fileRead_OK)
	{
		std::getline(std::cin, fileName);
		file.open(fileName);
		if (file.is_open())
		{
			fileRead_OK = true;
			std::cout << std::endl << "File opened successfully\n" << std::endl;
			while (file.good())
			{
				while (getline(file, line))
				{
					//std::cout << line << '\n';
					std::stringstream ss(line);
					while (getline(ss, line, '	'))
					{
						data.push_back(line);
						if (countHeaders)
						{
							headerCount++;
						}
					}
					countHeaders = false;
				}

			}
			file.close();
			std::cout << "Read file successfully" << std::endl;
		}
		else
		{
			std::cout << "Did not open file!" << std::endl << "Try again?" << std::endl;
		}
	}


	if (fileRead_OK)
	{

		std::string x_loc("X Location");
		std::string y_loc("Y Location");
		std::string z_loc("Z Location");

		auto result_x_Loc = std::find(std::begin(data), std::end(data), x_loc);
		auto result_y_Loc = std::find(std::begin(data), std::end(data), y_loc);
		auto result_z_Loc = std::find(std::begin(data), std::end(data), z_loc);

		unsigned int x = result_x_Loc - data.begin();
		unsigned int y = result_y_Loc - data.begin();
		unsigned int z = result_z_Loc - data.begin();

		std::cout << "Converted X coordinates >>>" << std::endl;
		for (unsigned int i = x + headerCount; i < data.size(); i += headerCount)
		{
			float temp = std::stoi(data[i]) / 1000.0f;
			data[i] = std::to_string(temp);
			std::cout << data[i] << std::endl;

		}
		std::cout << "Converted Y coordinates >>>" << std::endl;
		for (unsigned int i = y + headerCount; i < data.size(); i += headerCount)
		{
			float temp = std::stoi(data[i]) / 1000.0f;
			data[i] = std::to_string(temp);
			std::cout << data[i] << std::endl;

		}
		std::cout << "Converted Z coordinates >>>" << std::endl;
		for (unsigned int i = z + headerCount; i < data.size(); i += headerCount)
		{
			float temp = std::stoi(data[i]) / 1000.0f;
			data[i] = std::to_string(temp);
			std::cout << data[i] << std::endl;

		}
		//setup output file
		std::string extension = ("_Converted.txt");
		std::ofstream out(fileName + extension);

		int k = 0;
		int sizer = 0;
		if (headerCount > 0)
		{
			sizer = data.size() / headerCount;
		}
		else
		{
			return 666;
		}


		for (unsigned int i = 0; i < data.size() / headerCount; i++)
		{
			for (int j = 0; j < headerCount; j++, k++)
			{
				out << data[k] << '	';
			}
			out << '\n';
		}

		out.close();

	}

	std::cout << "Press Any Key To EXIT";
	std::cin.get();
	std::cin.get();

	return 0;

}
