
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );

#define UART2_BASE  0x21E8000
#define UART2_URXD  (UART2_BASE+0x00)
#define UART2_UTXD  (UART2_BASE+0x40)
#define UART2_UCR1  (UART2_BASE+0x80)
#define UART2_UCR2  (UART2_BASE+0x84)
#define UART2_UCR3  (UART2_BASE+0x88)
#define UART2_UCR4  (UART2_BASE+0x8C)
#define UART2_UFCR  (UART2_BASE+0x90)
#define UART2_USR1  (UART2_BASE+0x94)
#define UART2_USR2  (UART2_BASE+0x98)
#define UART2_UESC  (UART2_BASE+0x9C)
#define UART2_UTIM  (UART2_BASE+0xA0)
#define UART2_UBIR  (UART2_BASE+0xA4)
#define UART2_UBMR  (UART2_BASE+0xA8)
#define UART2_UBRC  (UART2_BASE+0xAC)
#define UART2_ONEMS (UART2_BASE+0xB0)
#define UART2_UTS   (UART2_BASE+0xB4)
#define UART2_UMCR  (UART2_BASE+0xB8)

#define GTIMER_LO        0x00A00200
#define GTIMER_HI        0x00A00204
#define GTIMER_CONTROL   0x00A00208

//------------------------------------------------------------------------
unsigned int uart_recv ( void )
{
    while(1)
    {
        if(GET32(UART2_USR2)&0x01) break;
    }
    return(GET32(UART2_URXD)&0xFF);
}
//------------------------------------------------------------------------
void uart_send ( unsigned int c )
{
    while(1)
    {
        if(GET32(UART2_USR2)&0x4000) break;
    }
    PUT32(UART2_UTXD,c);
}
//------------------------------------------------------------------------
void uart_flush ( void )
{
    while(1)
    {
        if(GET32(UART2_USR2)&0x0008) break;
    }
}
//------------------------------------------------------------------------
void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}
//------------------------------------------------------------------------
void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}
//------------------------------------------------------------------------
void uart_init ( void )
{
}
//------------------------------------------------------------------------
void  timer_init ( void )
{
    PUT32(GTIMER_CONTROL,0);
    PUT32(GTIMER_LO,0);
    PUT32(GTIMER_HI,0);
    PUT32(GTIMER_CONTROL,1);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
