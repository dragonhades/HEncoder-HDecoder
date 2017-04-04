#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <bitset>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
using namespace std;

#include "tools.h"

struct Tree;
struct Node;
struct Ascii;

string read_bits(const char* filename){
  string bitstring;
  ifstream file(filename, ios::binary);
  char c;
  while(file.get(c)){
    for (int i = 7; i >= 0; i--) {
      if(int((c >> i) & 1)==1) bitstring += "1";
      else bitstring += "0";
    }
  }
  return bitstring;
}

char decode(Tree &t, vector<char> &input,int &count){
  int inp;
  auto ptr = make_shared<Node>(t.list[0]);
  while(1){
    if(ptr->left==nullptr&&ptr->right==nullptr){
      return (char) ptr->c;
    }
    if(input.empty()) throw "EMPTY";
    count++;
    inp = input[0];
    input.erase(input.begin());
    if(inp=='0'){
      ptr = ptr->left;
    } else {
      ptr = ptr->right;
    }
  }
  throw "EMPTY";
}

int main(int argc, char* argv[]){
  
  if(argc<2){
    cerr<<"Usage: ./HDecode Filename";
    return 0;
  }

  //http://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
  cerr<<"Enter password:"<<endl;
  cerr<<"WARNING: Wrong password will get you unreadable messy code."<<endl;
  string enter;
  getline(cin, enter);
  setSeed(enter);

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  char inp;
  Ascii ascii1;
  Ascii ascii2;
  vector<char> input;
  int acc = 128;
  int count = 0;
  string str = read_bits(argv[1]);
  istringstream iss(str);
  while(iss>>inp){
    input.emplace_back(inp);
  }

  int bits=0;
  while(!input.empty()){
    Tree t(ascii1);
    if(count==0){
      random_shuffle(t.list.begin(),t.list.end());
    }
    t.merge_least();
    if(count==1) acc = 128;
    for(register int i = 0; i<acc; i++){
      char c;
      try {
	c = decode(t,input,bits);
	if(i==acc-1){
	  int offset = 8-bits%8;
	  bits+=offset;
	  if(offset!=8){
	    for(int x=0;x<offset;x++){
	      input.erase(input.begin());
	    }
	  }
	}
      } catch(const char *exp){ break; }
      unsigned int num = int(c);
      ascii2.update(num);
      cout<<c;
    }
    acc=acc*2;
    count++;
    ascii1=ascii2;
  }
}
