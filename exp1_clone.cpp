#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#define FIBER_STACK 8192
int a;
void * stack;
int do_something(void *arg){
		a=10;
		printf("This is son, the pid is:%d, the a is: %d\n", getpid(), a);
		free(stack); 
		exit(1);
}
int main() {
		void * stack;
		a = 1;
		stack = malloc(FIBER_STACK);//为子进程申请系统堆栈
		if(!stack) {
				printf("The stack failed\n");
				exit(0);
		}
		printf("creating son thread!!!\n");
		pid_t son_pid = clone(&do_something, (char *)stack + FIBER_STACK, CLONE_VM|CLONE_VFORK, 0);//创建子线程
		printf("This is father, my pid is: %d, the a is: %d, son_pid = %d\n", getpid(), a, son_pid);
		exit(1);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <sched.h>

// #define STACK_SIZE (1024 * 1024)

// int child_func(void *arg) {
//     // 强制刷新输出缓冲区，确保子进程输出即时显示
//     printf("Child thread created with PID: %d\n", getpid());
//     // free(stack);
//     exit(1);
// }

// int main() {
//     void *stack = malloc(STACK_SIZE);
//     if (stack == NULL) {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
//     }

//     pid_t pid = clone(child_func, (char*)stack + STACK_SIZE, CLONE_VM|CLONE_VFORK, NULL);
//     if (pid == -1) {
//         perror("clone failed");
//         exit(EXIT_FAILURE);
//         // int a = CLONE_FS|CLONE_VFORK|CLONE_FILES|CLONE_FS|CLONE_CHILD_CLEARTID;
//     }

//     printf("Parent process with PID: %d created a child with PID: %d\n", getpid(), pid);
//     free(stack);
//     exit(1);
// }
