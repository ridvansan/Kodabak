#include <Servo.h>
Servo on;
Servo arka;
// ÖN (1)
const int on_hiz1 = 2;//beyaz
const int on_hiz2 = 3;//sarı
const int on_1 = 22;//mor SAĞ
const int on_2 = 23;//gri
const int on_3 = 24;//yesil SOL
const int on_4 = 25;//mavi
//ARKA (2)
const int arka_hiz1 = 4;//mor
const int arka_hiz2 = 5;//mavi
const int arka_1 = 26;//siyah SAĞ
const int arka_2 = 27;//yeşil
const int arka_3 = 28;//sarı SOL
const int arka_4 = 29;//mor
//KOL (3)
const int kol_hiz1 = 6;//siyah
const int kol_hiz2 = 7;//gri
const int kol_1 = 30;//beyaz SAĞ
const int kol_2 = 31;//mavi
const int kol_3 = 32;//turuncu SOLW
const int kol_4 = 33;//yeşil
//ULTRASONİK
const int trigPin = A0;
const int echoPin = A1;
const int trigPin2 = A7;
const int echoPin2 = A6;
const int trigPin3 = A12;
const int echoPin3 = A13;


int onbaslangic = 180;
int onbitis = 110;
int arkabaslangic = 180;
int arkabitis = 0;

float duration;
int distance;
int stat = 0;
int total = 0;
int stat2 = 0;
int total2 = 0;
int stat3 = 0;
int total3 = 0;
int cm, cm2, cm3, x;


int arkaSagHiz = 150;
int arkaSolHiz = 100;
int onSagHiz = 100;
int onSolHiz = 80;
int arkaKolSagHiz = 220;
int arkaKolSolHiz = 60;

int basamak = 0; //NORMALİ SIFIR

void setup() {
  pinMode(on_hiz1, OUTPUT);
  pinMode(on_1, OUTPUT);
  pinMode(on_2, OUTPUT);
  pinMode(on_hiz2, OUTPUT);
  pinMode(on_3, OUTPUT);
  pinMode(on_4, OUTPUT);
  pinMode(arka_hiz1, OUTPUT);
  pinMode(arka_hiz2, OUTPUT);
  pinMode(arka_1, OUTPUT);
  pinMode(arka_2, OUTPUT);
  pinMode(arka_3, OUTPUT);
  pinMode(arka_4, OUTPUT);
  pinMode(kol_hiz1, OUTPUT);
  pinMode(kol_hiz2, OUTPUT);
  pinMode(kol_1, OUTPUT);
  pinMode(kol_2, OUTPUT);
  pinMode(kol_3, OUTPUT);
  pinMode(kol_4, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT);


  Serial.begin(9600);
  on.attach(12);
  arka.attach(11);
  arka.write(180);
  on.write(180);
  delay(1000);
  deneme();
}


void loop() {
  if (basamak < 7 ) {
    kendiniKaldir();

    if (basamak == 4) {
      arkaTekerIleri();
      delay(500);
      arkaTekerDur();
      delay(100);
      donus();
      delay(1000);
      donus2();
      delay(1400);
      arkaTekerGeri();
      delay(200);
      arkaTekerDur();
      delay(200);
      arkaTekerIleri();
      delay(650);
      arkaTekerDur();
    }

    delay(200);
    x = mesafeOlc();
    Serial.print("bastır ");
    Serial.println(x);
    while (x > 7 || x == 0 ) {
      arkaTekerIleri();
      x = mesafeOlc();
      on.write(110);
      Serial.print("bastırX ");
      Serial.println(x);
    }
    delay(100);
    arkaTekerDur();
    delay(100);
    on.write(onbaslangic); // basamağı görünce ön kolu kaldır
    delay(1000);
    basamakCik();


  }
  else if (basamak == 7) {
    arkaSagHiz = arkaSagHiz * 0.8;
    arkaSolHiz = arkaSagHiz * 0.8;
    onTekerIleri();
    arkaTekerIleri();
    delay(250);
    onTekerDur();
    arkaTekerDur();
    delay(2000);
    inis();
  }
  else if (basamak > 7 && basamak != 10) {
    inis();
  }
  else if (basamak == 10 ) {
    kendiniKaldir();
    yenigeridonus();
    delay(4000);
    arkaTekerDur();
    arka.write(180);
    kendiniIndir();
    inis();
  }


}

