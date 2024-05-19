#include <Arduino.h>
#include <canfd2.h>

#define SPI_RX  0
#define SPI_CS  1
#define SPI_SCK 2
#define SPI_TX  3
#define UART_TX 4
#define UART_RX 5

CANFD2 canfd2(UART_TX, UART_RX, SPI_TX, SPI_RX, SPI_CS, SPI_SCK);

static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg) {
    if(notify == CAN2040_NOTIFY_RX) {
      Serial.println("RX CAN MSG");
      Serial.print("ID: 0x");
      Serial.print(msg->id, HEX);
      Serial.print(" DLC: 0x");
      Serial.print(msg->dlc, HEX);
      Serial.print(" DATA: ");
      for(int i = 0; i < (msg->dlc); i++) {
        Serial.print(msg->data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
}

void setup(){
  Serial.begin(115200);
  Serial.println("Setting up CANFD 2 CLICK");
  canfd2.begin(500000, can2040_cb);
}


void loop() {
  struct can2040_msg msg;
  msg.id = 0x123;
  msg.dlc = 8;
  msg.data[0] = 0x01;
  msg.data[1] = 0x02;
  msg.data[2] = 0x03;
  msg.data[3] = 0x04;
  msg.data[4] = 0x05;
  msg.data[5] = 0x06;
  msg.data[6] = 0x07;
  msg.data[7] = 0x08;

  uint8_t res = canfd2.send_frame(&msg);
  delay(100);
}
