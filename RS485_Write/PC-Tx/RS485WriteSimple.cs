//====================================================================================================//
//   Program to transmit data to the microcontroller (MSP430G2553) through RS485 network              //
//====================================================================================================//


//====================================================================================================//
// Program opens a  connection to USB2SERIAL board and configures the RS485 chip in transmit mode.    //
// The code then sends character 'A' to the microcontroller through RS485 network.The Micro controller//
// receives the data and lights up an LED connected to its Port                                       //
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
using System.IO.Ports; // for accessing SerialPort Class

namespace USB2SERIAL_RS485_Write
{
    class RS485Write
    {
        static void Main(string[] args)
        {
            SerialPort COMPort = new SerialPort();// Create a SerialPort Object called COMPort

            COMPort.PortName = "COM91";           // Assign the COM port number
			
			//COMPort.PortName = "/dev/ttyUSB0";  //On Linux Systems,here ttyUSB0 is the USB2SERIAL port number
			
            COMPort.BaudRate = 9600;              // Set Baud rate = 9600
            COMPort.DataBits = 8;                 // Number of data bits = 8
            COMPort.Parity   = Parity.None;       // No parity
            COMPort.StopBits = StopBits.One;      // One stop bit
           
   		    COMPort.Open();                       // Open the serial port
			
            //Put USB2SERIAL in Transmit Mode 
            COMPort.DtrEnable = false;            // Since DTR = 0.~DTR = 1 So  DE = 1 Transmit Mode enabled
            COMPort.RtsEnable = false;            // Since RTS = 0,~RTS = 1 So ~RE = 1

            COMPort.Write("A");                   // Write  "A" to opened serial port

            COMPort.Close();                      // Close the Serial port
        }
	}
}

            
            