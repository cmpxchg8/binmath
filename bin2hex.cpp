

// printf result = 123456789ABCDEF
// bin2hex result= 123456789ABCDEF

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
  unsigned long long num=0x123456789abcdef;
  char buf[256]={0};
  char *p=buf;
  size_t len;
  
  printf ("\nprintf result = %llX", num);
  printf ("\nbin2hex result= ");
  
  while (num != 0) {
    unsigned long long c = num % 16;
    *p++ = (c < 10 ? (c + '0') : (c + '7'));   // lowercase can be (c + 'a' - 10)
    num /= 16;
  }
  len=p-buf;
  while (len--) {
    printf ("%c", buf[len]);
  }
  return 0;
}
