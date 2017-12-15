#include<SPI.h>
//#include<nRF24L01.h>
#include<RF24.h>
const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(7,8);

typedef struct
{
  int X;
  int Y;
}positions;

positions pos;

//int ack[1] = {990};
void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);

  
}
void loop()
{
    if(radio.available())
    {
      radio.read(&pos,sizeof(pos));
      radio.writeAckPayload(1,&pos,sizeof(pos));
      Serial.println("X = "+String(pos.X)  +  "  Y = "+String(pos.Y));
    }
}
