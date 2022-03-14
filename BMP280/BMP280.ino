#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

float ilkyukseklik=0, ayukseklik=0, byukseklik=0, fark=0;
int ikincikosul=0;

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


                  ilkyukseklik=bmp.readAltitude(1013.25);
}

void loop() 
{

  ayukseklik=bmp.readAltitude(1013.25);
  ayukseklik=ayukseklik-ilkyukseklik;
  
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(10);

/// Algoritma Açıklaması : ayukseklik verisini kaydettikten sonra byukseklik versini kaydedecektir.
/// byukseklik, ayukseklik verisinden küçük olduğu anda if şartını sağlayacaktır.
/// ayukseklik verisi if yapısı içerisinde sabit tutulup sadece byukseklik verisi tekrar alınacaktır.
/// arada ki fark atmaya devam ettikçe sürüklenme paraşütü ikinci koşul sağlanacaktır.
    
  byukseklik=bmp.readAltitude(1013.25);
  byukseklik=byukseklik-ilkyukseklik;
  
    if(byukseklik-ayukseklik<=-0.3)
    {
      fark=byukseklik-ayukseklik;
      Serial.print("Fark1 = ");
      Serial.println(fark);
            delay(10);
      byukseklik=bmp.readAltitude(1013.25);
      byukseklik=byukseklik-ilkyukseklik;

      if(byukseklik-ayukseklik<=-0.4)
      {
        fark=byukseklik-ayukseklik;
        Serial.print("Fark2 = ");
        Serial.println(fark);
              delay(10);
        byukseklik=bmp.readAltitude(1013.25);
        byukseklik=byukseklik-ilkyukseklik;

        if(byukseklik-ayukseklik<=-0.6)
        {
          fark=byukseklik-ayukseklik;
          Serial.print("Fark3 = ");
          Serial.println(fark);
                    delay(100);
          byukseklik=bmp.readAltitude(1013.25);
          byukseklik=byukseklik-ilkyukseklik;

          if(byukseklik-ayukseklik<=-1.2)
          {
            fark=byukseklik-ayukseklik;
            Serial.print("Fark4 = ");
            Serial.println(fark);
            Serial.println("SÜRÜKLENME PARAŞÜTÜ AÇILDI");
            ikincikosul=1;
          }
        }
      }
    }
    
    
}
