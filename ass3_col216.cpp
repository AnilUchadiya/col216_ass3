
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int cpi = 0;
int PC = 0;

// 32 32-bits register
vector<int32_t> registers;

struct lines
{
	string instruction;
	vector<string> arguements;
};

vector<lines> assembly_program_storage;

void split_inst(string line)
{
	vector<string> arg;
	string ar1 = "";
	bool flag = true;
	struct lines l;
	vector<string> argss;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ',')
		{
			arg.push_back(ar1);
			ar1 = "";
		}
		else if ((line[i] == ' ') && flag)
		{
			ar1.push_back(line[i]);
			flag = false;
			l.instruction = ar1;
			ar1 = "";
		}
		else if (line[i] != ' ')
			ar1.push_back(line[i]);
	}
	arg.push_back(ar1);
	l.arguements = arg;
	assembly_program_storage.push_back(l);
	// return arg;
}

int main(int argc, char **argv)
{
	for (int i = 0; i < 32; i++)
	{
		registers.push_back((int32_t)0);
	}

	string myText;
	ifstream MyReadFile(argv[1]);
	if (!MyReadFile)
	{
		cerr << "Error File not found" << '\n';
		return 0;
	}
	int lno = 0;
	try
	{
		/* code */
		while (getline(MyReadFile, myText))
		{
			struct lines l;
			vector<string> argss;
			string delimiter = " ";
			int pos = 0;
			std::string token;
			int c = 0;

			while ((pos = myText.find(delimiter)) != std::string::npos)
			{
				token = myText.substr(0, pos);
				if (c == 0)
				{
					l.instruction = token;
				}
				else
				{
					argss.push_back(token);
				}
				myText.erase(0, pos + delimiter.length());
				c += 1;
			}
			argss.push_back(myText);
			l.arguements = argss;
			assembly_program_storage.push_back(l);
		}
		MyReadFile.close();
	

		while (assembly_program_storage[PC].instruction != "END")
		{	
			lno++;
			if (assembly_program_storage[PC].instruction == "lw")
			{
				if (assembly_program_storage[PC].arguements[1] == "$zero")
				{
					registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = 0;
				}
				else
				{
					registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))];
				}
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "sw")
			{
				registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] = registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))];
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "addi")
			{
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] + stoi(assembly_program_storage[PC].arguements[2]);
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "add")
			{
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] + registers[stoi(assembly_program_storage[PC].arguements[2].substr(1))];
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "sub")
			{
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] - registers[stoi(assembly_program_storage[PC].arguements[2].substr(1))];
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "mult")
			{
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = (registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))]) * (registers[stoi(assembly_program_storage[PC].arguements[2].substr(1))]);
				PC++;
			}
			else if (assembly_program_storage[PC].instruction == "beq")
			{
				if (registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] == registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))])
				{
					PC = stoi(assembly_program_storage[PC].arguements[2]) - 1;
				}
				else
				{
					PC++;
				}
			}
			else if (assembly_program_storage[PC].instruction == "j")
			{
				PC = stoi(assembly_program_storage[PC].arguements[0]) - 1;
			}
			else if (assembly_program_storage[PC].instruction == "bne")
			{
				if (registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] != registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))])
				{
					PC = stoi(assembly_program_storage[PC].arguements[2]) - 1;
				}
				else
				{
					PC++;
				}
			}
			else if (assembly_program_storage[PC].instruction == "slt")
			{
				if (registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] < registers[stoi(assembly_program_storage[PC].arguements[2].substr(1))])
				{
					registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = 1;
				}
				else
				{
					registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))] = 0;
				}
				PC++;
			}
			cpi++;
		}

	}
	catch (std::exception e)
	{
		std::cout << "Invalid Instruction at line : " << lno << '\n';
		return 0;
	}

	for (int i = 0; i < 32; i++)
	{
		cout << "value of register ";
		cout << i;
		cout << "= ";
		cout << std::hex << registers[i] << endl;
	}
	cout << "CPI = ";
	cout << std::dec << cpi << endl;
}
