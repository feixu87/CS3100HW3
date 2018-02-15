#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <sys/stat.h>
#include <string>
#include <unistd.h>
using namespace std;
string getcwdF();
int chdirFun(string p);
int accessCheck(const char* p,int flag);
void syncFun();
int chmodFun(const char* path);
int dup2F(int oldfd,int newfd);
#endif