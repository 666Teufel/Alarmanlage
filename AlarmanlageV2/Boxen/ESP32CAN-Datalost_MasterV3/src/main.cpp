#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg;             // CAN Config
unsigned long previousMillis = 0; // will store last time a CAN Message was send
const int interval = 0;           // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;     // Receive Queue size
const int this_modul_id = 1;

unsigned long sent_messages[4] = {0, 0, 0, 0};     // Array für die anzahl der gesendeten Nachrichten an das Modul
unsigned long received_messages[4] = {0, 0, 0, 0}; // Array für die anzahl der empfangenden Nachrichten von einem Modul
unsigned long message_loss[4] = {0, 0, 0, 0};      // Array für die anzahl der verlorenden Nachrichten von einem Modul
unsigned long data_loss[4] = {0, 0, 0, 0};         // Array für die anzahl der Fehlerhaften Teile im Array
String message[4][7];                              // Nachrichten Spericher zum Vergleich
int next_modul = 2;                                // Welches modul angesprochen werden soll
int i;                                             // Variabel für die Forschleife

unsigned long messages_sent_all = 0;
unsigned long received_messages_all = 0;

unsigned long Durchschnitt = 50000000;
unsigned long Zeit_pro_Durchschnittlast = 0;
unsigned long Zeit_pro_Durchschnitt = 0;

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
  Zeit_pro_Durchschnitt = millis();
  Zeit_pro_Durchschnittlast = millis();
}

void loop()
{
  delay(1000);
  randomSeed(34238400);

  CAN_frame_t rx_frame;

  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = next_modul;         // Addresse des Zieles
  tx_frame.FIR.B.DLC = 8;              // Länge der Nachricht
  tx_frame.data.u8[0] = this_modul_id; // Sender der Nachricht
  for (i = 0; i <= 6; i++)
  {
    message[next_modul - 2][i] = String(random(0, 4096 + 1), HEX); // Erstellen der Zufälligen Nachricht
    tx_frame.data.u8[i + 1] = 0x01;                                // message[next_modul - 2][i]; // Senden der Vorher zufälig gewälten Nachricht
  }
  ESP32Can.CANWriteFrame(&tx_frame);

  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
  {

    if (rx_frame.FIR.B.FF == CAN_frame_std)
    {
      printf("New standard frame");
    }
    else
    {
      printf("New extended frame");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR)
    {
      printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
    }
    else
    {
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID, rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++)
      {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");
    }
  }

  /*// Calculate and print data loss every 1000 sent messages
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
  } */
}
