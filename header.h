
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iterator>

using namespace std;

int right_pos;
int middle_pos;
int left_pos;


template<typename K, typename V>
void print_map(unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
      cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

unordered_map<string, int> key={
	{"a",0},
    {"b",1},
    {"c",2},
    {"d",3},
    {"e",4},
    {"f",5},
    {"g",6},
    {"h",7},
    {"i",8},
    {"j",9},
    {"k",10},
    {"l",11},
    {"m",12},
    {"n",13},
    {"o",14},
    {"p",15},
    {"q",16},
    {"r",17},
    {"s",18},
    {"t",19},
    {"u",20},
    {"v",21},
    {"w",22},
    {"x",23},
    {"y",24},
    {"z",25},
    {"0",26},
    {"1",27},
    {"2",28},
    {"3",29},
    {"4",30},
    {"5",31},
    {"6",32},
    {"7",33},
    {"8",34},
    {"9",35}
	};

unordered_map<int, string> rev_key={
		{0,"a"},
    {1,"b"},
    {2,"c"},
    {3,"d"},
    {4,"e"},
    {5,"f"},
    {6,"g"},
    {7,"h"},
    {8,"i"},
    {9,"j"},
    {10,"k"},
    {11,"l"},
    {12,"m"},
    {13,"n"},
    {14,"o"},
    {15,"p"},
    {16,"q"},
    {17,"r"},
    {18,"s"},
    {19,"t"},
    {20,"u"},
    {21,"v"},
    {22,"w"},
    {23,"x"},
    {24,"y"},
    {25,"z"},
    {26,"0"},
    {27,"1"},
    {28,"2"},
    {29,"3"},
    {30,"4"},
    {31,"5"},
    {32,"6"},
    {33,"7"},
    {34,"8"},
    {35,"9"}
	};

string left_rotor []= {"2" , "y", "z", "0", "1", "a", "w", "i", "p", "k", "s", "n", "3", "t", "e", "r", 
"m", "u", "c", "5", "v", "6", "x", "7", "f", "q", "o", "l", "4", "8", "g", "d", "9", "b", "j", "h" };

string middle_rotor []= {"0", "l", "x",	"1", "2", "8",	"h", "b",	"3", "n", "r", "o", "k", "d", "t", "7", "c", 
"6", "p", "i", "v", "j", "4", "a", "u", "w", "m",	"e", "9", "5", "q", "s", "z",	"g", "y", "f"};

string right_rotor []  {"3", "5",	"h", "e", "f", "g", "d", "q", "8", "m",	"2", "k", "l", "j", "n", "s", 
"u", "w", "o", "v",	"r", "x", "z", "c", "i", "9", "t", "7", "b", "p", "a", "0", "1", "y", "6", "4"};

unordered_map<int,string> nw_left_rotor;

unordered_map<int,string> nw_middle_rotor;

unordered_map<int,string> nw_right_rotor;
/////////////////////////////
unordered_map<string,int> rev_nw_left_rotor;

unordered_map<string,int> rev_nw_middle_rotor;

unordered_map<string,int> rev_nw_right_rotor;

void init_rotorI(int left_pos){
  for (int i=0; i<36; i++ ){
    nw_left_rotor[i] = left_rotor[left_pos];
    rev_nw_left_rotor.insert(pair<std::string,int>(left_rotor[left_pos],i));
    left_pos++;

    if (left_pos == 36){
      left_pos = 0;
    }
  }
}


void rotorI(){
  rev_nw_left_rotor.clear();
  string l;
  l = nw_left_rotor.find(35)->second;
  for (int i =0; i <36; i++){
    if (left_rotor[i] == l){
      left_pos = i;
    }
  }
  for (int i=0; i<36; i++ ){
    nw_left_rotor[i] = left_rotor[left_pos];
    rev_nw_left_rotor.insert(pair<std::string,int>(left_rotor[left_pos],i));
    left_pos++;

    if (left_pos == 36){
      left_pos = 0;
    }
  }
  
}

void init_rotorII(int middle_pos){
  for (int i=0; i<36; i++ ){
    nw_middle_rotor[i] = middle_rotor[middle_pos];
    rev_nw_middle_rotor.insert(pair<std::string,int>(middle_rotor[middle_pos],i));
    middle_pos++;

    if (middle_pos == 36){
      middle_pos = 0;
    }
  }

}
void rotorII(){
  rev_nw_middle_rotor.clear();
  string l;
  l = nw_middle_rotor.find(35)->second;
  for (int i =0; i <36; i++){
    if (middle_rotor[i] == l){
      middle_pos = i;
    }
  }
  for (int i=0; i<36; i++ ){
    nw_middle_rotor[i] = middle_rotor[middle_pos];
    rev_nw_middle_rotor.insert(pair<std::string,int>(middle_rotor[middle_pos],i));
    middle_pos++;

    if (middle_pos == 36){
      middle_pos = 0;
    }
  }
}
  

void init_rotorIII(int right_pos){
  for (int i=0; i<36; i++ ){
    nw_right_rotor[i] = right_rotor[right_pos];
    rev_nw_right_rotor.insert(pair<std::string,int>(right_rotor[right_pos],i));
    right_pos++;
    if (right_pos == 36){
      right_pos = 0;
    }
  }
}

void rotorIII(){
  rev_nw_right_rotor.clear();
  string l;
  l = nw_right_rotor.find(35)->second;
  for (int i =0; i <36; i++){
    if (right_rotor[i] == l){
      right_pos = i;
    }
  }
  for (int i=0; i<36; i++ ){
    nw_right_rotor[i] = right_rotor[right_pos];
    rev_nw_right_rotor.insert(pair<std::string,int>(right_rotor[right_pos], i));
    right_pos++;

    if (right_pos == 36){
      right_pos = 0;
    }
  }
}