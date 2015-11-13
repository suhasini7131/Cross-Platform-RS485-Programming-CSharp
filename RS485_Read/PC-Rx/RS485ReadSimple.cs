//====================================================================================================//
//   Program to receive the data send from the microcontroller (MSP430G2553) through RS485 network    //
//====================================================================================================//

//====================================================================================================//
// Program opens a  connection to USB2SERIAL board and configures the RS485 chip in Receive mode.     //
// The code then waits for the data send by the microcontroller board.When data is rxed,its displayed //
// on the console.                                                                                    //
//----------------------------------------------------------------------------------------------------//
// BaudRate     -> 9600                                                                               //
// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
// Flow Control -> None                                                                               //
//----------------------------------------------------------------------------------------------------//
// www.xanthium.in										                                              //
// Copyright (C) 2015 Rahul.S                                                                         //
//====================================================================================================//

//==============================================================//
// Please put your COM port number for your USB2SERIAL board at //
//       COMPort.PortName = "COM91";                            //
// Instead of "COM91"                                           //
//==============================================================//

using System;
using System.IO.Ports;//namespace containing SerialPort class

namespace USB2SERIAL_RS485_Read
{
  class RS485_Read
  {
   static void Main(string[] args)
   {
     string RxedData;                      // Variable for Holding received data
     SerialPort COMPort = new SerialPort();// Create a SerialPort Object called COMPort

     COMPort.PortName = "COM91";           // Assign the COM port number
	 
	 //COMPort.PortName = "/dev/ttyUSB0";  //On Linux Systems,here ttyUSB0 is the USB2SERIAL port number
	 
     COMPort.BaudRate = 9600;              // Set Baud rate = 9600
     COMPort.DataBits = 8;                 // Number of data bits = 8
     COMPort.Parity   = Parity.None;       // No parity
     COMPort.StopBits = StopBits.One;      // One stop bit

     COMPort.Open();                       // Open the serial port
     //Put USB2SERIAL in Receive Mode       
     COMPort.RtsEnable = true;            // Since RTS = 1, ~RTS = 0 So ~RE = 0 Receive  Mode enabled
     COMPort.DtrEnable = true;            // Since DTR = 1. ~DTR = 0 So  DE = 0 
                                          // ~RE and DE LED's on USB2SERIAL board will be off
     RxedData = COMPort.ReadLine();       // Wait for data reception
     Console.WriteLine("\n\t \" {0} \" ", RxedData); 
     Console.Read();
   }
  }
}