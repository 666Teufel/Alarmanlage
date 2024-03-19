#ifndef Reset_h
#define Reset_h

#include "Arduino.h"
class Reset
{
 private:
 unsigned long Zeit;
 unsigned long Reset_timer = 10000;

 int Wochen = 0;
 int Tage = 0;
 int Stunden = 0;
 int Minuten = 0;
 public:
 Reset(int R_pin,int R_time,int M,int S,int T,int W,int timer);
 int Reset_pin = 2;

 int get_Zeit();
 int get_Minuten();
 int get_Stunden();
 int get_Tage();
 int get_Wochen();
 int get_Reset_timer();
 void set_Zeit(int timer);
 void set_Reset_timer(int R_time);
 void set_Reset_pin(int R_pin);
 void set_Tage(int T);
 void set_Wochen(int W);
 void set_Stunden(int S);
 void set_Minuten(int M);
};
#endif
