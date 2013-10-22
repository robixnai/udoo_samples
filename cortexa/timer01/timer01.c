
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );

extern void uart_send ( unsigned int );
extern unsigned int uart_recv ( void );
extern void hexstring ( unsigned int );
extern void hexstrings ( unsigned int );
extern void  timer_init ( void );

#define GTIMER_LO        0x00A00200
#define GTIMER_HI        0x00A00204
#define GTIMER_CONTROL   0x00A00208

//------------------------------------------------------------------------
int notmain ( void )
{
    hexstring(0x12345678);
    hexstring(GETPC());
    hexstring(0x12345678);
    timer_init();
    while(1)
    {
        hexstrings(GET32(GTIMER_HI));
        hexstring(GET32(GTIMER_LO));
    }
    //return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
