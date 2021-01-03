#include "stdio.h"

//configuration registers
typedef enum
{
    IOCFG3 = 0x00,
    IOCFG2 = 0x01,
    IOCFG1 = 0x02,
} registers;

int main()
{
    printf("Hello World!\n");
    printf("%d\n", IOCFG2);
}