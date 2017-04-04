# HEncoder-HDecoder
Encoder and Decoder based on the user input password to encode the given ASCII text file using Huffman tree.

Install: 
  Please download all the file in order to compile successfully. Makefile will generate two executables, "HDecode" and "HEncode"

Usage:
  'HEncode' takes a filename as commandline arguement. It will ask the user to give input as a password, and will output the encoded binary file to stdout.
  'HDecode' takes a filename as commandline arguement. It will ask the user to give input as a password, and ask again to prevent possible typo. Then it will output the decoded text to stdout.

Note: The input file should only contain ASCII charators.
      If the password given in HDecode is wrong, unreadable messy code will be given.

Credits: http://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt   for hiding user password input from screen

Contact: Any bug reports or concerns please contact jimmyshanofficial@gmail.com
