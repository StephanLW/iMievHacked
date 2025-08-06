/*
**************************************
Created by Stephan Langwald
Use on your own risk
To calculate the temperature use this Formula:
Use line 29 to change the voltage. If you want to lower it from 4.1
to 3.9V, you have to use a value of "20" for 0.2 V reduction.
You can also change the minimum battery voltage byte in line 63.

If you always not fully charge the battery it may not be balanced correctly.
**************************************
!!!Be carefull: If you change these bytes, the real Voltage is not used for supervising the battery!!!
!!!->Overcharging or overdischarging could damage or burn down your battery!!! 
**************************************
*/


#include <SPI.h>
#include <mcp2515.h>


struct can_frame canMsg;

//BMU -> Connect this MCP2515 to the BMU
MCP2515 mcp2515_0(8); //8
//Car -> Connect this MCP2515 to the Car` CAN BUS
MCP2515 mcp2515_1(10);  //10

byte lowerVoltage = 20; //-> Reduce the charing Voltage by 0.2 Volt

byte maxVoltRealByte;
byte maxVoltManipByte;

byte minVoltRealByte;
byte minVoltManipByte;

void setup() {
  Serial.begin(115200);

  //BMU
  mcp2515_0.reset();
  mcp2515_0.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_0.setNormalMode();

  //Car
  mcp2515_1.reset();
  mcp2515_1.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_1.setNormalMode();  
}

void loop() {

  //BMU-Seite//
  if (mcp2515_0.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    
    if (canMsg.can_id == 883) {
      
      maxVoltRealByte = canMsg.data[0];
      maxVoltManipByte = maxVoltRealByte+lowerVoltage; //+18 -> 3,92V
      canMsg.data[0] = maxVoltManipByte;

      minVoltRealByte = canMsg.data[1];
      minVoltManipByte = minVoltRealByte+0;
      canMsg.data[1] = minVoltManipByte;        
      }
            
    mcp2515_1.sendMessage(&canMsg);
  }


  //Car//
  if (mcp2515_1.readMessage(&canMsg) == MCP2515::ERROR_OK) {      
    mcp2515_0.sendMessage(&canMsg);
  }  
}
