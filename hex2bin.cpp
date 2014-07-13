

// C:\>hex2bin 123123123abcde
//
// You entered: 123123123abcde

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
  unsigned long long num=0;
  
  if (argc != 2) {
    printf ("\nusage: hex2bin <hexadecimal>\n");
    return 0;
  }
  
  char *s=argv[1];
  size_t len=strlen(s);
  int valid=1;
  
  for (size_t i=0; i<len; i++)
  {
    if (isxdigit (tolower(s[i]))) {
      num *= 16;
      if (s[i] >= 'a' && s[i] <= 'f')
        num += s[i] - 'a' + 10;
      else
        num += s[i] - '0';
    } else {
      printf ("\nInvalid character found : %c", s[i]);
      valid=0;
      break;
    }    
  }
  if (valid) printf ("\nYou entered: %llx", num);
  return 0;
}
