#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg;             // CAN Config
unsigned long previousMillis = 0; // will store last time a CAN Message was send
const int interval = 0;           // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;     // Receive Queue size
unsigned long dataLoss = 0;
unsigned long sentMessages = 0;     // Variable to count sent messages
unsigned long receivedMessages = 1; // Variable to count received messages
unsigned long Durchschnitt = 50000000;
unsigned long Zeit_pro_Durchschnittlast = 0;
unsigned long Zeit_pro_Durchschnitt = 0;
unsigned long Zeit_pro_Durchschnittlasta = 0;
unsigned long Zeit_pro_Durchschnitta = 0;
unsigned long Messages_sent_all = 0;
void setup()
{
  Serial.begin(230400);
  delay(10000);
  Serial.println("Basic Demo - ESP32-Arduino-CAN");
  CAN_cfg.speed = CAN_SPEED_1000KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_5;
  CAN_cfg.rx_pin_id = GPIO_NUM_4;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
  Zeit_pro_Durchschnittlast = millis();
  Zeit_pro_Durchschnittlasta = millis();
  Zeit_pro_Durchschnitt = millis() - Zeit_pro_Durchschnittlast;
  Zeit_pro_Durchschnittlast = millis();
  Zeit_pro_Durchschnitt = Zeit_pro_Durchschnitt / 1000;
  Messages_sent_all = sentMessages + Messages_sent_all;
  Serial.printf("Sent: %u, Received: %u, Data Loss: %u\r\n", sentMessages, receivedMessages, dataLoss);
  Serial.printf("Sent All: %u, Time per %u Messages: %u\r\n", Messages_sent_all, Durchschnitt, Zeit_pro_Durchschnitt);
  receivedMessages = 0;
  sentMessages = 0;
}

void loop()
{

   CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
  {
    receivedMessages++;
  }

  // Send CAN Message
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    sentMessages++;

    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x001;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0x00;
    tx_frame.data.u8[1] = 0x01;
    tx_frame.data.u8[2] = 0x02;
    tx_frame.data.u8[3] = 0x03;
    tx_frame.data.u8[4] = 0x04;
    tx_frame.data.u8[5] = 0x05;
    tx_frame.data.u8[6] = 0x06;
    tx_frame.data.u8[7] = 0x07;
    ESP32Can.CANWriteFrame(&tx_frame);
  }

  // Calculate and print data loss every 1000 sent messages
  if (sentMessages == Durchschnitt)
  {
    dataLoss = sentMessages - receivedMessages;
    Zeit_pro_Durchschnitt = millis() - Zeit_pro_Durchschnittlast;
    Zeit_pro_Durchschnittlast = millis();
    Zeit_pro_Durchschnitt = Zeit_pro_Durchschnitt / 1000;
    Messages_sent_all = sentMessages + Messages_sent_all;
    Serial.printf("Sent: %u, Received: %u, Data Loss: %u\r\n", sentMessages, receivedMessages, dataLoss);
    Serial.printf("Sent All: %u, Time per %u Messages: %u\r\n", Messages_sent_all, Durchschnitt, Zeit_pro_Durchschnitt);
    receivedMessages = 0;
    sentMessages = 0;
  }
  if (sentMessages % 10000 == 0)
  {
    dataLoss = sentMessages - receivedMessages;
    Serial.print(">DataLoss:");
    Serial.println(dataLoss);
    Zeit_pro_Durchschnitta = millis() - Zeit_pro_Durchschnittlasta;
    Zeit_pro_Durchschnittlasta = millis();
    Serial.print(">Millisekunden_pro_10000_Nachrichten:");
    Serial.println(Zeit_pro_Durchschnitta);
  }
}
