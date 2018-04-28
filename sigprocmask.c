#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  uint sigmask; 
  if(argc < 2){
    printf(2, "usage: signal pid...\n");
    exit();
  }
  sigmask = atoi(argv[1]);
  sigprocmask(sigmask);
  exit();
}
