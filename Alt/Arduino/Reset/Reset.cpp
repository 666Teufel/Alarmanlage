#include "Arduino.h"
#include "Reset.h"
Reset::Reset(int R_pin,int R_time,int M,int S,int T,int W,int timer)
{
Reset_pin = R_pin;
Reset_timer = R_time;
Wochen = W;
Tage = T;
Stunden = S;
Minuten = M;
Zeit = timer;
}
 int Reset::get_Zeit(){
  return Zeit;
 }
 int Reset::get_Minuten(){
  return Minuten;
 }
 int Reset::get_Stunden(){
  return Stunden;
 }
 int Reset::get_Tage(){
  return Tage;
 }
 int Reset::get_Wochen(){
  return Wochen;
 }
 int Reset::get_Reset_timer(){
  return Reset_timer;
 }
 void Reset::set_Zeit(int timer){
  Zeit = timer;
 }
 void Reset::set_Reset_timer(int R_time){
  Reset_timer = R_time;
 }
 void Reset::set_Reset_pin(int R_pin){
  Reset_pin = R_pin;
 }
 void Reset::set_Tage(int T){
  Tage = T;
 }
 void Reset::set_Wochen(int W){
  Wochen = W;
 }
 void Reset::set_Stunden(int S){
  Stunden = S;
 }
 void Reset::set_Minuten(int M){
  Minuten = M;
 }
