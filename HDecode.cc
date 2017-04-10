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


// open filename and read 1 byte every time, get bit and convert them into a string
string read_bits(const char* filename){
  string bitstring;
  ifstream file(filename, ios::binary);
  if(file.fail()) throw string("Cannot open ")+filename;
  char c;
  while(file.get(c)){
    for (int i = 7; i >= 0; i--) {
      if(int((c >> i) & 1)==1) bitstring += "1";
      else bitstring += "0";
    }
  }
  return bitstring;
}

// use Tree t, find and return the decoded message
char decode(Tree &t, vector<char> &input){
  int inp;
  auto ptr = make_shared<Node>(t.list[0]);
  while(1){
    if(ptr->left==nullptr&&ptr->right==nullptr){
      return (char) ptr->c;
    }
    if(input.empty()) throw "EMPTY";
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
  
  // check if have enough argument
  if(argc<2){
    cerr<<"Usage: ./HDecode Filename";
    return 0;
  }

  string str;
  try {
    str = read_bits(argv[1]);
  } catch(const string &s){
    cerr<<s<<endl;
    return 0;
  }
  
  // hide user entered password from screen
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
  istringstream iss(str);
  while(iss>>inp){
    input.emplace_back(inp);
  }

  while(!input.empty()){
    
    Tree t(ascii1);
    
    if(count==0){
      // see HEncode.cc for details
      random_shuffle(t.list.begin(),t.list.end());
    }
    t.merge_least();
    
    if(count==1) acc = 128;  // sequence is 128, 128, 256, 512, 1024 ...
    
    for(register int i = 0; i<acc; i++){
      char c;
      try {
	c = decode(t,input); // may throw 
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
