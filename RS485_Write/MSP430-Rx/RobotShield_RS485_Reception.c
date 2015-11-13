// Program for configuring MAX485 chip of RobotShield V1.0 Booster Pack in Reception Mode  

//============================================================================================================//
// The Program acts as a slave to the software running on the PC.The Program configures the MSP430 UART to-   //
// wait for data coming from the PC.It puts the MAX485 chip on the RobotShield board in receive mode-         //
// and switches on the LED's connected to P2.1 and P2.2                                                       //
// RS485 communication happens at 9600bps (8N1)                                                               //
//============================================================================================================//
// www.xanthium.in                                                                                            //
// (c) Rahul.S 2015                                                                                           //
//============================================================================================================//
//                                                                                                            //
//  |------------|                                                  MAX485             MSP430G2553            //
//  | RS485 Tx   |                                               +------------+       +--------------+        //
//  |            |             USB2SERIAL V2.0                   |          RO|------>|P1.1/RXD      |        //
//  |------------|            |--------------|                   |          DI|<------|P1.2/TXD      |        //
//   \ [][][][][] \===========| USB -> RS485 |~~~~~~~~~~~~~~~~~~~|A,B         |       |              |        //
//    \------------\   USB    |--------------|      Twisted      |          DE|-------|P1.7          |        //
//        Laptop                                     Pair        |	       ~RE|-------|P2.5          |        //
//                                                               +------------+       |              |        //
//                              			                                          |              |        //
//                                                                                    |              |        //
//                                                                         (LED1)-----|P2.1          |        //
//                                                                         (LED2)-----|P2.2          |        //
//                                                                                    |              |        //
//                                                                                    +--------------+        //
//                                                           [---Robot shield---]   [-----Launchpad-----]     //
//    [Transmitter] ------------------------------------>   [-----------------Receiver-------------------]    //
//                                                                                                            //
//============================================================================================================//
// Compiled on IAR Embedded Workbench for MSP430 version 5.30.1                                               //
//                                                                          // 
// Programmer    :	Rahul.S                                                                                   //
// 20-May-2015                                                                                                //                                                                                                  //
//============================================================================================================//



	#include "msp430g2553.h"
	void main(void)
	{
		WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog
     
		//------------------- Configure the Clocks -------------------//
        
		if (CALBC1_1MHZ==0xFF)   // If calibration constant erased
		{	
			while(1);          // do not load, trap CPU!!
		} 
		DCOCTL  = 0;             // Select lowest DCOx and MODx settings
		BCSCTL1 = CALBC1_1MHZ;   // Set range
		DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation 
       
		//------------------- Configure the Ports  -------------------//
      
		// Setting the UART function for P1.1 & P1.2
		P1SEL  |=  BIT1 + BIT2;  		// P1.1 UCA0RXD input
		P1SEL2 |=  BIT1 + BIT2;  		// P1.2 UCA0TXD output
        
		// Setting the ports for MAX485 control
		 P1DIR  |=  BIT7;                // P1.7-> DE Output
         P2DIR  |=  BIT5;                // P2.5 -> ~RE Output
		 
		 P1OUT  &= ~BIT7;                // P1.7 = 0 
		 P2OUT  &= ~BIT5;                // P2.5 = 0, Receive Mode
		 
		//LED control for RS485 
		P2DIR   = 0xFF; // Port 2 all pins output
		P2OUT   = 0x00;
		
		P2OUT &=  ~BIT1; //Switch off P2.1 LED
        P2OUT &=  ~BIT2; //Switch off P2.2 LED
		
		P2OUT &= ~BIT0 + BIT6; // Both motors Off,P2.0 = P2.6 = 0,
		
		//-------------- Configure USCI_A0 in UART mode --------------//  
      
		UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
		UCA0BR0   =  104;                 //  104 From datasheet table-  
		UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
		UCA0MCTL  =  UCBRS_6;             // Modulation value = 6 from datasheet
      
		UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
      
		//-------------- Configure USCI_A0 interrupts  --------------// 
      
		IE2 |= UCA0RXIE;                 //Enable Recieve interrupt            
      
		_BIS_SR(LPM0_bits + GIE);        // Going to LPM0
        
		}//end of main()

		//-----------------   USCI_A0 Recieve ISR    --------------------------//

		#pragma vector = USCIAB0RX_VECTOR
		__interrupt void USCI_A0_RecieveInterrupt(void)
		{
			IFG2 &= ~UCA0RXIFG; //Clear the UCA0RXIFG
			
			switch(UCA0RXBUF) // Switch to control P2.1 and P2.2
				{
					case 'A': P2OUT |=  BIT1; //Switch on P2.1 LED
					          P2OUT |=  BIT2; //Switch on P2.2 LED
							  break;
				}//end of switch
		}//end of ISR