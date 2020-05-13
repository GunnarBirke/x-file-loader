#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;


void next_token_text(std::ifstream& in, int& line_count)
{
	std::string read_so_far;
	char next = 0;
	in.get(next);

	while(std::isspace(next))
	{
		if (next == '\n')
		{
			++line_count;
		}

		in.get(next);
	}

	if (std::isalpha(next))
	{
		read_so_far.push_back(next);
		in.get(next);

		while(std::isalpha(next))
		{
			read_so_far.push_back(next);
			in.get(next);
		}

		//std::cout << read_so_far << std::endl;
		return; // got string
	}
	else if (std::isdigit(next) || next == '-')
	{
		read_so_far.push_back(next);
		in.get(next);

		while (std::isdigit(next))
		{
			read_so_far.push_back(next);
			in.get(next);
		}

		if (next == '.')
		{
			read_so_far.push_back(next);
			in.get(next);;

			while (std::isdigit(next))
			{
				read_so_far.push_back(next);
				in.get(next);
			}

			return; // got floating point number
		}

		return; // got integer
	}
	else if (next == '<')
	{
		read_so_far.resize(32);
		char uuid[32];
		in.readsome(uuid, 36);

		in.get(next);

		if (next != '>')
		{
			std::cout << "wrong uuid format" << std::endl;
		}
		else
		{
			std::copy(uuid, uuid + 32, read_so_far.begin());
			//std::cout << read_so_far << std::endl;
			return;
		}
	}
	else if (next == '"')
	{
		in.get(next);

		while (next != '"')
		{
			read_so_far.push_back(next);
			in.get(next);
		}

		return;
	}

	switch (next)
	{
	case '(':
		return;
	case ')':
		return;
	case '{':
		return;
	case '}':
		return;
	case ']':
		return;
	case '[':
		return;
	case ',':
		return;
	case ';':
		return;
	case '\0':
		return;
	default:
		std::cout << "Unknown token   " << next << "   at line " << line_count << std::endl;
	}
}

void next_token_binary()
{

}

int main()
{
	std::ifstream in("trinity.x", std::ios::in | std::ios::binary);
	char first[4] = { 0, 0, 0, 0};
	char second[4] = { 0, 0, 0, 0};
	char third[4] = { 0, 0, 0, 0};
	char fourth[4] = { 0, 0, 0, 0};
	in.read(first, 4);
	in.read(second, 4);
	in.read(third, 4);
	in.read(fourth, 4);

	int line_count = 0;

	if (third[0] == 't' && third[1] == 'x' && third[2] == 't')
	{
		while(!in.eof())
		{
			next_token_text(in, line_count);
		}
	}

	return 0;
}
