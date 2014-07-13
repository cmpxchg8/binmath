
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t gcd (uint64_t X, uint64_t Y)
{
  uint64_t x = X, y = Y;
  
  while (1)
  {
    if (y == 0) 
      return x;
    
    x = x % y;
    
    if (x == 0) 
      return y;
    y = y % x;
  }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf ("\nUsage: gcd <num 1> <num 2>\n");
    return 0;
  }

  printf ("\ngcd(%s, %s) = %lld", 
    argv[1], argv[2], 
    gcd (_strtoui64(argv[1], NULL, 10), 
      _strtoui64(argv[2], NULL, 10)));
  return 0;
}
