
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t add (uint64_t x, uint64_t y)
{
  while (y != 0)
  {
    uint64_t carry = x & y;  
    x = x ^ y; 
    y = carry << 1;
  }
  return x;
}

uint64_t mul (uint64_t x, uint64_t y) {
  uint64_t c = 0;
  
  while (x > 0) 
  {
    if (x & 1) {
      c = add (c, y);
    }
    x >>= 1;
    y <<= 1;
  }  
  return c;
}

int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    printf ("\nUsage: mul <multiplicand> <multiplier>\n");
    return 0;
  }
  
  printf ("\n%llu = %s * %s",  
    mul (_strtoui64(argv[1], NULL, 10), 
    _strtoui64(argv[2], NULL, 10)),
    argv[1], argv[2]); 
  return 0;
}
