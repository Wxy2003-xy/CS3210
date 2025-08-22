#include <sys/shm.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

struct petersons_lock {
    int turn;
    bool flags[2];
};

int main() {
    int shmid;
    shmid = shmget(IPC_PRIVATE, sizeof(petersons_lock), IPC_CREAT | 0600);
    petersons_lock* lock = (petersons_lock*) shmat(shmid, NULL, 0);
    // initialization:
    lock->turn = 0;
    lock->flags[0] = false;
    lock->flags[1] = false;
    int pid;
    // child process
    if ((pid = fork()) == 0) {
        while (lock->turn == 0 && lock->flags[0]);
        lock->turn = 1;
        lock->flags[1] = true;
        cout<< pid << endl;
        cout<< "Child process: " << lock->turn <<endl;
        cout<< "Child process: " << lock->turn <<endl;
        cout<< "Child process: " << lock->turn <<endl;
        cout<< "Child process: " << lock->turn <<endl;
        cout<< "Child process: " << lock->turn <<endl;
        lock->flags[1] = false;
    } 
    // parent process
    else {
        while (lock->turn == 1 && lock->flags[1]);
        lock->turn = 0;
        lock->flags[0] = true;
        cout<< pid << endl;
        cout<< "Parent process: " << lock->turn <<endl;
        cout<< "Parent process: " << lock->turn <<endl;
        cout<< "Parent process: " << lock->turn <<endl;
        cout<< "Parent process: " << lock->turn <<endl;
        cout<< "Parent process: " << lock->turn <<endl;
        lock->flags[0] = false;
    }
    return 0;
}
