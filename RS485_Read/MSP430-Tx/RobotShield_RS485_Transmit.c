// Program for configuring MAX485 chip of RobotShield V1.0 Booster Pack in Transmisson Mode  

//============================================================================================================//
// The Program transmits a string to PC.The Program configures the MAX485 chip on the RobotShield board       //
// in transmit mode.                                                                                          //
// RS485 communication happens at 9600bps (8N1)                                                               //
//============================================================================================================//
// www.xanthium.in                                                                                            //
// (c) Rahul.S 2015                                                                                           //
//============================================================================================================//
//                                                                                                            //
//  |------------|                                                  MAX485             MSP430G2553            //
//  | RS485 RX   |                                               +------------+       +--------------+        //
//  |            |             USB2SERIAL V2.0                   |          RO|------>|P1.1/RXD      |        //
//  |------------|            |--------------|                   |          DI|<------|P1.2/TXD      |        //
//   \ [][][][][] \===========| USB <- RS485 |~~~~~~~~~~~~~~~~~~~|A,B         |       |              |        //
//    \------------\   USB    |--------------|      Twisted      |          DE|-------|P1.7          |        //
//        Laptop                                     Pair        |	       ~RE|-------|P2.5          |        //
//                                                               +------------+       |              |        //
//                              			                                          |              |        //
//                                                                                    |              |        //
//                                                                                    +--------------+        //
//                                                           [---Robot shield---]   [-----Launchpad-----]     //
//    [Receiver] <------------------------------------   [-----------------Transmitter-------------------]    //
//                                                                                                            //
//============================================================================================================//
// Compiled on IAR Embedded Workbench for MSP430 version 5.30.1                                               //
//                                                                          // 
// Programmer    :	Rahul.S                                                                                   //
// 20-May-2015                                                                                                //      //                                                                                                            //
//============================================================================================================//    
	
	
	
	
	#include "msp430g2553.h"
    void main(void)
    {
      WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog
	  
	  char Text[50] = "Hello From MSP430\n";
      char Count = 0;  
     
      //------------------- Configure the Clocks -------------------//
        
      if (CALBC1_1MHZ==0xFF)   // If calibration constant erased
         {	
            while(1);          // do not load, trap CPU!!
         } 

      DCOCTL  = 0;             // Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ;   // Set range
      DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation 
	  
	  
	  //------------ Configuring MAX485 Control Lines ---------------//
	  
	  P1DIR  |=  BIT7;                // P1.7-> DE Output
      P2DIR  |=  BIT5;                // P2.5 -> ~RE Output
	  
	  //--------- Setting the UART function for P1.1 & P1.2 ---------//
      P1DIR  |=  BIT1 + BIT2;
	  P1SEL  |=  BIT1 + BIT2;  		    // P1.1 UCA0RXD input
      P1SEL2 |=  BIT1 + BIT2;  		    // P1.2 UCA0TXD output
	  
	  //------------ Configuring the UART(USCI_A0) ----------------//
	  
	  UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
      UCA0BR0   =  104;                 // 104 From datasheet table-  
      UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
      UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
      UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
	  
	 //----------------- Put MAX485 in Transmit Mode ---------------//
	  P1OUT  |=  BIT7;                // P1.7-> DE high -> Transmit
      P2OUT  |=  BIT5;                // P2.5 -> ~RE High-> Receive Disabled
	  
	 
	  while(Text[Count] != '\0')
	  {
			while(!(UCA0TXIFG & IFG2));
			UCA0TXBUF = Text[Count]; 
			Count++;
	  }
	  
	  _BIS_SR(LPM0_bits + GIE); // Going to LPM0
	}