void yenigeridonus() {
  //sag teker
  digitalWrite (arka_1, HIGH);//low geri
  digitalWrite (arka_2, LOW);
  analogWrite(arka_hiz1, arkaSagHiz * 9 / 5);
  //sol teker
  digitalWrite (arka_3, LOW);
  digitalWrite (arka_4, HIGH);
  analogWrite(arka_hiz2, arkaSolHiz * 9 / 5);
}
void inis() {
  int m, n, k, i;
  for (i = 180; i >= 90 ; i--) {
    arka.write(i);
    delay(5);
  }
  m = mesafeOlc2();
  while ( m < 9 || m > 30) {
    arkaTekerGeri();
    onTekerGeri();
    m = mesafeOlc2();
  }
  arkaTekerDur();
  onTekerDur();
  for (i = 90; i >= 0 ; i--) {
    arka.write(i);
    delay(5);
  }
  n = mesafeOlc3();
  while ( n < 11 || n > 35) {
    arkaTekerGeri();
    onTekerGeri();
    arkaKollarGeri();
    n = mesafeOlc3();
  }
  onTekerIleri();
  arkaKolIleri();
  arkaTekerDur();
  delay(100);
  onTekerDur();
  arkaKollarDur();
  delay(300);
  for (i = 180; i >= 130 ; i--) {
    on.write(i);
    delay(5);
  }
  delay(500);
  for (i = 0; i <= 110 ; i++) {
    arka.write(i);
    delay(5);
  }
  delay(300);
  for (i = 130; i >= 110 ; i--) {
    on.write(i);
    delay(5);
  }
  n = mesafeOlc2();
  while ( n < 11 || n > 35) {
    arkaTekerGeri();
    arkaKollarGeri();
    onTekerGeri();
    n = mesafeOlc2();
  }
  onTekerDur();
  arkaTekerDur();
  arkaKollarDur();
  arka.write(180);
  kendiniIndir();
  basamak++;



}



void donus() {//90 derecedeki ileri manvera yukarı çıkış
  //ARKASAĞ İLERİ
  digitalWrite (arka_1, LOW);
  digitalWrite (arka_2, LOW);
  analogWrite(arka_hiz1, arkaSagHiz);
  //ARKASOL İLERİ
  digitalWrite (arka_3, LOW);
  digitalWrite (arka_4, HIGH);
  analogWrite(arka_hiz2, 150);
}
void donus2() { //90 derecede geri manevra yukarı çıkış
  //ARKASAĞ geri
  digitalWrite (arka_1, HIGH);
  digitalWrite (arka_2, LOW);
  analogWrite(arka_hiz1, arkaSagHiz);
  //ARKASOL dur
  digitalWrite (arka_3, LOW);
  digitalWrite (arka_4, LOW);
  analogWrite(arka_hiz2, arkaSolHiz);
}
void geridonus() {
  //arka sağ duruyor
  digitalWrite (arka_1, LOW);
  digitalWrite (arka_2, HIGH);
  analogWrite(arka_hiz1, 255);
  //arka sol geri döner
  digitalWrite (arka_3, HIGH);//low ken ileri
  digitalWrite (arka_4, LOW);
  analogWrite(arka_hiz2, 200);

}
void geridonus2() {
  //arka sağ ileri döner
  digitalWrite (arka_1, LOW);//low ken ileri
  digitalWrite (arka_2, HIGH);
  analogWrite(arka_hiz1, 255);
  //arka sol durur
  digitalWrite (arka_3, HIGH);
  digitalWrite (arka_4, LOW);
  analogWrite(arka_hiz2, 45);
}


void kendiniKaldir() {// mesafe ölçüp robotu yukarı kaldırıyor

  int x = mesafeOlc();
  /*Serial.print("mesafe");
    Serial.println(x);*/
  int i = onbaslangic;
  /*for(i = onbaslangic ; i >= onbitis ; i--) {
    on.write(i);
    delay(20);
    }*/
  while (x <= 13) {
    Serial.print("burdayız ");
    Serial.println(x);
    on.write(onbitis); // kendini kaldırıncaya kadar servoya bunu yazdır
    x = mesafeOlc();
  }
  Serial.print("asdasdasdasdasdasdasdasdas");
}

void kendiniIndir() { //robot yavaşça aşağıya iner
  int i;
  for (i = onbitis ; i <= onbaslangic ; i++) {
    on.write(i);
    delay(45);
  }
}

int mesafeOlc() {
  //ULTRASONİK
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  /*Serial.print("distance");
    Serial.println(distance);*/
  stat++;
  total += distance;
  if (stat == 5) {
    cm = total / 5;
    stat = 0;
    total = 0;
    return cm;
  }
  return 0;
}

int mesafeOlc2() {
  //ULTRASONİK
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  /*Serial.print("distance");
    Serial.println(distance);*/
  stat2++;
  total2 += distance;
  if (stat2 == 3) {
    cm2 = total2 / 3;
    stat2 = 0;
    total2 = 0;
    return cm2;
  }
  return 0;
}
int mesafeOlc3() {
  //ULTRASONİK
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  /* Serial.print("distance");
    Serial.println(distance);*/
  stat3++;
  total3 += distance;
  if (stat3 == 3) {
    cm3 = total3 / 3;
    stat3 = 0;
    total3 = 0;
    return cm3;
  }
  return 0;
}

