#include <stdio.h>

int regs[8];
int ic, acr, adr;
int mem[256];

#define SP 0x7

int tick()
{
    return ic++;
}

void printState()
{
    printf("RA: %d RB: %d RC: %d RD: %d RE: %d RF: %d RG: %d\n", regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6]);
    printf("SP: %d\n", regs[SP]);
    printf("IC: %d\n", ic);
    printf("ADR: %d\n", adr);
    printf("ACR: %d\n", acr);
    printf("\nstack:\n");
    for(int i = 0; i < regs[SP]; i++)
        printf("%d: %d\n", i, mem[i]);
}

void add(unsigned char rx, unsigned char ry)
{
    acr = regs[rx] + regs[ry];
}

void sub(unsigned char rx, unsigned char ry)
{
    acr = regs[rx] - regs[ry];
}

void ssp(unsigned char v)
{
    acr = regs[SP] - v;
}

void inc(unsigned char rx)
{
    acr = regs[rx] + 1;
}

void dec(unsigned char rx)
{
    acr = regs[rx] - 1;
}

void neg(unsigned char rx)
{
    acr = -regs[rx];
}

void not(unsigned char rx)
{
    acr = ~regs[rx];
}

void and(unsigned char rx, unsigned char ry)
{
    acr = regs[rx] & regs[ry];
}

void or(unsigned char rx, unsigned char ry)
{
    acr = regs[rx] | regs[ry];
}

void lod_v_adr(unsigned char v)
{
    adr = v;
}

void str_v_madr(unsigned char v)
{
    mem[adr] = v;
}

void lod_madr_rx(unsigned char rx)
{
    regs[rx] = mem[adr];
}

void str_rx_madr(unsigned char rx)
{
    mem[adr] = regs[rx];
}

void lod_rx_adr(unsigned char rx)
{
    adr = regs[rx];
}

void lod_acr_rx(unsigned char rx)
{
    regs[rx] = acr;
}

void lod_acr_adr()
{
    adr = acr;
}

void str_acr_madr()
{
    mem[adr] = acr;
}

void str_ic_madr()
{
    mem[adr] = ic;
}

void jmp_adr()
{
    ic = adr+1;
}

void jmp(unsigned char x)
{
    ic = x+1;
}

void jmpz(unsigned char x)
{
    if(acr == 0) ic = x+1;
}

void jmpn(unsigned char x)
{
    if(acr < 0) ic = x+1;
}

void jmpo(unsigned char x)
{
    if(acr >= 256) ic = x+1;
}