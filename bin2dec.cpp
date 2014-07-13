
// printf result = 1234567891234
// bin2dec result= 1234567891234

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
  unsigned long long num=1234567891234;
  char buf[256]={0};
  char *p=buf;
  size_t len;
  
  printf ("\nprintf result = %lld", num);
  printf ("\nbin2dec result= ");
  
  while (num != 0) {
    *p++ = (num % 10) + '0';
    num /= 10;
  }
  len=p-buf;
  while (len--) {
    printf ("%c", buf[len]);
  }
  return 0;
}
