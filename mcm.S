/*unsigned int mcm (unsigned int m, unsigned int n)*/

#include <sys/regdef.h>

#define MCM_SS 44 

//ABA del caller
#define MCM_A3 60
#define MCM_A2 52
#define MCM_A1 48
#define MCM_A0 44

//SRA
#define MCM_FP 36
#define MCM_GP 32
#define MCM_RA 24

//LTA
#define MCM_MN 20
#define MCM_MCD_RESULT 16

//ABA
#define MCM_ABA_A3 12
#define MCM_ABA_A2 8
#define MCM_ABA_A1 4
#define MCM_ABA_A0 0

.text
.align 2
.extern mcd
.globl mcm
.ent mcm

mcm:
subu sp, sp, MCM_SS
sw fp, MCM_FP(sp)
sw gp, MCM_GP(sp)
sw ra, MCM_RA(sp)
move fp, sp

sw a0, MCM_A0(fp)
sw a1, MCM_A1(fp)

lw t0, MCM_A0(fp)
lw t1, MCM_A1(fp)

mul t0, t0, t1
sw t0, MCM_MN(fp)

lw a0, MCM_A0(fp)
lw a1, MCM_A1(fp)
jal mcd
sw v0, MCM_MCD_RESULT(fp)

lw ra, MCM_RA(fp)

lw t0, MCM_MN(fp)
lw t1, MCM_MCD_RESULT(fp)
div v0, t0, t1

return:

move fp, sp
lw gp, MCM_GP(sp)
lw fp, MCM_FP(sp)
addiu sp, sp, MCM_SS

jr ra
.end mcm
