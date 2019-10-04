#include <Arduino.h>
#include <EasyTransfer.h>
#include <Adafruit_MLX90614.h>
#include <DHT.h>  
#include <Wire.h>

EasyTransfer ET; 
Adafruit_MLX90614 mlx1 = Adafruit_MLX90614();
Adafruit_MLX90614 mlx2 = Adafruit_MLX90614(0x5B);
Adafruit_MLX90614 mlx3= Adafruit_MLX90614(0x5C);
Adafruit_MLX90614 mlx4 = Adafruit_MLX90614(0x5D);

DHT dht1(13,DHT22 );
DHT dht2(12,DHT22 ); 
DHT dht3(11,DHT22 );


struct unodata
{ float mlx[4]; // to float *(.02 -273) , then out as a double.
  float dhtT[3];
  float dhtH[3];
};


unodata UNODATA;
unsigned long startT;
int volatile sensorstep=0;
unsigned long loadcellT,waitT,sendT;

void setup()
{ 
  Serial.begin(19200);
  Wire.setClock(100000);
   mlx1.begin(); 
   mlx2.begin(); 
   mlx3.begin(); 
   mlx4.begin(); 
   dht1.begin();
   dht2.begin();    
   dht3.begin();
   ET.begin(details(UNODATA), &Serial);
   sendT= millis();
   loadcellT = millis();
};

void loop()
{ 
  if ( millis() - sendT >= 450)
        {  ET.sendData(); 
           sendT=millis();
         };

                  switch(sensorstep)
      {
               case 0:  
                      UNODATA.mlx[0]=mlx1.readObjectTempC();
                       sensorstep++;
                        break;
               case 1: UNODATA.mlx[1]=mlx2.readObjectTempC();
                        sensorstep++;  
                        break; 
               case 2:  UNODATA.mlx[2]=mlx3.readObjectTempC();
                       sensorstep++;  
                        break;   
               case 3:  UNODATA.mlx[3]=mlx4.readObjectTempC();
                        waitT=millis();
                        sensorstep++;  
                        break;

               case 4:   
                        UNODATA.dhtT[0]= dht1.readTemperature(); 
                       sensorstep++;  
                        break;
               case 5:  UNODATA.dhtT[1]= dht2.readTemperature(); 
                       // scalerun();
                        sensorstep++;  
                        break;
               case 6:  UNODATA.dhtT[2]= dht3.readTemperature();      
                       sensorstep++;
                       waitT=millis();  
                        break;
               case 7:
                              if (millis() - waitT > 2000)
                            {sensorstep++;   };      
                              break;                  
               case 8:  
                        UNODATA.dhtH[0]= dht1.readHumidity();                   
                      sensorstep++;
                        break;
               case 9: UNODATA.dhtH[1]= dht2.readHumidity();  
                        sensorstep++;  
                        break;
               case 10: UNODATA.dhtH[2]= dht3.readHumidity(); 
                                waitT=millis();  
                                sensorstep++; 
                        break;
               case 11:
                    if (millis() - waitT > 2000)
                            sensorstep=0; 
                            break; 
                              };
                  };
