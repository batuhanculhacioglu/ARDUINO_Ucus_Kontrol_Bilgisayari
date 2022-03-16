#include <MPU6050.h>    //Eğim ve İvme Sensörü kütüphanesi
#include <Wire.h>

MPU6050 MPU;

int16_t gx, gy, gz;

short anglex, angley;

void setup() {
Wire.begin();  //12C iletişim protokülünü başlatıyoruz.
Serial.begin(9600);


 MPU.initialize();

}

///Algoritma açıklaması : Pitch (X) rokete yerleştirildiğinde yaklaşık 165 derece ile başlayacaktır.
///Roll(Y) değeri roket aktifleştirildiğin de 90 derece ile başlayacaktır.
///Sürüklenme paraşütü aktifleşme koşulu Pitch 95'den küçüksedir.
///Roll için 175'den büyük veya 5'den küçüksedir.

void loop() {

         MPU.getAcceleration(&gx, &gy, &gz);
         anglex = map(gx, -16500, 16500, 0, 180);
         angley = map(gy, -16000, 16000, 0, 180);

  Serial.print("X : ");
  Serial.print(anglex);
  Serial.print("\tY : ");
  Serial.println(angley);

    if(angley<=95)
    {
      Serial.print("Anglex = ");
      Serial.println(anglex);
      Serial.print("Angley = ");
      Serial.println(angley);
      Serial.print("y Sürüklenme paraşütü açıldı");
      while(1);

    }

    if(anglex>=175 || anglex<=5)
    {
      Serial.print("Anglex = ");
      Serial.println(anglex);
      Serial.print("Angley = ");
      Serial.println(angley);
      Serial.print("x Sürünlenme paraşütü açıldı");
      while(1);

    }
    delay(1000);
}
