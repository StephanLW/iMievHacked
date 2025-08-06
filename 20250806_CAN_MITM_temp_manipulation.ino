/*
**************************************
Created by Stephan Langwald
Use on your own risk
To calculate the temperature use this Formula:
Temp = X - 50  -> X = Temp + 50
Example: If you want to set the temp. to 25 °C set the byte to 75.
**************************************
!!!Be carefull: If you change these bytes, the real temperature is not used for supervising the battery!!!
!!!->Overheating or overcooling could damage or burn down your battery!!! 
**************************************
*/


#include <SPI.h>
#include <mcp2515.h>

byte maxtemp = 75;  //Set the maximum cell temperature
byte mintemp = 75;  //Set the minimum cell temperature

struct can_frame canMsg;

//BMU -> Connect this MCP2515 to the BMU
MCP2515 mcp2515_0(8);
//Car -> Connect this MCP2515 to the Car` CAN BUS
MCP2515 mcp2515_1(10);



void setup() {

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


  //BMU//
  if (mcp2515_0.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    
    if (canMsg.can_id == 884) {
      canMsg.data[4] = maxtemp;
      canMsg.data[5] = mintemp;       
      }
            
    mcp2515_1.sendMessage(&canMsg);
  }


  //Car//
  if (mcp2515_1.readMessage(&canMsg) == MCP2515::ERROR_OK) {      
    mcp2515_0.sendMessage(&canMsg);
  } 
}
