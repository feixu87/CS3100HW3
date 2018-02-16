#include <iostream>
#include <csignal>
#include <cstdio>
#include <cmath>
#include "clang.hpp"
extern bool quittingTime;

void addOpt(void){
	int c=0;
	while(!quittingTime)
	{
		c=1+1;

	}
	quittingTime = false;
}
void sqrtOpt(void){
	double c=0;
	while(!quittingTime)
	{
		c=sqrt(25);

	}
	quittingTime = false;
}
void NewDel(void) {

    while (!quittingTime) {
        char* a=new char[20];
	delete a;
        }

    quittingTime = false;
}
void NewAll(void) {

    while (!quittingTime) {
        char* a=new char[1024];
	
        }

    quittingTime = false;
}