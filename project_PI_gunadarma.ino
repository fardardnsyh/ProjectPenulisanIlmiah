#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Wire.h> // Library komunikasi I2C 
float suhuC;

// default address 0x27 
// tipe LCD 16x2 (16,2)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
virtuabotixRTC myRTC(6, 7, 8); //If you change the wiring change the pins here also

const int pinDigital = A0; //inisialisasi pin sensor
const int suhuPin = A1; //inisialisasi pin suhu
const int relay = 2; //inisialisasi pin relay
int pompa = 2;     // Pompa pada pin 2
int  hours, minutes, seconds;


void setup() {
  Serial.begin(9600); //memanggil serial monitor
//myRTC.setDS1302Time(0, 00, 7, 3, 7, 6, 2022);  
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  pinMode(suhuPin, INPUT); // menetapkan pin A1 sebagai input 
  pinMode(pinDigital, INPUT); // menetapkan pin A0 sebagai input
  pinMode(relay, OUTPUT); // menetapkan pin 2 sebagai output
  pinMode(pompa, OUTPUT); // menetapkan pin 2 sebagai output
  digitalWrite(2,LOW);// nyalakan pompa dan relay  
}

void loop(){
myRTC.updateTime();
lcd.setCursor(0,1);
lcd.print("Jam: ");
lcd.print(myRTC.hours);
lcd.print(":");
lcd.print(myRTC.minutes);
lcd.print(":");
lcd.print(myRTC.seconds);
lcd.println(" ");
delay(1000);
lcd.clear();

suhuC = analogRead(suhuPin); //membaca nilai adc sensor
suhuC = (suhuC / 1024) * 5000; //konversi data analog menjadi milivolt
suhuC = suhuC/10; //konversi kedalam derajat celcius dengan persamaan 1 derajat / 10 milivolt
lcd.setCursor(0,1); //set di kolom 0 dan baris 1
lcd.print("suhu="); //tampilkan tulisan "suhu=" di LCD
lcd.print((byte)suhuC); //tampilkan nilai suhu
lcd.print("   "); // spasi
delay(5000);
lcd.clear();

int dataAnalog = analogRead (pinDigital); //membaca nilai dari pin sensor
lcd.setCursor(0,0);
lcd.print("Kelembaban =");
lcd.print(dataAnalog);
delay(2000);
lcd.clear();

if((myRTC.hours == 7 & myRTC.minutes == 00 & myRTC.seconds == 0)){
  digitalWrite(2,LOW);
  delay(10000);
  digitalWrite(2,HIGH);
}
else {
((myRTC.hours == 7 & myRTC.minutes == 1 & myRTC.seconds == 0));{
  digitalWrite(2,HIGH);
}

//output suhu

if(suhuC > 30){
  lcd.setCursor(0,1);
  lcd.print(" Suhu Panas");
  digitalWrite(2,LOW);
  delay(5000);
  lcd.setCursor(3,0);
  lcd.print("suhu="); //tampilkan tulisan "suhu=" di LCD
  lcd.print((byte)suhuC); //tampilkan nilai suhu
  delay(1000);
}

else(suhuC == 18);{
  lcd.setCursor(1,1);
  lcd.print(" Suhu Ideal");
  digitalWrite(2,HIGH);
  delay(2000);
  lcd.setCursor(3,0);
  lcd.print("suhu="); //tampilkan tulisan "suhu=" di LCD
  lcd.print((byte)suhuC); //tampilkan nilai suhu
  delay(3000);
  lcd.clear();
}

//output kelembaban
if (dataAnalog > 500){
  lcd.setCursor(2,0);
  lcd.print(" Tanah Kering");
  digitalWrite(2,LOW);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Kelembaban =");
  lcd.print(dataAnalog);
  delay(2000);

}

else (dataAnalog == 200); {
  lcd.setCursor(1,0);
  lcd.print(" Tanah Basah");
  digitalWrite(2,HIGH);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Kelembaban =");
  lcd.print(dataAnalog);
  delay(3000);
  lcd.clear();
}

if((myRTC.hours == 15 & myRTC.minutes == 30 & myRTC.seconds == 0)){
  digitalWrite(2,LOW);
  delay(10000);
  digitalWrite(2,HIGH);
}

else {
((myRTC.hours == 15 & myRTC.minutes == 31 & myRTC.seconds == 0));
  digitalWrite(2,HIGH);
}
}
}
