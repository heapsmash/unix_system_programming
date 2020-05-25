#include <gnu/libc-version.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  
  puts(gnu_get_libc_version());

  return 0; 
}
