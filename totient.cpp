
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t totient(uint64_t n)
{
  uint64_t i, ans = n;

  for (i=2; i * i <= n; i++)
  {
    if (n % i == 0)
    ans -= ans / i;

    while(n % i == 0)
      n /= i;
  }   

  if (n != 1)
    ans -= ans / n;
  return ans;   
}  

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf ("\nUsage: totient <number>\n");
    return 0;
  }

  printf ("\ntotient (%s) = %lld", 
    argv[1], totient (_strtoui64(argv[1], NULL, 10)));
  return 0;
}
