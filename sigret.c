#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc < 1){
    printf(2, "usage: sigret error...\n");
    exit();
  }
  sigret();
  exit();
}