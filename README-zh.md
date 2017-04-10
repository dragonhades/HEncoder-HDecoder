# 使用说明：  
基于改良过的哈夫曼树对ASCII文本压缩算法制作的二进制文件编码器和解码器。 改良版的算法可以在仅一遍的用户文件长度时间中完成编码，并且不需要将原本的哈夫曼树包含在加密文件中也可完成解码。  
增加了加密功能，使得用户可以输入密码进行加密，只有拥有相同密钥才可解码，且密码本身不包含在加密文件中。  
  
安装：  
下载所有文件后运行Makefile即可完成安装。会产生两个可执行文件HEncode,HDecode。编译器为 g++ -std=c++14  
  
使用：  
  'HEncode' 需要一个文件名作为commandline arguement， 会询问用户输入两次密码， 然后将二进制加密结果输出在stdout。  
  'HEncode' 需要一个文件名作为commandline arguement， 会询问用户输入一次密码， 然后将解码结果输出在stdout。  
  'runTest.sh' 是测试用bash脚本， 需要一个文件名作为commandline arguement， 若无stdout结果则程序运行正常（详见diff命令）。  
  
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
  
注意: 由于哈夫曼算法特性，输入文件目前只支持ASCII文本（即不支持中文）。  
     只有当加密时输入的密码和解码时输入的密码一致时正确的文本才会被显示出来。 如果解码时密码错误则会得到乱码。  
  
引用: http://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt   参考了在用户输入密码时不显示字符的技术
  
联系： Bug反馈和问题请发送到 jimmyshanofficial@gmail.com 
