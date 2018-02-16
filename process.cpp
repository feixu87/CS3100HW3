#include "process.hpp"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
extern bool quittingTime;
int killPID(const pid_t& PID,int sig)
{

	return kill(PID,sig);

}
/*
int killPID2(const pid_t& PID,int sig)
{
	return kill(PID,SIGUSR2);
}
*/
int clock(struct timespec *tp)
{
	return clock_gettime(CLOCK_MONOTONIC, tp);
}
void mysleep(int nanosec)
{
    struct timespec res;
    res.tv_sec = nanosec/1000000000;
    res.tv_nsec = (nanosec) % 1000000000;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &res, NULL);
}
pid_t forkFun()
{
	return fork();
}