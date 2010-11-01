#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

/*
 * getpriority wrapper by D.Busby
 * Copyright 2010 David Busby, Saiweb.co.uk
 */

// value defnitions of string values
enum wTypes { evNotDefined, evPID, evGRP, evUSR };
// Map to associate strings to the enum values
static std::map<std::string, wTypes> s_mapTypes;

void mapInit(){
        s_mapTypes["pid"] = evPID;
        s_mapTypes["uid"] = evUSR;
        s_mapTypes["gid"] = evGRP;
}

void usage(){
        cout << "Usage: getpriority <type> <uid/gid/pid>" << endl;
        cout << "Types: uid/gid/pid" << endl;
        cout << "i.e. getpriority uid 48" << endl;
}

int main(int argc, char *argv[]){
        mapInit();
        if(argc < 2){
                usage();
                return 1;
        } else {
                int res=-1;
                switch(s_mapTypes[argv[1]]){
                        case evPID:
                                res = getpriority(PRIO_PROCESS,atoi(argv[2]));
                        break;
                        case evUSR:
                                res = getpriority(PRIO_USER,atoi(argv[2]));
                        break;
                        case evGRP:
                                res = getpriority(PRIO_PGRP,atoi(argv[2]));
                        break;
                        default:
                                usage();
                                return 1;
                }
                if(-1 == res){
                        cout << "woops! there was an error getting the priority" << endl;
                } else {
                        printf("Priority is %d\n",res);
                }
        }
}

