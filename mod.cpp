
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t mod (uint64_t dividend, uint64_t divisor)
{
  uint64_t r = 0;
  uint64_t t = dividend;
  uint64_t i;
  
  for (i = 0; i < sizeof (uint64_t) * CHAR_BIT; i++) 
  {
    r <<= 1; 
    r |= (t & INT64_MIN) >> (sizeof (uint64_t) * CHAR_BIT) - 1;
    
    if (r >= divisor) {
      r -= divisor;
    }
    t <<= 1;
  }
  return r;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf ("\nUsage: mod <dividend> <divisor>\n");
    return 0;
  }

  printf ("\n%s %% %s = %lld", 
    argv[1], argv[2], 
    mod (_strtoui64(argv[1], NULL, 10), 
      _strtoui64(argv[2], NULL, 10)));
  return 0;
}
