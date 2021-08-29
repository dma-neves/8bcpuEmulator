#include <stdio.h>
#include <sys/stat.h>

#include "cpu.h"
#include "isa.h"

void printInstruction(unsigned char inst);

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("usage: ./emulator binaryFile mode\n");
        printf("mode can be set to e (execute the whole program) or s (step through every instruction)\n");
    }
    else
    {

        char* fileName = argv[1];
        char* mode = argv[2];
        char step = mode[0] == 's';

        struct stat sb;
        if (stat(fileName, &sb) == -1)
            perror("stat");

        unsigned char bytes[sb.st_size];
        FILE* f = fopen(fileName, "r");
        fread(bytes, sb.st_size, 1, f);
        fclose(f);

        unsigned char inst;
        unsigned char data;

        do
        {
            inst = bytes[tick()];
            data = bytes[tick()];
            unsigned char lowb = data & 0xF;
            unsigned char highb = (data & 0xF0) >> 4;

            switch (inst)
            {
                case ADD_RX_RY: add(lowb, highb); break;
                case SUB_RX_RY: sub(lowb, highb); break;
                case SSP_V: ssp(data); break;
                case INC_RX: inc(data); break;
                case DEC_RX: dec(data); break;
                case NEG_RX: neg(data); break;
                case NOT_RX: not(data); break;
                case AND_RX_RY: and(lowb, highb); break;
                case OR_RX_RY: or(lowb, highb); break;
                case LOD_V_ADR: lod_v_adr(data); break;
                case STR_V_MADR: str_v_madr(data); break;
                case LOD_MADR_RX: lod_madr_rx(data);
                case STR_RX_MADR: str_rx_madr(data); break;
                case LOD_RX_ADR: lod_rx_adr(data); break;
                case LOD_ACR_RX: lod_acr_rx(data); break;
                case LOD_ACR_ADR: lod_acr_adr(); break;
                case STR_ACR_MADR: str_acr_madr(); break;
                case STR_IC_MADR: str_ic_madr(); break;
                case JMP_ADR: jmp_adr(); break;
                case JMP_X: jmp(data); break;
                case JMPZ_X: jmpz(data); break;
                case JMPN_X: jmpn(data); break;
                case JMPO_X: jmpo(data); break;
            }

            if(step)
            {
                printInstruction(inst);
                printf("data: %d lowByte: %d highByte: %d\n", data, lowb, highb);
                printState();
                printf("\n");
                getchar();
            }
        }
        while(inst != HLT);

        if(!step) printState();
    }
}

void printInstruction(unsigned char inst)
{
    switch(inst) 
    {
            case ADD_RX_RY: printf("instruction: add RX RY\n"); break;
			case SUB_RX_RY: printf("instruction: sub RX RY\n"); break;
			case SSP_V: printf("instruction: ssp $V\n"); break;
			case INC_RX: printf("instruction: inc RX\n"); break;
			case DEC_RX: printf("instruction: dec RX\n"); break;
			case NEG_RX: printf("instruction: neg RX\n"); break;
			case NOT_RX: printf("instruction: not RX\n"); break;
			case AND_RX_RY: printf("instruction: and RX RY\n"); break;
			case OR_RX_RY: printf("instruction: or RX RY\n"); break;
			case LOD_V_ADR: printf("instruction: lod $V ADR\n"); break;
			case STR_V_MADR: printf("instruction: str $V [ADR]\n"); break;
			case LOD_MADR_RX: printf("instruction: lod [ADR] RX\n"); break;
			case STR_RX_MADR: printf("instruction: str RX [ADR]\n"); break;
			case LOD_RX_ADR: printf("instruction: lod RX ADR\n"); break;
			case LOD_ACR_RX: printf("instruction: lod ACR RX\n"); break;
			case LOD_ACR_ADR: printf("instruction: lod ACR ADR\n"); break;
			case STR_ACR_MADR: printf("instruction: str ACR [ADR]\n"); break;
			case STR_IC_MADR: printf("instruction: str IC [ADR]\n"); break;
			case JMP_ADR: printf("instruction: jmp ADR\n"); break;
			case JMP_X: printf("instruction: jmp X\n"); break;
			case JMPZ_X: printf("instruction: jmpz X\n"); break;
			case JMPN_X: printf("instruction: jmpn X\n"); break;
			case JMPO_X: printf("instruction: jmpo X\n"); break;
			case HLT: printf("instruction: hlt\n"); break;
            default: printf("inst: %d\n", inst); break;
    }
}