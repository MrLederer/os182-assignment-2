#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "x86.h"
#define STDOUT 1
#define LOOPSIZE 15
// meant to be run w/ at most two CPUs
void
killsign1(void)
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ KILL SIGNAL TEST1 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to kill... \n");

    printf(STDOUT, "kill return %d \n",kill(pid1,SIGKILL));

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "kill signal test1 ok\n");
}
void
killsign2(void)
{
  int pid1, pid2;// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ KILL SIGNAL TEST2 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }
  pid2 = fork();
  if(pid2 == 0)
  {
    for(;;)
    {}
  }
  printf(STDOUT, "trying to kill... \n");

    printf(STDOUT, "kill return %d \n",kill(pid1,SIGKILL));
    printf(STDOUT, "kill return %d \n",kill(pid2,SIGKILL));

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());
    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "kill signal test2 ok\n");
}

void
killsignloop(void)
{
  int i,pid[LOOPSIZE];// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ KILL SIGNAL TEST LOOP @@@@@@@@@@@@@@@@@\n ");
  for(i=0;i<LOOPSIZE;i++)
  {
    pid[i] = fork();
    if(pid[i] == 0)
    {
      for(;;)
      {}
    }  
  }
  printf(STDOUT, "trying to kill... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "kill return %d \n",kill(pid[i],SIGKILL));
  }

  printf(STDOUT, "trying to wait... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "wait return %d\n",wait());
  }
  printf(STDOUT, "kill signal test loop ok\n");
}
void
stopsign1(void)
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ STOP SIGNAL TEST1 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to stop... \n");

    printf(STDOUT, "stop return %d \n",kill(pid1,SIGSTOP));

  printf(STDOUT, "trying to kill and wait... \n");
    printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "stop signal test1 ok\n");
}
void
stopsign2(void)
{
  int pid1, pid2;// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ STOP SIGNAL TEST2 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }
  pid2 = fork();
  if(pid2 == 0)
  {
    for(;;)
    {}
  }
  printf(STDOUT, "trying to stop... \n");

    printf(STDOUT, "stop return %d \n",kill(pid1,SIGSTOP));
    printf(STDOUT, "stop return %d \n",kill(pid2,SIGSTOP));

  printf(STDOUT, "trying to kill and wait... \n");
    printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    printf(STDOUT, "wait return %d\n",wait());
    printf(STDOUT, "kill return %d\n",kill(pid2,SIGKILL));
    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "stop signal test2 ok\n");
}
void
stopsignloop(void)
{
  int i,pid[LOOPSIZE];// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ STOP SIGNAL TEST LOOP @@@@@@@@@@@@@@@@@\n ");
  for(i=0;i<LOOPSIZE;i++)
  {
    pid[i] = fork();
    if(pid[i] == 0)
    {
      for(;;)
      {}
    }  
  }
  printf(STDOUT, "trying to stop... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "stop return %d \n",kill(pid[i],SIGSTOP));
  }
  printf(STDOUT, "trying to kill and wait... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "kill return %d\n",kill(pid[i],SIGKILL));
  }
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "wait return %d\n",wait());
  }
  
  printf(STDOUT, "stop signal test loop ok\n");
}
void
contsign1(void)
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ CONT SIGNAL TEST1 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to cont... \n");
    printf(STDOUT, "stop return %d\n",kill(pid1,SIGSTOP));
    printf(STDOUT, "cont return %d \n",kill(pid1,SIGCONT));


  printf(STDOUT, "trying to kill and wait... \n");

    printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "cont signal test1 ok\n");
}
void
contsign2(void)
{
  int pid1, pid2;// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ CONT SIGNAL TEST2 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }
  pid2 = fork();
  if(pid2 == 0)
  {
    for(;;)
    {}
  }
  printf(STDOUT, "trying to cont... \n");
    printf(STDOUT, "stop return %d\n",kill(pid1,SIGSTOP));
    printf(STDOUT, "stop return %d\n",kill(pid2,SIGSTOP));
    // for(int i=0;i<100;i++)
    //   printf(STDOUT,"afterSendingStop..");
    printf(STDOUT, "cont return %d \n",kill(pid1,SIGCONT));
    printf(STDOUT, "cont return %d \n",kill(pid2,SIGCONT));
      // for(int i=0;i<100;i++)
      // printf(STDOUT,"afterSendingCont..");
  printf(STDOUT, "trying to kill and wait... \n");
    printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    printf(STDOUT, "kill return %d\n",kill(pid2,SIGKILL));
    printf(STDOUT, "wait return %d\n",wait());
    printf(STDOUT, "wait return %d\n",wait());
  printf(STDOUT, "cont signal test2 ok\n");
}
void
contsignloop(void)
{
  int i,pid[LOOPSIZE];// pid3, pid4;

  printf(STDOUT, "@@@@@@@@@@@@@@@ CONT SIGNAL TEST LOOP @@@@@@@@@@@@@@@@@\n ");
  for(i=0;i<LOOPSIZE;i++)
  {
    pid[i] = fork();
    if(pid[i] == 0)
    {
      for(;;)
      {}
    }  
  }
  printf(STDOUT, "trying to stop all... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "stop return %d\n",kill(pid[i],SIGSTOP));
  }
  printf(STDOUT, "trying to cont all... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "cont return %d \n",kill(pid[i],SIGCONT));
  }
  printf(STDOUT, "trying to kill and wait... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "kill return %d\n",kill(pid[i],SIGKILL));
  }
  for(i=0;i<LOOPSIZE;i++)
  {
    printf(STDOUT, "wait return %d\n",wait());
  }
  
  printf(STDOUT, "cont signal test loop ok\n");
}
void
edgepointtest1()
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ EDGE POINT SIGNAL TEST1 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to cont a few times... \n");

  for(int i=0;i<3;i++)
  {
	printf(STDOUT, "cont return %d \n",kill(pid1,SIGCONT));
  }
  printf(STDOUT, "trying to kill... \n");

  printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "edge point signal test1 ok\n");
}
void
edgepointtest2()
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ EDGE POINT SIGNAL TEST2 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to stop a few times... \n");

  for(int i=0;i<3;i++)
  {
	printf(STDOUT, "stop return %d \n",kill(pid1,SIGSTOP));
  }
  printf(STDOUT, "trying to kill... \n");

  printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "edge point signal test2 ok\n");
}
void
edgepointtest3()
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ EDGE POINT SIGNAL TEST3 @@@@@@@@@@@@@@@@@\n ");
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to send stop and cont at the same time a few times... \n");

  for(int i=0;i<3;i++)
  {
  	printf(STDOUT, "cont return %d \n",kill(pid1,SIGCONT));
	printf(STDOUT, "stop return %d \n",kill(pid1,SIGSTOP));
  }
  printf(STDOUT, "trying to kill... \n");

  printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "edge point signal test3 ok\n");
}
void customSignalHandler(){
    printf(1, "This is a message from a custom signal handler. called by pid: %d\n",getpid());
}
void
customsignaltest1()
{
  int pid1;

  printf(STDOUT, "@@@@@@@@@@@@@@@ CUSTOM SIGNAL TEST1 @@@@@@@@@@@@@@@@@\n ");
  printf(STDOUT, "trying to define the custom signal \n");
  sighandler_t handler = customSignalHandler;
  printf(STDOUT, "systemcall signal return %d \n",signal(1, handler));
  pid1 = fork();
  if(pid1 == 0)
  {
    for(;;)
    {}
  }

  printf(STDOUT, "trying to call the user signal \n");

  printf(STDOUT, "customsignal return %d \n",kill(pid1,1));


  printf(STDOUT, "trying to kill... \n");

  printf(STDOUT, "kill return %d\n",kill(pid1,SIGKILL));
    

  printf(STDOUT, "trying to wait... \n");

    printf(STDOUT, "wait return %d\n",wait());

  printf(STDOUT, "custom signal signal test1 ok\n");
}
void
customsignaltest2()
{
  int i,pid[LOOPSIZE];

  printf(STDOUT, "@@@@@@@@@@@@@@@ CUSTOM SIGNAL TEST2 @@@@@@@@@@@@@@@@@\n ");
  printf(STDOUT, "trying to define the custom signal \n");
  sighandler_t handler = customSignalHandler;
  printf(STDOUT, "systemcall signal return %d \n",signal(1, handler));
  for(i=0;i<LOOPSIZE;i++)
  {
  	pid[i] = fork();
	if(pid[i] == 0)
	{
		for(;;)
		{}
	}
  }

  printf(STDOUT, "trying to call the user signal \n");
  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "customsignal return %d \n",kill(pid[i],1));
  }
  


  printf(STDOUT, "trying to kill... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "kill return %d\n",kill(pid[i],SIGKILL));
  }
  
    

  printf(STDOUT, "trying to wait... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "wait return %d\n",wait());
  }

  printf(STDOUT, "custom signal signal test2 ok\n");
}
void
customsignaltest3()
{
  int i,pid[LOOPSIZE];

  printf(STDOUT, "@@@@@@@@@@@@@@@ CUSTOM SIGNAL TEST3 @@@@@@@@@@@@@@@@@\n ");
  printf(STDOUT, "trying to define the custom signal \n");
  sighandler_t handler = customSignalHandler;
  printf(STDOUT, "systemcall signal return %d \n",signal(1, handler));
  for(i=0;i<LOOPSIZE;i++)
  {
  	pid[i] = fork();
	if(pid[i] == 0)
	{
		for(;;)
		{}
	}
  }

  printf(STDOUT, "trying to call the user signal a few times for each child \n");
  printf(STDOUT, "and so the number of times the custom signal will be activated is non deterministic \n");
  for(i=0;i<LOOPSIZE*3;i++)
  {
  	printf(STDOUT, "customsignal return %d \n",kill(pid[i%LOOPSIZE],1));
  }
  


  printf(STDOUT, "trying to kill... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "kill return %d\n",kill(pid[i],SIGKILL));
  }
  
    

  printf(STDOUT, "trying to wait... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "wait return %d\n",wait());
  }

  printf(STDOUT, "custom signal signal test3 ok\n");
}
void
customsignaltest4()
{
  int i,pid[LOOPSIZE];

  printf(STDOUT, "@@@@@@@@@@@@@@@ CUSTOM SIGNAL TEST4 @@@@@@@@@@@@@@@@@\n ");
  printf(STDOUT, "trying to define the custom signal \n");
  sighandler_t handler = customSignalHandler;
  printf(STDOUT, "systemcall signal return %d \n",signal(1, handler));
  
  printf(STDOUT, "defining each child to send the next child a siganl \n");
  printf(STDOUT, "creating an endless loop of signals \n");

	pid[0] = fork();
	if(pid[0] == 0)
	{
		for(;;)
		{
			sleep(100);
			kill(getpid()+LOOPSIZE-1,1);
		}
	}
  for(i=1;i<LOOPSIZE;i++)
  {
  	pid[i] = fork();
	if(pid[i] == 0)
	{
		for(;;)
		{
			
			kill(pid[i-1],1);
			sleep(100);
		}
	}
  }
  sleep(2000);

  printf(STDOUT, "trying to kill... \n");

  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "kill return %d\n",kill(pid[i],SIGKILL));
  }
  
    

  printf(STDOUT, "trying to wait... \n");
  for(i=0;i<LOOPSIZE;i++)
  {
  	printf(STDOUT, "wait return %d\n",wait());
  }

  printf(STDOUT, "custom signal signal test4 ok\n");
}
void
welcomeprint()
{
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~STARTING SIGNAL TESTS~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void
doneprint()
{
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~ALL TESTS PASSED~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(STDOUT,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
int
main(int argc, char *argv[])
{
  welcomeprint();

  killsign1();
  killsign2();
  killsignloop();

  stopsign1();
  stopsign2();
  stopsignloop();

  contsign1();
  contsign2();
  contsignloop();

  edgepointtest1(); 
  edgepointtest2();
  edgepointtest3();

  customsignaltest1();
  customsignaltest2();
  customsignaltest3();
  customsignaltest4();

  doneprint();
  exit();
}
