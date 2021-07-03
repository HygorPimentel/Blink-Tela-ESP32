// AUTOR: Hygor Pimentel
// DATA: 01/07/2021

#include <Arduino.h>
#include <SSD1306.h>


/** Mapeamento de hardware **/

#define flag 25                  
#define OLED_ADDRES 0x3c
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RESET 16

/** Variaveis Globais **/

int counter   = 0,
    temp      = 0,
    temp_flag = 2000; //tempo em ms



/** Instanciamento de objetos **/

SSD1306 OLED(OLED_ADDRES,OLED_SDA,OLED_SCL);


/** Implementação das Funções **/

void display_config()
{
  pinMode(OLED_RESET,OUTPUT);
  digitalWrite(OLED_RESET,LOW);
  delay(10);
  digitalWrite(OLED_RESET,HIGH);
  delay(10);

  OLED.init();

  OLED.flipScreenVertically();
  OLED.setFont(ArialMT_Plain_16);
  OLED.setTextAlignment(TEXT_ALIGN_LEFT);
}

void Logica()
{
  if (millis() - temp >= temp_flag)
  {
    digitalWrite(flag,!digitalRead(flag));
    temp = millis();
    
  }
  if (digitalRead(flag) == HIGH)
  {
    OLED.clear();
    OLED.drawString(0,0,"Flag Ligada");
    OLED.display();
    delay(temp_flag);
    counter++;
  }
  
  OLED.clear();
  OLED.drawString(0,0,"Flag Desligada");
  OLED.drawString(0,20,"Qtd de Acion: " + String(counter) );
  OLED.display();

}


void setup() 
{
  display_config();
  pinMode(flag,OUTPUT);
  digitalWrite(flag,LOW);
  
}

void loop()
{
  Logica();
}