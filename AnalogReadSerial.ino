#include <LiquidCrystal.h>
#define trigPin 13
#define echoPin 12
#define led 22
#define led2 24
LiquidCrystal lcd(2,3,4,5,6,7);

int pot1,pot2;
int sicaklik_derecesiPin = A0; // analog girişin olacağı pin

int yesil_led = 36;        // yeşil led çıkış
int sari_led =38;          // sarı led
int kirmizii_led = 40; // kırmızı led
int buzzerPin = 50 ;
void setup() {
  Serial.begin (9600);
   lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode( yesil_led, OUTPUT);           // 7 nolu pin çıkış olarak belirle
pinMode( sari_led, OUTPUT);             // 6 nolu pin çıkış olarak belirle
pinMode( kirmizii_led, OUTPUT);     // 5 nolu pin çıkış olarak belirle


pinMode(buzzerPin,OUTPUT);
}
void loop() {
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  //
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  // Mesafe 10 cm den küçük olduğunda LED ve buzzer 0,3 sn de bir yanıp durucaktır.
  digitalWrite(led2,HIGH);
  delay(300);
   digitalWrite(led2,LOW);
   
  }
  if (distance >= 0 && distance < 10) {  // Mesafe 0-10 cm arasında olduğunda LED ve buzzer yanıp sönme frekansını ayarladık.
   
  digitalWrite(led,HIGH);
  digitalWrite(led2,HIGH);
  delay(500);
  melodi(500);

}
if (distance >= 10 && distance < 20) {  //aynı şekilde 10-20 cm arasında olduğunda 
  digitalWrite(led,HIGH);
  delay(700);
   digitalWrite(led2,LOW);
   melodi(100);
}
  if (distance >= 20 && distance < 30) {  // 20-30 cm arasında olduğunda yanıp sönme sıklığı
  digitalWrite(led2,LOW);
  delay(1000);
   digitalWrite(led,LOW);
   melodi(50);
} 
if (distance >= 30 || distance <=0){  //burada ise mesaje 30 cm ve üstündeyse LED ve buzzer ımıza hiç bir şey yaptırmıyoruz.

    
    digitalWrite(led2,LOW);
   digitalWrite(led,LOW);
   delay(1000);
  
  }
  else {
   
     ;
  }
  
  delay(100);
  
float sicaklik_derecesi;
float gerilim_degeri;
gerilim_degeri = analogRead(sicaklik_derecesiPin);       // analog degeri oku
gerilim_degeri = (gerilim_degeri/1023)*5000;                // analog deger mv ye çevirir.
sicaklik_derecesi = gerilim_degeri/10.0;                            // celciusa çevirip sicakliğa atadık.
// bulduğumuz değer aralığına göre yanacak ledleri belirliyoruz.
if ( sicaklik_derecesi < 23 )
{
digitalWrite ( yesil_led , HIGH );     // yeşil ledi yak
digitalWrite ( sari_led , LOW );         //
digitalWrite ( kirmizii_led , LOW ); //
}
else if( (sicaklik_derecesi >=23) && ( sicaklik_derecesi < 25) )
{
digitalWrite ( yesil_led , LOW );      // yeşil ledi söndür
digitalWrite ( sari_led , HIGH );       // sarı ledi yak
digitalWrite ( kirmizii_led , LOW ); // kırmızı ledi söndür
}
else if( (sicaklik_derecesi >=25) && ( sicaklik_derecesi < 50) )
{
digitalWrite ( yesil_led , LOW );            // yeşil ledi söndür
digitalWrite ( sari_led , LOW );               // sarı ledi söndür
digitalWrite ( kirmizii_led , HIGH );      // kırmızı ledi yak
}


// yarım saniyede bir bizde ekranımızdan değeri görelim.
pot1=(int)distance;
pot2=(int)sicaklik_derecesi;
Serial.print(pot1);
Serial.print("*");
Serial.println(pot2);

lcd.begin(16,2);
lcd.clear();
lcd.print("Mesafe D: ");
lcd.print(pot1);

lcd.setCursor(0,2);
lcd.print("Sicaklik D: ");
lcd.print(pot2);


delay(500);

}
int melodi(int gecikme)
  {
    tone(buzzerPin, 440);
    delay(gecikme);
    noTone(buzzerPin);
    delay(gecikme);
  }