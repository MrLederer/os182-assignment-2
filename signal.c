#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int signum; 
  sighandler_t handler;
  if(argc < 3){
    printf(2, "usage: signal pid...\n");
    exit();
  }
  signum = atoi(argv[1]);
  handler = (sighandler_t)atoi(argv[2]);
  signal(signum,handler);
  exit();
}