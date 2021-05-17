#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"

#include <sys/time.h>
#include <sys/resource.h>

int x[5] = {1,2,3,4,5};

void allocate()
{
    int i;
    int *p;
    for(i =1 ; i<1000000 ; i++)
    {
      p = malloc(500 * sizeof(int));
      if(func(i)) { free (p);}
    }
}

void allocate1()
{
  int i;
  int *p;
  for (i=1 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    if(i & 1)
      free (p);
  }
}

void allocate2()
{
  int i;
  int *p;
  for (i=1 ; i<300000 ; i++)
  {
    p = malloc(10000 * sizeof(int));
    free (p);
  }
}


int main(int argc, char const *argv[]) {
  int i;
  int *p;

  struct rusage usage;
  struct timeval start_sys, end_sys, start_user, end_user;

  getrusage(RUSAGE_SELF, &usage);
  start_sys = usage.ru_stime;
  start_user = usage.ru_utime;

  printf("Max Resident Set Size: %ld\n", usage.ru_maxrss);
  printf("Voluntary Context Swithces: %ld\n", usage.ru_nvcsw);
  printf("Involuntary Context Switches: %ld\n", usage.ru_nivcsw);

  printf("Executing the code ......\n");
  allocate();

  for (i=0 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    free (p);
  }
  printf("Program execution successfull\n\n");

  getrusage(RUSAGE_SELF, &usage);
  end_sys = usage.ru_stime;
  end_user = usage.ru_utime;

  printf("Started System at: %ld.%lds\n", start_sys.tv_sec, start_sys.tv_sec);
  printf("Ended System at: %ld.%lds\n\n", end_sys.tv_sec, end_sys.tv_sec);

  printf("Started User at: %ld.%lds\n", start_user.tv_sec, start_user.tv_sec);
  printf("Ended User at: %ld.%lds\n\n", end_user.tv_sec, end_user.tv_sec);

  printf("Max Resident Set Size: %ld\n", usage.ru_maxrss);
  printf("Voluntary Context Swithces: %ld\n", usage.ru_nvcsw);
  printf("Involuntary Context Switches: %ld\n", usage.ru_nivcsw);

  return 0;
}