void arkaTekerIleri() {
  //ARKASAĞ İLERİ
  digitalWrite (arka_1, LOW);
  digitalWrite (arka_2, HIGH);
  analogWrite(arka_hiz1, arkaSagHiz);
  //ARKASOL İLERİ
  digitalWrite (arka_3, LOW);
  digitalWrite (arka_4, HIGH);
  analogWrite(arka_hiz2, arkaSolHiz);
}

void arkaTekerDur() {
  //ARKASAĞ İLERİ
  digitalWrite (arka_1, HIGH);
  digitalWrite (arka_2, HIGH);
  analogWrite(arka_hiz1, arkaSagHiz);
  //ARKASOL İLERİ
  digitalWrite (arka_3, HIGH);
  digitalWrite (arka_4, HIGH);
  analogWrite(arka_hiz2, arkaSolHiz);

}

void arkaTekerGeri() {
  //ARKASAĞ İLERİ
  digitalWrite (arka_1, HIGH);
  digitalWrite (arka_2, LOW);
  analogWrite(arka_hiz1, arkaSagHiz * 0.9);
  //ARKASOL İLERİ
  digitalWrite (arka_3, HIGH);
  digitalWrite (arka_4, LOW);
  analogWrite(arka_hiz2, arkaSolHiz * 0.9);
}

void onTekerIleri() {
  //ÖNSAĞ İLERİ
  digitalWrite (on_1, HIGH); // BÖYLE DÜZ
  digitalWrite (on_2, LOW);
  analogWrite(on_hiz1, onSagHiz);
  //ÖNSOL İLERİ
  digitalWrite (on_3, LOW);
  digitalWrite (on_4, HIGH);
  analogWrite(on_hiz2, onSolHiz);
}

void onTekerDur() {
  //ÖNSAĞ İLERİ
  digitalWrite (on_1, HIGH); // BÖYLE DÜZ
  digitalWrite (on_2, HIGH);
  analogWrite(on_hiz1, onSagHiz);
  //ÖNSOL İLERİ
  digitalWrite (on_3, LOW);
  digitalWrite (on_4, LOW);
  analogWrite(on_hiz2, onSolHiz);
}

void onTekerGeri() {
  //ÖNSAĞ İLERİ
  digitalWrite (on_1, LOW); // BÖYLE DÜZ
  digitalWrite (on_2, HIGH);
  analogWrite(on_hiz1, onSagHiz * 0.9);
  //ÖNSOL İLERİ
  digitalWrite (on_3, HIGH);
  digitalWrite (on_4, LOW);
  analogWrite(on_hiz2, onSolHiz * 0.9);
}

void arkaKolIleri() {
  //KOLSAĞ İLERİ
  digitalWrite (kol_1, LOW);
  digitalWrite (kol_2, HIGH);
  analogWrite(kol_hiz1, arkaKolSagHiz);
  //KOLSOL İLERİ
  digitalWrite (kol_3, HIGH);
  digitalWrite (kol_4, LOW);
  analogWrite(kol_hiz2, arkaKolSolHiz);
}

void arkaKollarDur() {
  //KOLSAĞ İLERİ
  digitalWrite (kol_1, HIGH);
  digitalWrite (kol_2, HIGH);
  analogWrite(kol_hiz1, arkaKolSagHiz * 0.9);
  //KOLSOL İLERİ
  digitalWrite (kol_3, LOW);
  digitalWrite (kol_4, LOW);
  analogWrite(kol_hiz2, arkaKolSolHiz * 0.9);

}

void arkaKollarGeri() { // koldaki tekerler geri çalışır
  //KOLSAĞ İLERİ
  digitalWrite (kol_1, HIGH);
  digitalWrite (kol_2, LOW);
  analogWrite(kol_hiz1, arkaKolSagHiz * 0.7);
  //KOLSOL İLERİ
  digitalWrite (kol_3, LOW);
  digitalWrite (kol_4, HIGH);
  analogWrite(kol_hiz2, arkaKolSolHiz * 0.7);
}

void basamakCik() {
  int i;
  arkaTekerIleri();

  onTekerIleri();
  delay(750);
  for (i = arkabaslangic ; i >= arkabitis ; i--) {
    arka.write(i);
    delay(5);
  }
  arkaKolIleri();
  delay(1250);
  arkaTekerDur();
  onTekerDur();
  for (i = arkabitis ; i <= arkabaslangic ; i++) {
    arka.write(i);
    delay(5);
  }
  arkaKollarDur();
  arkaTekerIleri();
  onTekerIleri();
  delay(100);
  arkaTekerDur();
  onTekerDur();
  basamak++;
}
void arkayaindir() { //geri giderken robotu yavas yavas indircek
  int i;
  for (i = onbaslangic ; i <= onbitis ; i--) {
    on.write(i);
    delay(30);
  }
}


