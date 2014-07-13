
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

int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    printf ("\nUsage: add <augend> <addend>\n");
    return 0;
  }
    
  printf ("\n%s + %s = %lld", 
    argv[1], argv[2], 
    add (_strtoui64(argv[1], NULL, 10), 
      _strtoui64(argv[2], NULL, 10)));
  return 0;
}
