/*
 * File:   stepper_init.c
 * Author: Erik Sarkinen
 *
 * Created on February 12, 2022, 8:26 AM
 */


#include <xc.h>
#include <stdio.h>
#include <p33ep32mc202.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void stepper_init(void)
{
    int i = 0;
    OSCCONbits.NOSC0 = 0;       //Fast RC Oscillator
    OSCCONbits.NOSC1 = 0;       //Fast RC Oscillator
    OSCCONbits.NOSC2 = 0;       //Fast RC Oscillator
    OSCCONbits.OSWEN = 1;       //Requests oscillator switch to selection specified by the NOSC[2:0] bits
    OSCTUN = 0;         //Center frequency 7.37 MHz
 //   CLKDIVbits.PLLPOST = 0;     //Output divided by 2
   // CLKDIVbits.PLLPRE = 0;      //Input divided by 2
    //PLLFBD = 48;                 //50 is the PLL multiplier
    RPINR18 = 0b0000000000100110;       //U1RX = RP38
    RPOR3 = 0b0000000000000001;     //, U1_TX = RP40
  
    /*
    TRISBbits.TRISB9 = 0;       //TX
    TRISBbits.TRISB8 = 1;       //RX
    TRISBbits.TRISB4 = 0;      //SW Buttonfor motor board
    TRISAbits.TRISA2 = 0;      //Wakeup for motor board
    TRISAbits.TRISA3 = 0;       //EAN for motor board
    TRISAbits.TRISA0 = 0;       //P2_0  for motor board
    TRISAbits.TRISA1 = 0;      //P2_4 for motor board
    LATBbits.LATB4 = 1;        //SW button  = On for motor board
    
    TRISBbits.TRISB2 = 0;       //Left direction
    TRISBbits.TRISB3 = 0;       //Right direction
    TRISBbits.TRISB11 = 0;      //MS1   Full Step
    TRISBbits.TRISB10 = 0;      //MS2   Full Step
    
    ANSELA=0;
    ANSELB=0;
     * */
    
            ///////////////////UART1/////////////////////////////////////////////
    U1MODEbits.UARTEN = 0;      //UART1 is disabled
    TRISBbits.TRISB6 = 1;       //U1 RX
    TRISBbits.TRISB8 = 1;       //U1 TX
    U1MODEbits.USIDL = 0;       //Continue module operation in Idle mode
    U1MODEbits.IREN = 0;        //IrDA encoder and decoder disabled
    U1MODEbits.UEN0 = 0;        //U1TX and RX pins are enabled and used. 
    U1MODEbits.UEN1 = 0;        //CTS and RTS pins are controlled by PORT latches
    U1MODEbits.WAKE = 0;        //UART1 continues to sample the U1RX pin; interrupt is generated on the falling edge
    U1MODEbits.LPBACK = 0;      //Loopback mode is disabled
    U1MODEbits.ABAUD = 0;       //Auto-Baud disabled
    U1MODEbits.URXINV = 0;      //Idle state is '0'
    U1MODEbits.BRGH = 1;        //High Speed
    U1MODEbits.PDSEL1 = 0;      //8-bit data, no parity
    U1MODEbits.URXINV = 0;      //Bit4 IdleState = 1  (for dsPIC)
    U1MODEbits.RTSMD = 0;       //Bit11 Simplex Mode
    U1MODEbits.PDSEL0 = 0;      
    U1MODEbits.STSEL = 0;       //One stop bit 
    INTCON2bits.GIE = 1;        //Global interrupt enable bit (enabled)
    IEC0bits.U1RXIE = 1;        //UART 2 interrupt enabled 
    IFS0bits.U1RXIF = 0;        //Reset RX interrupt flag 
    IPC2bits.U1RXIP = 7;        //Set RX interrupt priority to high priority
    U1STAbits.URXISEL1 = 0;     //Interrupt is set when there is 1 char
    U1STAbits.URXISEL0 = 0;     
    U1STAbits.ADDEN = 0;          //Address detect mode disabled
    U1STAbits.PERR = 0;         //Parity Error
    U1STAbits.OERR = 0;           //Clear the Receive //Overflow Flag.
    U1BRG = 95;                 //BAUD RATE 9,600 Fosc = 7.37 Mhz, Fp = Fosc/2
    IEC0bits.U1TXIE = 0;        //No transmit interrupt (We poll TRMT)
    U1MODEbits.UARTEN = 1;      //UART1 is enabled
   // U1STAbits.UTXEN = 1;        //Transmit enabled
   /*
    ////////////////PWM Initialization///////////////////////////////
    PTCONbits.PTEN = 0;         //PWM Module is disabled before any code
    
    TRISBbits.TRISB15 = 0;      //PWM1L is an output
    TRISBbits.TRISB14 = 0;      //PWM1H is an output
    TRISBbits.TRISB13 = 0;      //PWM2L is an output
    TRISBbits.TRISB12 = 0;      //PWM2H is an output
    TRISBbits.TRISB11 = 0;      //PWM3L is an output
    TRISBbits.TRISB10 = 0;      //PWM3H is an output
    PORTBbits.RB15 = 0;         //Clear the output pin
    PORTBbits.RB14 = 0;         //Clear the output pin
    PORTBbits.RB13 = 0;         //Clear the output pin
    PORTBbits.RB12 = 0;         //Clear the output pin
    PORTBbits.RB11 = 0;         //Clear the output pin
    PORTBbits.RB10 = 0;         //Clear the output pin
    
    PTCONbits.SYNCOEN = 0;      //SYNCO1 output is enabled
    PTCONbits.SYNCEN = 0;       //External synchronization of primary time base is disabled
    PTCONbits.SYNCSRC0 = 0;     //Synchronous Source is PTGO17
    PTCONbits.SYNCSRC1 = 1;
    PTCONbits.SYNCSRC2 = 0;
    PTCON2bits.PCLKDIV0 = 0;      //110 divide by 64 prescaler *Adjust this depending on speed
    PTCON2bits.PCLKDIV1 = 1;
    PTCON2bits.PCLKDIV2 = 1;
    PTCONbits.PTSIDL = 0;
    PTCONbits.EIPU = 0;
    PTCONbits.SYNCPOL = 0;
    PWMCON1bits.ITB = 1;        //PHASE1 register provides timing for this PWM generator
    PWMCON2bits.ITB = 1;        //PHASE2 register provides timing for this PWM generator
    PWMCON3bits.ITB = 1;        //PHASE3 register provides timing for this PWM generator
    PWMCON1bits.MDCS = 0;       //PDC1 register provide duty cycle information for this PWM generator
    PWMCON2bits.MDCS = 0;       //PDC2 register provide duty cycle information for this PWM generator
    PWMCON3bits.MDCS = 0;       //PDC3 register provide duty cycle information for this PWM generator
    PWMCON1bits.FLTIEN = 0;     //Fault interrupt disabled
    PWMCON2bits.FLTIEN = 0;     //Fault interrupt disabled
    PWMCON1bits.TRGIEN = 0;     //Trigger interrupt disabled
    PWMCON2bits.TRGIEN = 0;     //Trigger interrupt disabled
    PWMCON1bits.CLIEN = 0;      //Current limit interrupt disabled
    PWMCON2bits.CLIEN = 0;      //Current limit interrupt disabled
    PWMCON1bits.MTBS = 0;       //Primary master time base
    PWMCON2bits.MTBS = 0;       //Primary master time base
    PWMCON1bits.CAM = 0;        //Edge aligned
    PWMCON2bits.CAM = 0;        //Edge aligned
    PWMCON3bits.CAM = 0;        //Edge aligned
    PWMCON1bits.FLTSTAT = 0;    //No fault interrupt is pending
    PWMCON2bits.FLTSTAT = 0;    //No fault interrupt is pending
    PWMCON1bits.DTC = 0;
    PWMCON2bits.DTC = 0;
    PWMCON1bits.XPRES = 0;
    PWMCON2bits.XPRES = 0;
    PWMCON1bits.IUE = 0;
    PWMCON2bits.IUE = 0;
    PWMCON1bits.DTC = 2;
    PWMCON2bits.DTC = 2;
    IOCON1bits.PENL = 1;        //PWM module controls PWM1L pin
    IOCON2bits.PENL = 1;        //PWM module controls PWM2L pin
    IOCON1bits.PENH = 1;        //PWM module controls PWM1H pin
    IOCON2bits.PENH = 1;        //PWM module controls PWM2H pin
    IOCON3bits.PENH = 1;        //PWM module controls PWM3H pin
    IOCON3bits.PENL = 1;        //PWM module controls PWM3L pin
    IOCON1bits.PMOD0 = 1;       //Pin pair is in the redundant output mode
    IOCON1bits.PMOD1 = 0;       //Pin pair is in the redundant output mode
    IOCON2bits.PMOD0 = 1;       //Pin pair is in the redundant output mode
    IOCON2bits.PMOD1 = 0;       //Pin pair is in the redundant output mode
    IOCON3bits.PMOD0 = 1;       //Pin pair is in the redundant output mode
    IOCON3bits.PMOD1 = 0;       //Pin pair is in the redundant output mode
    IOCON1bits.OVRENH = 0;      //PWM generator controls pin
    IOCON1bits.OVRENL = 0;      //PWM generator controls pin
    IOCON2bits.OVRENH = 0;      //PWM generator controls pin
    IOCON2bits.OVRENL = 0;      //PWM generator controls pin
    IOCON3bits.OVRENL = 0;      //PWM generator controls pin
    IOCON3bits.OVRENH = 0;      //PWM generator controls pin
    IOCON1bits.POLH = 0;
    IOCON1bits.POLL = 0;
    IOCON2bits.POLH = 0;
    IOCON2bits.POLL = 0;
    IOCON3bits.POLH = 0;
    IOCON3bits.POLL = 0;
    IOCON1bits.SWAP = 0;
    IOCON2bits.SWAP = 0;
    IOCON3bits.SWAP = 0;
    IOCON1bits.OSYNC = 0;
    IOCON2bits.OSYNC = 0;
    IOCON3bits.OSYNC = 0;
    IOCON1bits.OVRDAT = 0;
    IOCON2bits.OVRDAT = 0;
    IOCON3bits.OVRDAT = 0;
    
    PTCONbits.SEIEN = 0;        //Special event interrupt disabled
    

    //PHASE1 = 1999999;
    //PHASE2 = 1999999;
    DTR1 = 0;
    DTR2 = 0;
    ALTDTR1 = 0;
    ALTDTR2 = 0;
    FCLCON1 = 0x0000;
    FCLCON2 = 0x0000;
    FCLCON1bits.FLTMOD = 3;
    FCLCON2bits.FLTMOD = 3;
 //   TRIG1 = 1568;
 //   TRIG2 = 1568;
    
 //   TRGCON1bits.TRGDIV = 7;     //Trigger output for every 8th trigger event
 //   TRGCON2bits.TRGDIV = 7;     //Trigger output for every 8th trigger event
    PTCONbits.PTEN = 1;         //PWM Module is enabled
    */

    return;
}
    /*
    ///////////////////UART/////////////////////////////////////////////
    U1MODEbits.UARTEN = 0;      //UART1 is disabled
    U1MODEbits.USIDL = 0;       //Continue module operation in Idle mode
    U1MODEbits.IREN = 0;        //IrDA encoder and decoder disabled
    U1MODEbits.UEN0 = 0;        //U1TX and RX pins are enabled and used. 
    U1MODEbits.UEN1 = 0;        //CTS and RTS pins are controlled by PORT latches
    U1MODEbits.WAKE = 0;        //UART1 continuse to sample the U1RX pin; interrupt is generated on the falling edge
    U1MODEbits.LPBACK = 0;      //Loopback mode is disabled
    U1MODEbits.ABAUD = 0;       //Auto-Baud disabled
    U1MODEbits.URXINV = 0;      //Idle state is '0'
    U1MODEbits.BRGH = 1;        //High Speed
    U1MODEbits.PDSEL1 = 0;      //8-bit data, no parity
    U1MODEbits.URXINV = 0;  // Bit4 IdleState = 1  (for dsPIC)
    U1MODEbits.RTSMD = 0;   // Bit11 Simplex Mode
    U1MODEbits.PDSEL0 = 0;      
    U1MODEbits.STSEL = 0;       //One stop bit 
    INTCON2bits.GIE = 1;        //Global interrupt enable bit
//    INTCON2bits.INT1EP = 1;     //Interrupt on negative edge
//    INTCON2bits.INT0EP = 1;     //Interrupt on negative edge
    IEC0bits.U1RXIE = 1;        //UART 1 interrupt enable  
    IPC2bits.U1RXIP  = 2;        //Set RX interrupt priority to high priority
    IFS0bits.U1RXIF = 0;         //Reset RX interrupt flag 
    U1STAbits.URXISEL1 = 0;     //Interrupt is set when there is 1 char
    U1STAbits.URXISEL0 = 0;     
    U1STAbits.ADDEN = 0;          //Address detect mode disabled
    U1STAbits.PERR = 0;         //Parity Error
    U1BRG = 7;                 //BAUD RATE 115,200 Fosc = 7.37 Mhz, Fp = Fosc/2
    IEC0bits.U1TXIE = 0;        //No transmit interrupt (We poll TRMT)
    U1MODEbits.UARTEN = 1;      //UART1 is enabled
    U1STAbits.UTXEN = 1;        //Transmit enabled
*/
    
    //////////////////////////////////////////////////////////////////////////

 
    /*
    //PWM Initialization
    TRISBbits.TRISB15 = 0;      //PWM1L is an output
    TRISBbits.TRISB14 = 0;      //PWM1H is an output
    TRISBbits.TRISB13 = 0;      //PWM2L is an output
    TRISBbits.TRISB12 = 0;      //PWM2H is an output
    PORTBbits.RB15 = 0;         //Clear the output pin
    PORTBbits.RB14 = 0;         //Clear the output pin
    PORTBbits.RB13 = 0;         //Clear the output pin
    PORTBbits.RB12 = 0;         //Clear the output pin
    
    PTCONbits.PTEN = 0;         //PWM Module is disabled before any code
    PTCONbits.SYNCOEN = 1;      //SYNCO1 output is disabled
    PTCONbits.SYNCEN = 0;       //External synchronization of primary time base is disabled
    PTCONbits.SYNCSRC0 = 1;     //Synchronous Source is PTGO17
    PTCONbits.SYNCSRC1 = 1;
    PTCONbits.SYNCSRC2 = 0;
    PTCON2bits.PCLKDIV0 = 0;      //100 divide by 16 prescaler *Adjust this depending on speed
    PTCON2bits.PCLKDIV1 = 0;
    PTCON2bits.PCLKDIV2 = 1;
    PTPER = 19999;              //Time base is 1 ms with fosc 80 Mhz *Adjust this depending on speed
    PWMCON1bits.ITB = 0;        //PTPER register provides timing for this PWM generator
    PWMCON2bits.ITB = 0;        //PTPER register provides timing for this PWM generator
    PWMCON1bits.MDCS = 0;       //PDC1 register provide duty cycle information for this PWM generator
    PWMCON2bits.MDCS = 0;       //PDC1 register provide duty cycle information for this PWM generator
    IOCON1bits.PENL = 1;        //PWM module controls PWM1L pin
    IOCON2bits.PENL = 1;        //PWM module controls PWM2L pin
    IOCON1bits.PENH = 1;        //PWM module controls PWM1H pin
    IOCON2bits.PENH = 1;        //PWM module controls PWM2H pin
    IOCON2bits.PMOD0 = 1;       //Pin pair is in the redundant output mode
    IOCON2bits.PMOD1 = 0;       //Pin pair is in the redundant output mode
    
    
    
    PTCONbits.PTEN = 1;         //PWM Module is enabled
    */
   // return;
    
      //  LATAbits.LATA2 = 1;     //Wakeup
    
    /*
    LATBbits.LATB2 = 0;     //EAN
    LATBbits.LATB14 = 1;    //P2_0
    LATBbits.LATB3 = 1;     //P2_4
    LATBbits.LATB11 = 1;    //SW Button
    LATBbits.LATB12 = 1;    //Wakeup
    */
    /*
        ///////////////////UART/////////////////////////////////////////////
    U2MODEbits.UARTEN = 0;      //UART1 is disabled
    U2MODEbits.USIDL = 0;       //Continue module operation in Idle mode
    U2MODEbits.IREN = 0;        //IrDA encoder and decoder disabled
    U2MODEbits.UEN0 = 0;        //U1TX and RX pins are enabled and used. 
    U2MODEbits.UEN1 = 0;        //CTS and RTS pins are controlled by PORT latches
    U2MODEbits.WAKE = 0;        //UART1 continuse to sample the U1RX pin; interrupt is generated on the falling edge
    U2MODEbits.LPBACK = 0;      //Loopback mode is disabled
    U2MODEbits.ABAUD = 0;       //Auto-Baud disabled
    U2MODEbits.URXINV = 0;      //Idle state is '0'
    U2MODEbits.BRGH = 1;        //High Speed
    U2MODEbits.PDSEL1 = 0;      //8-bit data, no parity
    U2MODEbits.URXINV = 0;  // Bit4 IdleState = 1  (for dsPIC)
    U2MODEbits.RTSMD = 0;   // Bit11 Simplex Mode
    U2MODEbits.PDSEL0 = 0;      
    U2MODEbits.STSEL = 0;       //One stop bit 
    INTCON2bits.GIE = 1;        //Global interrupt enable bit
//    INTCON2bits.INT1EP = 1;     //Interrupt on negative edge
//    INTCON2bits.INT0EP = 1;     //Interrupt on negative edge
    IEC1bits.U2RXIE;        //UART 2 interrupt enable  
    IPC7bits.U2RXIP = 2;        //Set RX interrupt priority to high priority
    IFS1bits.U2RXIF = 0;       //Reset RX interrupt flag 
    U2STAbits.URXISEL1 = 0;     //Interrupt is set when there is 1 char
    U2STAbits.URXISEL0 = 0;     
    U2STAbits.ADDEN = 0;          //Address detect mode disabled
    U2STAbits.PERR = 0;         //Parity Error
    U2BRG = 7;                 //BAUD RATE 115,200 Fosc = 7.37 Mhz, Fp = Fosc/2
    IEC1bits.U2TXIE = 1;        //No transmit interrupt (We poll TRMT)
    U2MODEbits.UARTEN = 1;      //UART1 is enabled
    U2STAbits.UTXEN = 1;        //Transmit enabled
  */  

