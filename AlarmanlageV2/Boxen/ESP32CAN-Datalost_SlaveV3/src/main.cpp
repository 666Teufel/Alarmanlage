#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg;         // CAN Config
const int rx_queue_size = 10; // Receive Queue size
const int this_modul_id = 2;

void setup()
{
  delay(10000);
  Serial.begin(115200);
  Serial.println("Slave Demo - ESP32-Arduino-CAN");
  CAN_cfg.speed = CAN_SPEED_125KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_5;
  CAN_cfg.rx_pin_id = GPIO_NUM_4;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
}

void loop()
{
  CAN_frame_t rx_frame;
  // receive next CAN frame from queue
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
      // printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
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
    if (rx_frame.data.u8[0] == this_modul_id){

    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = rx_frame.MsgID + 1;       // Zahl der Nachricht
    tx_frame.FIR.B.DLC = 8;                    // Länge der Nachricht
    tx_frame.data.u8[0] = rx_frame.data.u8[1]; // Empfänger der Nachricht
    tx_frame.data.u8[1] = this_modul_id;       // Sender der Nachricht
    for (int i = 2; i < rx_frame.FIR.B.DLC; i++)
    {
      tx_frame.data.u8[i] = rx_frame.data.u8[i];
    }
    ESP32Can.CANWriteFrame(&tx_frame);
    Serial.println("Senden");
    // respond to sender
    }
  }
}