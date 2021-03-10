
#include <string> 
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int cpi;
int PC=0;


// 32 32-bits register
vector<int32_t> registers;


struct lines{
	string instruction;
	vector<string> arguements;
};

int main(int argc,char** argv){
	for(int i=0;i<32;i++){
		registers.push_back((int32_t)0);
	}

	vector<lines> assembly_program_storage;

	string myText;
	ifstream MyReadFile(argv[1]);
	while (getline (MyReadFile, myText)) {
		struct lines l;
		vector<string> argss;
		string delimiter=" ";
		int pos = 0;
		std::string token;
		int c=0;
		while ((pos = myText.find(delimiter)) != std::string::npos) {
    		token = myText.substr(0, pos);
    		if(c==0){
    			l.instruction=token;
    		}
    		else{
    			argss.push_back(token);
    		}
    		myText.erase(0, pos + delimiter.length());
    		c+=1;
		}
		argss.push_back(myText);
		l.arguements=argss;
		assembly_program_storage.push_back(l);
	}
	MyReadFile.close();

	while(PC!=assembly_program_storage.size()){
		if(assembly_program_storage[PC].instruction=="lw"){
			if(assembly_program_storage[PC].arguements[1]=="$zero"){
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))]=0;
			}
			else{
				registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))]=registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))];
			}
		}
		else if(assembly_program_storage[PC].instruction=="addi"){
			registers[stoi(assembly_program_storage[PC].arguements[0].substr(1))]=registers[stoi(assembly_program_storage[PC].arguements[1].substr(1))] + stoi(assembly_program_storage[PC].arguements[2]);
		}
		PC++;
	}
	
	for(int i=0;i<32;i++){
		cout << "value of register ";
		cout << i;
		cout << "= ";
		cout << registers[i]<< endl;
	}
}
