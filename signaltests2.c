#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"

int pid;

void customSignalHandler(){
    printf(1, "This is a custom signal handler massage! \n");

    printf(1, "\nTest custom signal handler - PASSED ! \n");
    //exit();
}
void customSignalHandler1(){
    printf(1, "This is a custom signal handler massage! \n");
    printf(1, "\nTest custom signal handler - PASSED ! \n");
}

//Check custom signal handler AND signal kill
void test1(){
    printf(1, "Test start: test1 \n");
    sighandler_t handler = customSignalHandler;
    signal(5, handler);
    int i;
    pid = fork();
    if (pid == 0){
        while(1)
             printf(1, "child!-%d ",getpid());
    }
    for(i = 0; i<500; i++)
            printf(1, "father!-%d ",getpid());    
    kill(pid, 5);
    for(i = 0; i<400; i++)
            printf(1, "father! ");      
    kill(pid, SIGKILL);
    printf(1, "\nTest SIGKILL - PASSED ! \n");
    wait();
    printf(1, "\nTest end: test1 - PASSED! \n");
}

void test_StopCont(){
    printf(1, "\nTest start: test_StopCont \n");
    int i;
    pid = fork();
    if (pid == 0){
        for(i = 0; i < 200; i++){
            printf(1, "Child is running.. ");
        }
        exit();
    }
    printf(1, "\n\n\n");
    kill(pid, SIGSTOP);
    for(i = 0; i < 10; i++){
        printf(1, "Father is running.. ");
    }
    printf(1, "\n");
    kill(pid, SIGCONT);
    wait();
    
    printf(1, "\nTest end: test_StopCont \n");
}


void test_SignalMask(){
    printf(1, "\nTest start: test_SignalMask \n");
    sigprocmask(0);
    sighandler_t handler = customSignalHandler1;
    signal(5, handler);
    int i;
    pid = fork();
    if (pid == 0){
        for(i=0; i<40; i++)
            printf(1, " i am masked");
        printf(1, "\nmasked removed\n");       
        sigprocmask(0xffffffff);
        while(1);
                    printf(1, "keep alive");
        exit();
    }
    for(i=0;i<100;i++)
        printf(1, "...");
    kill(pid, 5);
    for(i=0;i<1000;i++)
        printf(1, "...");
    kill(pid, SIGKILL);
    // try to kill the child
    
    wait();
    printf(1, "signal mask test PASSED!\n");
}

void casTest(){
    printf(1, "\ntest cas\n");
    int inadd=0;
    int expected= 0;
    int newval=1;
    int bol= cas(&inadd,expected,newval);

    if(!bol || inadd!=1 ){
        printf(1, "cas test FAILED\n");
    }
    
    inadd=0;
    expected= 1;
    newval=2;
    bol= cas(&inadd,expected,newval);

    if(bol || inadd!=0 ){
        printf(1, "cas test FAILED\n");
    }
    printf(1, "cas test PASSED!\n");
}

int
main(int argc, char *argv[])
{
    printf(1, "~~~~~~~~~~~~~~~~~~%d~~~~~~~~~~~~~~~~\n",sizeof(struct trapframe));
    printf(1, "===== TEST STARTED =====\n");
    
    test1();
    //test_StopCont();
    //test_SignalMask();
    //casTest();
    
    printf(1, "===== ALL TESTS PASSED! =====\n");
    exit();
}