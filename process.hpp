#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
/*
use kill() to cause your program to send signal 0 to itself
use kill() to cause your program to send signal SIGUSR2 to itself
clock()
nanosleep() with a delay of 1ns
nanosleep() with a delay of 1,000ns
nanosleep() with a delay of 1,000,000ns
nanosleep() with a delay of 1,000,000,000ns
fork() - this function will also require that you use the following system calls:
exit() - your child process should do only this
wait() - your main program will need to call this function to "clean up" or "reap" its children which have called exit(). If you don't do this correctly, your computer may freeze.

*/
using namespace std;

int killPID(const pid_t& PID,int sig);
//int killPID2(const pid_t& PID,int sig);	
int clock(struct timespec *tp);
void mysleep(int nanosec);
pid_t forkFun();
#endif
