/*unsigned int mcd (unsigned int m, unsigned int n)*/

#include <sys/regdef.h>

//stack size
#define MCD_SS 16

//ABA del caller
#define MCD_A3 28
#define MCD_A2 24
#define MCD_A1 20
#define MCD_A0 16

//SRA
#define MCD_FP 12
#define MCD_GP 8 

//LTA
#define MCD_N 4
#define MCD_M 0

.text
.align 2
.globl mcd
.ent mcd

mcd:
subu sp, sp, MCD_SS
sw fp, MCD_FP(sp)
sw gp, MCD_GP(sp)
move fp, sp

sw a0, MCD_A0(fp)
sw a1, MCD_A1(fp)

lw t0, MCD_A0(fp)
lw t1, MCD_A1(fp)

while:
beqz t1, endwhile
rem t2, t0, t1
move t0, t1
move t1, t2
j while
endwhile:

return:
move v0, t0

move fp, sp
lw gp, MCD_GP(sp)
lw fp, MCD_FP(sp)
addiu sp, sp, MCD_SS

jr ra
.end mcd


