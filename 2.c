#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
pid_t child_pid;
void sigchld_handler(int signum){
int status;
pid_t terminated_pid;
terminated_pid=wait(&status);
if(WIFEXITED(status)){
printf("Child process with PID %d terminated normally with exit status
%d.\n",terminated_pid,WEXITSTATUS(status));
}else if(WIFSIGNALED(status)){
printf("Child process with PID %d terminated by signal
%d.\n",terminated_pid,WTERMSIG(status));
}
}
void sigalarm_handler(int signum){
printf("Child process exceeded the time limit and is killed.\n");
kill(child_pid,SIGKILL);
}
int main(){
signal(SIGCHLD,sigchld_handler);
signal(SIGALRM,sigalarm_handler);
if((child_pid=fork())==-1){
perror("fork");
return 1;
}
if(child_pid==0){
execlp("ls","ls","-l",NULL);
perror("execlp");
exit(1);
}else{
alarm(5);
wait(NULL);
}
return 0;

}
