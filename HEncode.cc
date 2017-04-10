#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
using namespace std;

#include "tools.h"

struct Tree;
struct Node;
struct Ascii;

// int defined in tool.cc, see more details there
// Used to set the acc for huffman coding loop sequence
// Default to 128
extern unsigned int ACCUMULATOR;

int char_to_int(const char &c){
  if(c=='0') return 0;
  else return 1;
}

void get_bit(int *arr, int &count, const char c){
  count++;
  arr[count-1] = char_to_int(c);
  if(count==8) count=0;
}

// using t as Huffman tree to encode input, return 0 & 1 in a string.
string encode(Tree &t,vector<int> &input){
  string s;
  for(auto num:input){
    s += t.list[0].out(num,"");
  }
  return s;
}

// bin_out outputs encoding into binary
// Challenges are that C++ (most languages) only can output 1 byte (1 char) at a time 
// Need to concatenate all bits into bytes intuitively
void bin_out(const string &s){
  istringstream iss(s);
  char c;
  int count=0;	// counting the bits
  int arr[8];	// use to contain one byte.
  
  try {
    while(1){
      for(register int i=0;i<8;i++){
	if(!(iss>>c)) throw 0;	// when input exhausted, need to "round up" a byte
	get_bit(arr, count, c);	//convert c into int and put in arr, count++
      }

      // if we have a full byte, we output it.
      putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2|arr[6]<<1|arr[7]);
    
    }
  } catch(...){

    // input exhausted, round up a byte by filling 0 bit(s).

    switch(count){
      case 0:
	break;
      case 1:
	putchar(arr[0]<<7);
	break;
      case 2:
	putchar(arr[0]<<7|arr[1]<<6);
	break;
      case 3:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5);
	break;
      case 4:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4);
	break;
      case 5:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3);
	break;
      case 6:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2);
	break;
      case 7:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2|arr[6]<<1);
	break;
    }
  }
}

int main(int argc, char* argv[]){
  
  // check if have enough argument
  if(argc<2){
    cerr<<"Usage: ./HDecode Filename";
    return 0;
  }
  
  ifstream fs(argv[1]);
  if(fs.fail()) {
    cerr<<"Cannot open "<<argv[1]<<endl;
    return 0;
  }
   
  // To hide password input from screen
  //http://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
  while(1){
    cerr<<"Enter password:"<<endl;
    string enter;
    getline(cin, enter);
    cerr<<"Please enter again:"<<endl;
    string again;
    getline(cin, again);
    if(enter!=again){
      cerr<<"The password you entered does not match the pervious one."<<endl;
      cerr<<"Try again."<<endl;
    } else {
      setSeed(enter);	// tools.h
      break;
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);	// clean up
  
  int count=0;
  char inp;
  Ascii ascii1;
  Ascii ascii2;
  vector<int> input;
  string output;
  int acc = ACCUMULATOR;

  while(1){
    ascii1=ascii2;
    input.clear();
    if(count==1) acc=ACCUMULATOR;	// need a sequence of acc acc acc*2 acc*4 acc*8 ...
    for(register int i = 0; i<acc; i++){
      fs>>noskipws>>inp;
      if(fs.fail()) break;	// works on empty input file
      input.emplace_back(inp);
      int num = (unsigned int) inp;
      ascii2.update(num);
    }
    Tree t(ascii1);
    
    if(count==0){

      // use the password as a seed to shuffle the first 128 ASCII entries.

      random_shuffle(t.list.begin(),t.list.end());	// <algorithm>
    }

    t.merge_least();	// tools.h
    output += encode(t,input);
    acc=acc*2;
    count++;
    if(fs.fail()) break;
  }
 
  // stream out binary sequence
  bin_out(output);

#ifdef DEBUG
  // tools.h
  t.huffcode();	
  ascii2.hufffreq();
  wpl(t,ascii2);
#endif

}
