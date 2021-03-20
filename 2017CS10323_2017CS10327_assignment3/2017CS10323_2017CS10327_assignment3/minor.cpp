//#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <boost/algorithm/string.hpp>
using namespace std;

int cpi = 0;
int PC = 0;

int line_nu = 0;

// 32 32-bits register
vector<int32_t> registers;
vector<int> line_countt;
map<string, int> countt;
int memory[1048576] = {0};
// memset(memory, 0, sizeof(memory));

struct lines
{
	string instruction;
	vector<string> arguements;
};

vector<lines> assembly_program_storage;

bool split_inst(string line, unordered_map<string, int> ins_check)
{
	boost::trim_left(line);
	boost::trim_right(line);
	vector<string> arg;
	string ar1 = "";
	bool flag = true;
	struct lines l;
	vector<string> argss;
	if (line == "\n" || line == "\0")
	{
		l.instruction = "";
		assembly_program_storage.push_back(l);
		return true;
	}
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ',')
		{
			arg.push_back(ar1);
			ar1 = "";
		}
		else if ((line[i] == ' ') && flag)
		{
			// ar1.push_back(line[i]);
			flag = false;
			l.instruction = ar1;
			ar1 = "";
		}
		else if (line[i] != ' ')
			ar1.push_back(line[i]);
	}
	arg.push_back(ar1);
	l.arguements = arg;
	if (ins_check.find(l.instruction) == ins_check.end())
	{
		std::cout << "Invalid Instruction at line : " << line_nu << '\n';
		cout << "Invalid-instruction : " << l.instruction << endl;
		return false;
	}
	if (ins_check[l.instruction] != l.arguements.size())
	{
		cout << "Error: Invalid no of Arguement :-" << l.instruction << "-required " << ins_check[l.instruction] << " arguement provided " << l.arguements.size() << " arguement " << endl;
		return false;
	}

	assembly_program_storage.push_back(l);
	return true;
	// return arg;
}
bool empty(std::ifstream &pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

void print_updates(int cpi_value, int registerr_num)
{
	cout << "current clock cycle = " << cpi_value + 1;
	cout << ", updated value of register " << registerr_num;
	cout << ": hex = ";
	cout << std::hex << registers[registerr_num];
	cout << ", int = ";
	cout << dec << registers[registerr_num] << endl;
}

int main(int argc, char **argv)
{

	for (int i = 0; i < 32; i++)
	{
		registers.push_back((int32_t)0);
	}

	unordered_map<string, int> ins_check;

	ins_check["add"] = 3;
	ins_check["sub"] = 3;
	ins_check["mul"] = 3;
	ins_check["beq"] = 3;
	ins_check["bne"] = 3;
	ins_check["slt"] = 3;
	ins_check["j"] = 1;
	ins_check["lw"] = 2;
	ins_check["sw"] = 2;
	ins_check["addi"] = 3;
	ins_check["END"] = 1;
	//ins_check[""] = 0;
	// ins_check[""]=0;
	string myText;
	ifstream MyReadFile(argv[1]);
	// ifstream MyReadFile("/home/anilu/Documents/216/col216_ass3/2017CS10323_2017CS10327_assignment3/2017CS10323_2017CS10327_assignment3/testcase2.txt");
	if (!MyReadFile)
	{
		cerr << "Error File not found : " << argv[1] << '\n';
		return 0;
	}
	if (empty(MyReadFile))
	{
		cerr << "Error Empty file" << '\n';
		return 0;
	}
	int lno = 0;
	try
	{
		/* code */
		bool error = false;
		while (getline(MyReadFile, myText))
		{

			// if(myText=="\0" || myText == "\n") continue;
			line_nu++;
			if (!split_inst(myText, ins_check))
			{
				error = true;
			}
			// struct lines l;
			// vector<string> argss;
			// string delimiter = " ";
			// int pos = 0;
			// std::string token;
			// int c = 0;

			// while ((pos = myText.find(delimiter)) != std::string::npos)
			// {
			// 	token = myText.substr(0, pos);
			// 	if (c == 0)
			// 	{
			// 		l.instruction = token;
			// 	}
			// 	else
			// 	{
			// 		argss.push_back(token);
			// 	}
			// 	myText.erase(0, pos + delimiter.length());
			// 	c += 1;
			// }
			// argss.push_back(myText);
			// l.arguements = argss;
			// assembly_program_storage.push_back(l);
		}
		MyReadFile.close();
		if (error)
		{
			cout << "Invalid Format Please use proper formatted file" << endl;
			return 0;
		}

		for (int i = 0; i < assembly_program_storage.size() - 1; i++)
		{
			line_countt.push_back(0);
		}

		while (assembly_program_storage[PC].instruction != "END")
		{
			countt[assembly_program_storage[PC].instruction]++;
			lno++;
			line_countt[PC]++;
			// cout<<assembly_program_storage[PC].instruction<<" "<<assembly_program_storage[PC].arguements[0]<<'\n';
			if (assembly_program_storage[PC].instruction == "")
			{
				PC++;
				continue;
			}
			if (assembly_program_storage[PC].instruction == "lw")
			{
				if (assembly_program_storage[PC].arguements[1] == "$zero")
				{
					registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = 0;
					print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				}
				else
				{
					// cout<<stol(assembly_program_storage[PC].arguements[1]<<endl;
					if (assembly_program_storage[PC].arguements[1][0] == '$')
					{
						registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[1].substr(1))];
					}
					else
					{
						cout << stol(assembly_program_storage[PC].arguements[1]) << endl;
						registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = memory[stol(assembly_program_storage[PC].arguements[1])];
					}
					// memo[stol(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[1].substr(1))];
					print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				}
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "sw")
			{
				// cout<<stol(assembly_program_storage[PC].arguements[1]<<endl;
				// registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[0].substr(1))];
				if (assembly_program_storage[PC].arguements[1][0] == '$')
				{
					registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[0].substr(1))];
				}
				else
				{
					cout << stol(assembly_program_storage[PC].arguements[1]) << endl;
					memory[stol(assembly_program_storage[PC].arguements[1])] = registers[stol(assembly_program_storage[PC].arguements[0].substr(1))];
				}
				print_updates(cpi, stol(assembly_program_storage[PC].arguements[1].substr(1)));
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "addi")
			{
				registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] + stol(assembly_program_storage[PC].arguements[2]);
				print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "add")
			{
				registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] + registers[stol(assembly_program_storage[PC].arguements[2].substr(1))];
				print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "sub")
			{
				registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] - registers[stol(assembly_program_storage[PC].arguements[2].substr(1))];
				print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "mul")
			{
				registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = (registers[stol(assembly_program_storage[PC].arguements[1].substr(1))]) * (registers[stol(assembly_program_storage[PC].arguements[2].substr(1))]);
				print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "beq")
			{
				if (registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] == registers[stol(assembly_program_storage[PC].arguements[1].substr(1))])
				{
					cout << "current clock cycle = " << cpi + 1 << ", value of register " << stol(assembly_program_storage[PC].arguements[0].substr(1)) << " equals value of register " << stol(assembly_program_storage[PC].arguements[1].substr(1)) << ", hence jumping to line " << stol(assembly_program_storage[PC].arguements[2]) << endl;
					PC = stol(assembly_program_storage[PC].arguements[2]) - 1;
				}
				else
				{
					cout << "current clock cycle = " << cpi + 1 << ", value of register " << stol(assembly_program_storage[PC].arguements[0].substr(1)) << " is not equal to value of register " << stol(assembly_program_storage[PC].arguements[1].substr(1)) << endl;
					PC++;
				}
			}
			else if (assembly_program_storage[PC].instruction == "j")
			{
				cout << "current clock cycle = " << cpi + 1 << ", jumping to the line " << stol(assembly_program_storage[PC].arguements[0]) << endl;
				PC = stol(assembly_program_storage[PC].arguements[0]) - 1;
			}
			else if (assembly_program_storage[PC].instruction == "bne")
			{
				if (registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] != registers[stol(assembly_program_storage[PC].arguements[1].substr(1))])
				{
					cout << "current clock cycle = " << cpi + 1 << ", value of register " << stol(assembly_program_storage[PC].arguements[0].substr(1)) << " not equals value of register " << stol(assembly_program_storage[PC].arguements[1].substr(1)) << ", hence jumping to line " << stol(assembly_program_storage[PC].arguements[2]) << endl;
					PC = stol(assembly_program_storage[PC].arguements[2]) - 1;
				}
				else
				{
					cout << "current clock cycle = " << cpi + 1 << ", value of register " << stol(assembly_program_storage[PC].arguements[0].substr(1)) << " is equal to value of register " << stol(assembly_program_storage[PC].arguements[1].substr(1)) << endl;
					PC++;
				}
			}
			else if (assembly_program_storage[PC].instruction == "slt")
			{
				if (registers[stol(assembly_program_storage[PC].arguements[1].substr(1))] < registers[stol(assembly_program_storage[PC].arguements[2].substr(1))])
				{
					registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = 1;
					print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				}
				else
				{
					registers[stol(assembly_program_storage[PC].arguements[0].substr(1))] = 0;
					print_updates(cpi, stol(assembly_program_storage[PC].arguements[0].substr(1)));
				}
				PC++;
			}
			// else if (assembly_program_storage[PC].instruction == ""){
			// 	//continue;
			// }
			else
			{
				cout << "Invalid instruction : " << assembly_program_storage[PC].instruction;
				for (string a : assembly_program_storage[PC].arguements)
				{
					cout << " " << a << " ";
				}
				cout << endl;
			}
			cpi++;
		}
	}
	catch (std::exception e)
	{
		std::cout << "Invalid Instruction at line : " << lno << '\n';
		cout << "Invalid instruction : " << assembly_program_storage[PC].instruction;
		for (string a : assembly_program_storage[PC].arguements)
		{
			cout << " " << a << " ";
		}
		cout << endl;
		return 0;
	}

	cout << "***********************************************" << endl;
	cout << "Final values of Registers-" << endl;

	for (int i = 0; i < 32; i++)
	{
		cout << "value of register ";
		cout << dec << i;
		cout << ": hex=";
		cout << std::hex << registers[i];
		cout << ", int=";
		cout << dec << registers[i] << endl;
	}
	cout << "***********************************************" << endl;
	cout << "Total clock cycles = ";
	cout << std::dec << cpi << endl;
	cout << "***********************************************" << endl;
	cout << "number of executions instruction wise -" << endl;
	map<string, int>::iterator itr;
	for (itr = countt.begin(); itr != countt.end(); ++itr)
	{
		if (itr->first != "")
			cout << '\t' << itr->first << '\t' << itr->second << '\n';
	}
	cout << "***********************************************" << endl;
	cout << "number of executions line wise -" << endl;

	for (int i = 0; i < assembly_program_storage.size() - 1; i++)
	{
		cout << "line " << i + 1 << ": ";
		cout << line_countt[i] << " times" << endl;
	}
	cout << "memory segment updated during executions ************" << endl;
	for (int i = 0; i < 1048576; ++i)
	{
		// cout<<memory[i]<<endl;
		if (memory[i] != 0)
		{
			cout << dec << i << " " << i + 3 << " " << hex << memory[i] << endl;
		}
	}
	// delete(memory);
}
