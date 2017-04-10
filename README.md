# HEncoder-HDecoder
Encoder and Decoder based on the user input password to encode the given ASCII text file using Huffman tree.

Install:   
  Please download all files in order to compile successfully. Makefile will generate two executables, "HDecode" and "HEncode". Compiler used is g++ -std=c++14

Usage:  
  'HEncode' takes a filename as commandline arguement. It will ask the user to give input as a password, and will output the encoded binary file to stdout.  
  'HDecode' takes a filename as commandline arguement. It will ask the user to give input as a password, and ask again to prevent possible typos. Then it will output the decoded text to stdout.  
  'runTest.sh' is a bash script yo help testing. It takes a filename as commandline argument, and use 'diff' command as result of output.  

Demo:
```bash
$ ./HEncode toEncode.txt > encode.out  
Enter password:  
pw42  
Please enter again:  
pw42  
$ ./HDecode encode.out > myfile.txt  
Enter password:  
WARNING: Wrong password will get you unreadable messy code.  
pw42  
$ diff toEncode.txt myfile.txt  
$  
```
  
Note: The input file should only contain ASCII charators.  
      Only when encoding password and decoding password match so the correct original file will be outputed.  
      If the password given in HDecode is wrong, unreadable messy code will be given.  

Credits: http://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt   for hiding user password input from screen  
  
Contact: Any bug reports or concerns please contact jimmyshanofficial@gmail.com 
