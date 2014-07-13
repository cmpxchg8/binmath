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

uint64_t mulmod (uint64_t a, uint64_t b, uint64_t p)
{
  uint64_t x = 0, y = a;
  
  while (b > 0)
  {
    if (b & 1) {
      x = mod (add(x, y), p);
    }
    y = mod (y << 1, p);
    b >>= 1;
  }
  return x;
}

int main(int argc, char *argv[]) {
  
  uint64_t result=0;
  
  if (argc != 4) {
    printf ("\nUsage: mulmod <multiplicand> <multiplier> <modulus>\n");
    return 0;
  }
  
  result = mulmod (_strtoui64(argv[1], NULL, 10), 
    _strtoui64(argv[2], NULL, 10),
    _strtoui64(argv[3], NULL, 10)); 

  printf ("\n%llu = %s * %s %% %s", 
    result, argv[1], argv[2], argv[3]);
  return 0;
}
