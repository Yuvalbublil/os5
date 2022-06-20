//
// Created by t8864522 on 12/06/2022.
//

#ifndef _CONTAINER_H_
#define _CONTAINER_H_
static const int STACK_SIZE = 8192;
static const int MODE = 777;

#include <cstdio>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <sched.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#define CGROUP_FOLDER0 "/sys/fs/"
#define CGROUP_FOLDER1 "/sys/fs/cgroup/"
#define CGROUP_FOLDER2 "/sys/fs/cgroup/pids/"
using std::string; using std::strlen;
class Container {
};

#endif //_CONTAINER_H_
