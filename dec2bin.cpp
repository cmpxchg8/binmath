
// C:\>dec2bin 123123123
//
// You entered: 123123123

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
  unsigned long long num=0;
  
  if (argc != 2) {
    printf ("\nusage: dec2bin <decimal>\n");
    return 0;
  }
  
  char *s=argv[1];
  size_t len=strlen(s);
  int valid=1;
  
  for (size_t i=0; i<len; i++)
  {
    if (isdigit(s[i])) {
      num *= 10;
      num += s[i] - '0';
    } else {
      printf ("\nInvalid digit found : %c", s[i]);
      valid=0;
      break;
    }    
  }
  if (valid) printf ("\nYou entered: %lld", num);
  return 0;
}
