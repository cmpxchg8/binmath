
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t sub (uint64_t x, uint64_t y)
{
  x = ~x;
  while (y != 0)
  {
    uint64_t carry = x & y;  
    x = x ^ y; 
    y = carry << 1;
  }
  return ~x;
}

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

void divmod (uint64_t dividend, uint64_t divisor, 
  uint64_t *quotient, uint64_t *remainder) {
  
  uint64_t r, q, t, i;
  
  *quotient  = 0;
  *remainder = 0;
  
  r = 0;
  q = 0;
  t = dividend;
  
  for (i = 0; i < sizeof (uint64_t) * CHAR_BIT; i++)
  {
    r <<= 1;
    q <<= 1;
    r |= (t & INT64_MIN) >> (sizeof (uint64_t) * CHAR_BIT)-1;
    
    if (r >= divisor) {
      r = sub (r, divisor);
      q = add (q, 1); 
    }
    t <<= 1;
  }
  *quotient  = q;
  *remainder = r;
}

int main(int argc, char *argv[]) {
  
  uint64_t remainder, quotient;
  
  if (argc != 3) {
    printf ("\nUsage: divmod <dividend> <divisor>\n");
    return 0;
  }
  
  divmod (_strtoui64(argv[1], NULL, 10), 
    _strtoui64(argv[2], NULL, 10), &quotient, &remainder); 

    
  printf ("\n%s / %s = %lld with remainder %lld", 
    argv[1], argv[2], quotient, remainder);
  return 0;
}
