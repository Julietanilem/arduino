
#include <EEPROM.h>

int valor;
int sensorValue;
int sensorPin = A0;
int bombaAgua=13;
int electroEntrada  = 12;
int electrovalvula=8; 
int valorBomba=0;
int valorBoton=0;
int estadoBomba1=0;
int estadoBomba2=0;
int estadoBomba3=0;
int dato=0, anterior =0, tiempoSegunBoton=0;
/*Pines de botones*/
int BotonElectrovalvula = 9;
int boton2 =10;
int boton3 = 11;
int boton4 = 7;
int botonProg = 5;
int botonPresionado;
/*Tiempos*/
int tiempo1=10;
int tiempo2=20;
int tiempo3=30;
int tiempo4=40;
unsigned long tiempoIn = 0;



void setup() {
   pinMode(BotonElectrovalvula, INPUT);
   pinMode(boton2, INPUT);
   pinMode(boton3, INPUT);
   pinMode(boton4, INPUT);
   pinMode(botonProg, INPUT);
   pinMode( bombaAgua, OUTPUT);
   pinMode( electroEntrada , OUTPUT); 
   pinMode(electrovalvula, OUTPUT);

   Serial.begin(9600);
}

void loop() {
    /*ProgramacionTiempo*/
    if( digitalRead(botonProg) == 1)
    {
      botonPresionado=0;
      tiempoIn=0;
      while(botonPresionado==0)
      {
        if(digitalRead(BotonElectrovalvula) == 1 )
        {
          botonPresionado=1;
          tiempoIn = millis();
        }
        else if(digitalRead(boton2) == 1 )
        {
          botonPresionado=2;
          tiempoIn = millis();
        }
        else if(digitalRead(boton3) == 1 )
        {
          botonPresionado=3;
          tiempoIn = millis();
        }
        else if(digitalRead(boton4) == 1 )
        {
          botonPresionado=4;
          tiempoIn = millis();
        }
      }
  
      
      switch(botonPresionado)
      {
        case 1:
        {
          while(digitalRead(BotonElectrovalvula) == 1)
          {
            delay(1);
          }
   
          EEPROM.update(0, millis()-tiempoIn);
          break;
        }
        case 2:
        {
          while(digitalRead(boton2) == 1)
          {
            delay(1);
          }
          EEPROM.update(1, millis()-tiempoIn);
 
          break;
        }
        case 3:
        {
          while(digitalRead(boton3) == 1)
          {
            delay(1);
          }
         EEPROM.update(2, millis()-tiempoIn);
 
          break;
        }
        case 4:
        {
         while(digitalRead(boton4) == 1)
          {
            delay(1);
          }
          EEPROM.update(3, millis()-tiempoIn);
 
          break;
        }
        default:{
        Serial.println("Error en la programación");
        }
      }
  
    }
    delay(100);
    /*Obtención de tiempos*/
    /*La primera vez antes hay que correr:
     * EEPROM.write(0, 10);
      EEPROM.write(1, 20);
      EEPROM.write(2, 30);
      EEPROM.write(3, 40);
    */
    EEPROM.get(0, tiempo1);
    EEPROM.get(1, tiempo2);
    EEPROM.get(2, tiempo3);
    EEPROM.get(3, tiempo4);
    
    /*Si se presiona uno de los botones se prende la de agua*/
   if( digitalRead(BotonElectrovalvula) == 1 ||   digitalRead(boton2) == 1 ||  digitalRead(boton3) == 1 ||  digitalRead(boton4) == 1)
   {
     valorBoton=1; 
     /*Tiempo depende del boton*/
     if(digitalRead(BotonElectrovalvula) == 1)
     {
      tiempoSegunBoton=tiempo1; 
     }
   
     if( digitalRead(boton2)==1 )
     {
      tiempoSegunBoton=tiempo2; 
     }
     if( digitalRead(boton3)==1 )
     {
      tiempoSegunBoton=tiempo3; 
     }
     if( digitalRead(boton4)==1 )
     {
      tiempoSegunBoton=tiempo4; 
     }
   }
   else{
     valorBoton=0;  
   }
  
   /*Leer valor del sensor (pendiente)*/
   sensorValue = analogRead(sensorPin);
   Serial.println(sensorValue);
   if(sensorValue==0)
    {
      estadoBomba1=1;
      digitalWrite(electroEntrada , 1);
    }
    else{
       estadoBomba1=0;
       digitalWrite(electroEntrada , 0);
    }
  
    if (valorBoton == 1 && anterior == 0)
    {
      estadoBomba2=1;
      digitalWrite(electrovalvula, 1); 
    }
    else if(valorBoton==0 && anterior==1){
      estadoBomba2=0;
      digitalWrite(electrovalvula, 0); 
    }
   anterior=valorBoton;
   delay(100);
   /*Si falta agua o se presiona un boton la bomba debería prenderse*/
   if(estadoBomba1 == 1 || estadoBomba2==1 )
   {
      digitalWrite(bombaAgua, 1);
      if(valorBoton == 1)
      {
        delay(tiempoSegunBoton);
        digitalWrite(bombaAgua, 0);
      }

   }
   else{
      digitalWrite(bombaAgua, 0);
   }
   
}
