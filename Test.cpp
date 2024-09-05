#include <Windows.h>
#include <Winbase.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(void) {
	char buf[128];
	DWORD bufsize = sizeof(buf);
	DWORD ret = GetEnvironmentVariableA("USERNAME", buf, bufsize);
	
	if (ret >= bufsize){
		std::ofstream eLog("errorlog.log");
		eLog << "[*] The username of the current user is too large to fit in the buffer size of [128].";
		return 1;
	}
	
	char uname[ret+1]; /// setup username variable
	
	strcpy(uname, buf); // copy buffer to username
	int size = 11+(ret+1)+16; // set size of the path based on the retrieved usernaem
	char pth[size] = ""; // set the new path size
	sprintf(pth, "C:\\Users\\%s\\testdirectory", uname); // copy uname into path
	
	char fname[12] = "\\hello.txt"; // Set File Name
	
	char dir[sizeof(pth) + sizeof(fname) + 1]; // Create a dir buffer for the filename + path
	sprintf_s(dir, sizeof(dir), "%s%s", pth, fname); // Conjoin the path+filename

	CreateDirectoryA(pth, NULL); // Create Directory before file
	CreateFileA(dir, GENERIC_ALL, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Create File
	

	return 0;
}