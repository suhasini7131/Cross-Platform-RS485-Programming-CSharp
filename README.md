## Cross Platform RS485 communication between Microcontroller and PC 

Code in this repository can be used for communication between a Windows /Linux PC with a microcontroller through RS485 network.The code can be used to control devices like Relays,Motors,Robots etc from your PC through RS485 protocol.

<img src = "http://xanthium.in/sites/default/files/site-images/RS485-comm-Csharp/MSP430-launchpad-interfaced-USB-RS485-converter.jpg"/>


<a href="http://xanthium.in/crossplatform-rs485-communication-using-csharp-dotnet-framework-mono">Full Tutorial is available online here</a> 

The code is written in **C#** and is compiled using Microsoft Visual Studio Express edition and Sharpdevelop on Windows Operating System.The code runs on dot net framework on Windows.

On **Linux** The same code runs on **Mono Framework** and is compiled using mcs (Mono C# compiler).

On the PC side a **USB to RS485 converter** is used to convert the USB signals to RS485 protocol.
<img src = "http://www.xanthium.in/sites/default/files/site-images/product-page/usb_to_rs485_converter_250px.jpg"/>

The converter used in the tutorial can be <a href = http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">brought online here </a>.

On the device end, a **MSP430 Launchpad along with a MAX485** chip is used to decode the RS485 protocol and take appropriate action.

You can also use <a href = "http://xanthium.in/Robot-MotorControl-RS485-Shield-for-MSP430-Launchpad">MSP430 Motor control Booster Pack</a> (RobotShield V1.0) for decoding RS485 Signals.

<img src = "http://www.xanthium.in/sites/default/files/site-images/product-page/Robot_shield_msp430_launchpad_250px.jpg" /a>

The Booster Pack is available<a href = "http://xanthium.in/Robot-MotorControl-RS485-Shield-for-MSP430-Launchpad"> online here</a>.

The embedded System side code is written in **Embedded C** and compiled using IAR embedded workbench for MSP430

####ScreenShots (Windows)

<img src = "http://xanthium.in/sites/default/files/site-images/RS485-comm-Csharp/USB-to-RS485-Communication-Writing-Win32.jpg"/>

####ScreenShots (Linux)

<img src = "http://xanthium.in/sites/default/files/site-images/RS485-comm-Csharp/USB-to-RS485-Communication-writing-Linux.jpg"/>

<img src = "http://xanthium.in/sites/default/files/site-images/RS485-comm-Csharp/USB-to-RS485-Communication-Reading-Linux.jpg"/>

<a href="http://xanthium.in/crossplatform-rs485-communication-using-csharp-dotnet-framework-mono">Full Tutorial is available online here</a> 


