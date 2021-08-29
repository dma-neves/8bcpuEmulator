
int tick();
void printState();

void add(unsigned char rx, unsigned char ry);
void sub(unsigned char rx, unsigned char ry);
void ssp(unsigned char v);
void inc(unsigned char rx);
void dec(unsigned char rx);
void neg(unsigned char rx);
void not(unsigned char rx);
void and(unsigned char rx, unsigned char ry);
void or(unsigned char rx, unsigned char ry);
void lod_v_adr(unsigned char v);
void str_v_madr(unsigned char v);
void lod_madr_rx(unsigned char rx);
void str_rx_madr(unsigned char rx);
void lod_rx_adr(unsigned char rx);
void lod_acr_rx(unsigned char rx);
void lod_acr_adr();
void str_acr_madr();
void str_ic_madr();
void jmp_adr();
void jmp(unsigned char x);
void jmpz(unsigned char x);
void jmpn(unsigned char x);
void jmpo(unsigned char x);