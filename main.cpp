#include <iostream>
#include <csignal>
#include <cstdio>
#include "clang.hpp"
#include "process.hpp"
#include "filesystem.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
 * This program performs CPU-bound and I/O-bound operations so you can observe
 * its performance characteristics from a process monitor such as htop.
 * If htop is not already installed,
 *  
 *  $ sudo apt install htop
 *
 * By default it uses your Raspberry Pi's MicroSD card as its "slow" device.
 * The MicroSD not actually that slow, however. Plug in an external USB drive
 * to watch this program *really* waste time.
 *
 * You can find out the device name of your USB drive by reading the file
 * /proc/partitions after you plug it in:
 *  
 * $ cat /proc/partitions
 *  
 * Try running algorithm #2 with a USB drive and again with /dev/zero.
 * 
 * NOTE: you may need to add your user to another group in order to have
 * permission to access the raw device file. For instance, if I use `ls` to
 * give me a long listing of /dev/sda, I see that this file belongs to the
 * 'disk' group:
 * 
 * $ ls -l /dev/mmcblk0
 * brw-rw---- 1 root disk 179, 0 Jan 31 12:17 /dev/mmcblk0
 * 
 * Use this command to add your user to that group. You will have to log
 * out and log back in for the change to become effective.
 * 
 * $ sudo gpasswd -a $USER disk
 * 
 */


using namespace std;

#define VERSION "1.3"

/* this must be global since it needs to be accessible by the signal handler */
bool quittingTime = false;

/* This function runs when Ctrl-C is pressed */
void sigint(int signal) {
    quittingTime = true;
}
void help()
{
	cout << "------------the main menu-------------"<<endl;
	cout <<"a: getcwd()"<<endl;
	cout <<"b: chdir()"<<endl;
	cout <<"c: access()"<<endl;
	
	cout <<"d: sync()"<<endl;
	cout <<"e: chmod()"<<endl;
	cout <<"f: dup2()"<<endl;
	cout <<"g: addOpt()"<<endl;
	cout << "h: sqrt()" << endl;
	cout <<"i: new/delete()"<<endl;
	cout <<"j: new()"<<endl;
	cout <<"k: kill()"<<endl;
	cout <<"l: clock()"<<endl;
	cout <<"m: sleep()"<<endl;
	cout << "n: fork()" << endl;
	cout << "q: exit the program." << endl;
}
void check()
{
		cout << "-----check access opitions:-----"<<endl;
		cout << "0:  check the file existence" << endl;
		cout << "1:  check the read access" << endl;
		cout << "2:  check the write access" << endl;
}
int main(int argc, char** argv) {
    // Which slow I/O device to use?
    // The default is to use your Raspberry Pi's MicroSD card.
    // Else, use the device specified as the 1st argument to this program


    if (argc < 2 )
	{
		cout << "error" <<endl;
		help();
		return 0;
	}
    pid_t PID= getpid();
    cout << PID<<endl;
    char* input=(argv[1]);
    char inputnum=input[0];
    bool inputFlag=true;
    while(!quittingTime)
    {
	
        if(inputnum<'a'||inputnum>'n'&&inputnum!='q')
	{
		help();
		cin >> inputnum;
		continue;
	}

    /* This is how your application can respond to software-defined interrupts
     * (a.k.a. traps) sent from the OS.
     *
     * Connect the interrupt signal SIGINT (it happens when you press Ctrl-C in
     * the terminal) to our sigint() function, defined above */
    signal(SIGINT, sigint);
	
        switch (inputnum) {
            case 'a':
            {
		cout << getcwdF() <<endl;
                break;
            }
            case 'b':
	    {
		string newpath;
		cout << "enter the new directory:" <<endl;   
		cin >> newpath;	
		cin.get();
                chdirFun(newpath);
		cout << "new directory:" <<getcwdF()<<endl;
                break;
	    }
	    case 'c':
            {
		char* path="/proc/self/exe";
		int flag;
		check();
		cout << "enter the option:" ;
		cin >> flag;
		syncFun();
		while(flag!=0 && flag!=1 &&flag !=2)
		{
			check();
			cin >> flag;
		}	
		int revl=accessCheck(path,flag);
		if(revl==0)
			cout << "The file can be accessed." << endl;
		else
			cout << "Access denied." << endl;
		break;
	    }
            case 'd':
	    {
		syncFun();
		break;
	    }
            case 'e':
	    {
		int rev=chmodFun("/proc/self/exe");
		if(rev==0)
			cout << "sucess!" <<endl;
		else
			cout << "error" << endl;
		break;
	    }
            case 'f':
	    {
		int defout=dup(1);
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		int fd=open("out.txt", O_RDWR | O_TRUNC | O_CREAT,mode);
		int rev=dup2F(fd,1);
		if(rev==0)
			cout << "sucess!" <<endl;
		else
			cout << "error" << endl;
		close(fd);
		break;
	    }
            case 'g':
		addOpt();
		break;
            case 'h':
	    {
   		sqrtOpt();
		break;
	    }
            case 'i':
	    {
		NewDel();
		break;
	    }
            case 'j':
		NewAll();
		break;           
	    case 'k':
	    {
		cout << "two options:0, send siginal 0 ;1, send singinal SIGUSR2:" << endl;
		int sig;
		cin >> sig;
		while(sig!=0 && sig!=1)
		{	
			cout << "enter the option: 0 or 1" ;
			cin >> sig;
		}
		if(sig==0)
		{
		if(killPID(PID,0))
			cout << "sucess!"<<endl;
		else
			cout << "fail!" << endl;
		}	
		else
		{	
		if(killPID(PID,SIGUSR2))
			cout << "sucess!"<<endl;
		else
			cout << "fail!" << endl;
		}
		break;
	    }
            case 'l':
	    {
		struct timespec spec;
		
		clock(&spec);
		
		double ts  = spec.tv_sec+double(spec.tv_nsec / 1.0e6);
    		
		printf("Current time:%03ld seconds since the Epoch\n",
           ts);
		break;
	    }
            case 'm':
	    {
		cout <<"the sleep functions:enter the delaying time, unit nanosec" <<endl;
		int nanosec;
		cin >> nanosec;
		mysleep(nanosec);
		break;
	    }
            case 'n':
	    {
		int status;
		pid_t child_pid=forkFun();
		cout << child_pid<<endl;
	  	if (child_pid< 0) {     /* fork a child process           */
	         printf("*** ERROR: forking child process failed\n");
	         exit(1);
    		  }
		else if(child_pid==0)
			exit(1);
		else{
		 while(wait(&status)!=child_pid)
			;
		}
		
		break;
	    }
            case 'q':
	    {	
                quittingTime = true;
                exit(0);
	    }
        }
	cout <<"enter your option:";
	cin >> inputnum;
    }
  
    return 0;
}