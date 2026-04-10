/*
**************************************
Created by Stephan Langwald

Be careful: The values are static and dont show the real parameters of the battery. That means, it is not protected against 
overheating, overcharge, overdischarge and insulation fault. You have to implement your own code to dynamicly feed the real
values into the canbus. Otherwise the battery can be damaged, start burning or somebody can be hurt or killed.
Maybe the real parameters of your battery have to be manipulated further, to get the outcome you want.

Use on your own risk!!!
*/


#include <SPI.h>
#include <mcp2515.h>

//Timing variables of the original BMU
const long intervallSend373 = 10; 
const long intervallSend374 = 100;
const long intervallSend375 = 100;
const long intervallSend5A1 = 50;

unsigned long previousSend373 = 0;
unsigned long previousSend374 = 0;
unsigned long previousSend375 = 0;
unsigned long previousSend5A1 = 0;

struct can_frame canMsg;

MCP2515 mcp2515_0(10);



void setup() {
  Serial.begin(115200);
  mcp2515_0.reset();
  mcp2515_0.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_0.setNormalMode();
 
}

void loop() {
  if ((previousSend373 + intervallSend373) < millis())
    { 
     send373();
     previousSend373 = millis();     
    }  

  if ((previousSend374 + intervallSend374) < millis())
    { 
     send374();
     previousSend374 = millis();     
    }

  if ((previousSend375 + intervallSend375) < millis())
    { 
     send375();
     previousSend375 = millis();     
    }    

  if ((previousSend5A1 + intervallSend5A1) < millis())
    { 
     send5A1();
     previousSend5A1 = millis();     
    }
}


void send373() {
  canMsg.can_id = 883;
  canMsg.can_dlc = 8;
  canMsg.data[0] = 178;    //Highest Cell Voltage
  canMsg.data[1] = 176;    //Lowest Cell Voltage
  canMsg.data[2] = 127;    //Current high byte
  canMsg.data[3] = 254;    //Current low byte
  canMsg.data[4] = 13;     //Battery voltage high byte
  canMsg.data[5] = 71;     //Battery voltage low byte
  canMsg.data[6] = 0;
  canMsg.data[7] = 22;

  mcp2515_0.sendMessage(&canMsg);
  //Serial.println("373 gesendet!");
}


void send374() {
  canMsg.can_id = 884;
  canMsg.can_dlc = 8;
  canMsg.data[0] = 121;   //SOC1
  canMsg.data[1] = 125;   //SOC2
  canMsg.data[2] = 0;
  canMsg.data[3] = 0;
  canMsg.data[4] = 76;    //high temp
  canMsg.data[5] = 69;    //low temp
  canMsg.data[6] = 56;
  canMsg.data[7] = 0;

  mcp2515_0.sendMessage(&canMsg);
  //Serial.println("374 gesendet!");  
}

void send375() {
  canMsg.can_id = 885;
  canMsg.can_dlc = 8;    
  canMsg.data[0] = 15;
  canMsg.data[1] = 15;
  canMsg.data[2] = 0;
  canMsg.data[3] = 0;
  canMsg.data[4] = 0;
  canMsg.data[5] = 0;
  canMsg.data[6] = 0;
  canMsg.data[7] = 0;
  
  mcp2515_0.sendMessage(&canMsg);
  //Serial.println("375 gesendet!");  
}

void send5A1() {
  canMsg.can_id = 1441;
  canMsg.can_dlc = 8;
  canMsg.data[0] = 0;   //Insulation fault
  canMsg.data[1] = 0;
  canMsg.data[2] = 0;
  canMsg.data[3] = 0;
  canMsg.data[4] = 0;
  canMsg.data[5] = 0;
  canMsg.data[6] = 0;
  canMsg.data[7] = 0;
  mcp2515_0.sendMessage(&canMsg);
  //Serial.println("5A1 gesendet!");  
}
