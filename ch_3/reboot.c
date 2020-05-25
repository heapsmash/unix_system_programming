#include <stdio.h>
#include <unistd.h>
#include <linux/reboot.h>
int main(int argc, char **argv)
{
    
    printf("0x%08x\n", LINUX_REBOOT_MAGIC1);
    return 0;
}