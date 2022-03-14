#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

float anglex=0, angley=0;
int birincikosul=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);

  Serial.println("Done!\n");
}

///Algoritma açıklaması : Pitch(X) ve Roll(Y) değerleri başlangıçta 0 olacak şekilde kalibrasyon işlemi yapılacaktır.
///Sonrasında kalibrasyon kodu algoritmadan kaldırılacaktır.
///MPU6050 aviyonik sistemle birlikte rokete yerleştirildiğinde Pitch değeri 75 derecelik bi açı gösterecektir.
///Roll değeri ise 0 olacaktır.
///(Atış rampası 15 derecelik bi eğime sahiptir.)
///Pitch değeri 0 ile 180 arasında değer alırken, Roll +90 ile -90 arasında değerler almaktadır.
///Sürüklenme paraşütü için Pitch (0ile20 veya 165ile180 arasında) veya Roll (75ile90 veya -75ile-90 arasında) değerler almalıdır.
///Algoritma Pitch ve Roll değerlerini ayrı ayrı sorgulamakta ve hangisi gerekli koşulu sağlarsa sürüklenme paraşütü açılmaktadır. 

void loop() 
{
  mpu.update();

anglex=mpu.getAngleX();
angley=mpu.getAngleY();

	Serial.print("X : ");
	Serial.print(anglex);
	Serial.print("\tY : ");
	Serial.println(angley);

    if(anglex<=15 || anglex>=165)
    {
      Serial.print("Anglex = ");
      Serial.println(anglex);
      Serial.print("Angley = ");
      Serial.println(angley);
      Serial.print("Sürüklenme paraşütü açıldı");
      while(1);
    }

    if(angley>=75 || angley<=-75)
    {
      Serial.print("Anglex = ");
      Serial.println(anglex);
      Serial.print("Angley = ");
      Serial.println(angley);
      Serial.print("y Sürünlenme paraşütü açıldı");
      birincikosul=1;
      while(1);
    }
  
}
