//
// Created by t8864522 on 12/06/2022.
//


#include "Container.h"

char *get_stack_memory() {
    auto *stack_p = new(std::nothrow)char[STACK_SIZE];

    if (stack_p == nullptr) {
        printf("Cannot allocate memory \n");
        exit(EXIT_FAILURE);
    }
    return stack_p + STACK_SIZE;
}

void del_stack_memory(char *stackp) {
    char *temp = stackp - STACK_SIZE;
    delete[] temp;
}

void write_rule(const char *path, const string &value) {
    std::ofstream f(path);
    f << string(value) << std::endl;
    chmod(path, MODE);

}

static int run(char *const name, char **argv) {
    argv[0] = name;
    return execvp(name, argv);
}

void remove_dir(const char *path) {
    string s1(path);
    string s2(CGROUP_FOLDER0);
    string s3 = string("rm -r ") + s1 + s2;
    system(s3.c_str());
//    rmdir (CGROUP_FOLDER2);
//    rmdir (CGROUP_FOLDER1);
//    rmdir (CGROUP_FOLDER0);
}

void limitNumProcess(const char *max, const string &directory) {
    mkdir((directory + string(CGROUP_FOLDER0)).c_str(), MODE);
    mkdir((directory + string(CGROUP_FOLDER1)).c_str(), MODE);
    mkdir((directory + string(CGROUP_FOLDER2)).c_str(), MODE);

    const char *pid = new char[strlen(std::to_string(getpid()).c_str()) + 1];
    pid = std::to_string(getpid()).c_str();
    write_rule((directory + string(CGROUP_FOLDER2) + string("cgroup.procs")).c_str(), std::to_string(getpid()));
    write_rule((directory + string(CGROUP_FOLDER2) + string("pids.max")).c_str(), string(max));
    write_rule((directory + string(CGROUP_FOLDER2) + string("notify_on_release")).c_str(), "1");
//    delete[] pid;

}

int inner_run(void *args_out) {

    char **argv = (char **) args_out;
    char *hostname = argv[1];
    char *directory = argv[2];

    char *path_to_program = argv[4];
    int num = 0;
    char *v = argv[num];
    while (v != nullptr) {
        ++num;
        v = argv[num];
    }
    int argc = num + 1;
    auto args_for_program = new char *[argc - 4]; // TODO: save on this alloc
    for (int i = 0; i < argc - 4; ++i) {
        args_for_program[i] = argv[i + 4];
    }
    args_for_program[argc - 5] = nullptr;
    args_for_program[0] = path_to_program;
    sethostname(hostname, std::strlen(hostname));
    char *num_processes = argv[3];
    limitNumProcess(num_processes, string(directory));
    chroot(directory);
    chdir("/");


    mount("proc", "/proc", "proc", 0, 0);
    int b = run(path_to_program, (char **) args_for_program);


    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {

    auto args = new char *[argc + 1];
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }
    args[argc] = nullptr;
    char *stack = get_stack_memory();

    clone(inner_run, stack, CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD | CLONE_NEWNS, args);
    wait(nullptr);

    remove_dir(args[2]);
    std::ofstream f("gay");
    f << "ssss\n";
    f << (string(argv[2]) + "/proc") << std::endl;
    string s = (string(argv[2]) + "/proc");

    unsigned long n = s.length();

    char char_array[n + 1];


    strcpy(char_array, s.c_str());
    umount(char_array);
    del_stack_memory(stack);

    delete[] args;
    return EXIT_SUCCESS;
}