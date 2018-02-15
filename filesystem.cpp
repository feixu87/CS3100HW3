#include <iostream>
#include <csignal>
#include <cstdio>
#include <sys/stat.h>
#include "globalVal.hpp"
#include "filesystem.hpp"
#include <string>
#include <unistd.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;
extern bool quitingTime;

string getcwdF()
{
  char buff[1024];
  GetCurrentDir( buff, 1024);
  string current_working_dir(buff);
  return current_working_dir;
//	return std::boost::filesystem::current_path();
}
int chdirFun(string p)
{
	return chdir(p.c_str());
}
int accessCheck(const char* p,int flag)
{
	if(flag==0) //check the existence
		return access(p,F_OK);
	else if(flag==1)  //check read access
		return access(p,R_OK);
	else  //check write access;
		return access(p,W_OK);

}
void syncFun()
{
	sync();
}
int chmodFun(const char* path)
{
	return chmod(path,S_IRWXU);
}
int dup2F(int oldfd,int newfd)
{
	return dup2(oldfd,newfd);
}