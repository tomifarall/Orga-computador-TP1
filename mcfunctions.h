#ifndef MCFUNCTIONS
#define MCFUNCTIONS

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef USE_MIPS32

unsigned int mcm(unsigned int m, unsigned int n);
unsigned int mcd(unsigned int m, unsigned int n);

#else 

extern unsigned int mcm(unsigned int m, unsigned int n);
extern unsigned int mcd(unsigned int m, unsigned int n);

#endif /* USE_MIPS32 */ 


#endif /* MCFUNCTIONS */