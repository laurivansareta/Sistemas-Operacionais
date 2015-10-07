// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  3

void
printf(int fd, char *s, ...)
{
  write(fd, s, strlen(s));
}

void
forktest(void)
{
  int n, pid;

  printf(1, "\nfork test\n");
	
  for(n=0; n<N; n++){
    pid = fork();
    //sleep(1000);
    printf(1,"\ncriando");
    if(pid < 0)
      break;
    if(pid == 0)
      exit();
  }
  
  if(n == N){
    printf(1, "\nfork claimed to work N times!\n", N);
    exit();
  }
  
  for(; n > 0; n--){
    if(wait() < 0){
      printf(1, "\nwait stopped early\n");
      exit();
    }
  }
  
  if(wait() != -1){
    printf(1, "\nwait got too many\n");
    exit();
  }
  
  printf(1, "\nfork test laurivan OK\n");
}

int
main(void)
{
  forktest();
  exit();
}
