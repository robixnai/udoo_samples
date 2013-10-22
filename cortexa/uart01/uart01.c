
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

//------------------------------------------------------------------------
int notmain ( void )
{
    hexstring(0x12345678);
    hexstring(GETPC());
    hexstring(0x12345678);
    while(1) uart_send(uart_recv());
    //return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
