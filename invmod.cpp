
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t invmod (uint64_t a, uint64_t m)
{
  uint64_t j = 1, i = 0, b = m, c = a, x, y;
  while (c != 0)
  {
    x = b / c;
    y = b - x * c;
    b = c; 
    c = y;
    y = j;
    j = i - j * x;
    i = y;
  }
  if ((int64_t)i < 0)
    i += m;
  return i;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf ("\nUsage: invmod <n> <p>\n");
    return 0;
  }
  
  printf ("\n%llu = (%s ^ -1) %% %s", 
    invmod (_strtoui64(argv[1], NULL, 10), 
      _strtoui64(argv[2], NULL, 10)),
      argv[1], argv[2]);
      
  return 0;
}
