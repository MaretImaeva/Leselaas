//Koden per nå, skal prøve å ordne github straks:
int tidIgjen = 0;
int valgtTid = 0;  //60, 45, 30 eller 15 min
 
//alle ledlysene;
 
// const int ledPins[12]= {
// //alle må kobles til en pin. Udefinert per nå
const int led2 = 2; 
const int led3 = 3;
const int led4 = 4;
const int led5 = 5;
const int led6 = 6;
const int led7 = 7;
const int led8 = 8;
const int led9 = 9;
const int led10 = 10;
const int led11 = 11;
const int led12 = 12;
const int led13 = 13;

// const int ledPins[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
 
const int button15 = A0;
const int button30 = A1;
const int button45 = A2;
const int button60 = A3;
const int buttonPause = A4;
const int buttonPluss = A5;
 
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);

 
  pinMode(button15, INPUT_PULLUP);
  pinMode(button30, INPUT_PULLUP);
  pinMode(button45, INPUT_PULLUP);
  pinMode(button60, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  pinMode(buttonPluss, INPUT_PULLUP);
 
  lysLeds();
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
    if (digitalRead(button15) == LOW) {
    tidIgjen = 0; //nullstiller tid igjen for sikkerhets skyld
    valgtTid = 15; //setter valgte tiden lik dette. Variabel trengs når tiden igjen og valgt tid skal sammenlignes senere
    leggTilTid(15);
    delay(200); // Kort pause for å unngå å registrere samme trykk flere ganger
  } else if (digitalRead(button30) == LOW) {
    tidIgjen = 0;
    valgtTid = 30;
    leggTilTid(30);
    delay(200);
  } else if (digitalRead(button45) == LOW) {
    tidIgjen = 0;
    valgtTid = 45;
    leggTilTid(45);
    delay(200);
  } else if (digitalRead(button60) == LOW) {
    tidIgjen = 0;
    valgtTid = 60;
    leggTilTid(60);
    delay(200);
  } else if (digitalRead(buttonPluss) == LOW) {
    leggTilTid(300000);
    delay(200);
  } else if (digitalRead(buttonPause) == LOW) {
    pause(300000);
  }
 
  for (tidIgjen; tidIgjen > 0; tidIgjen--){
    delay(1000);
   
  }
 
}
 
 
void leggTilTid(int input){ //når det legges til tid ved + knappen eller ved start
tidIgjen += input;
}
 
void pause(){
  delay(300000);  //5min pause
}
 
 
void lysLeds(){
  int lysSomSkalLys = (valgtTid - tidIgjen) * 12 / valgtTid;
   
    for (int i = 2; i < 13; i++) {
        if (i < lysSomSkalLys) {
            digitalWrite(ledPins[i], HIGH);  // Slår på LED
        } else {
            digitalWrite(ledPins[i], LOW);   // Slår av LED
        }
    }
}
 
 
void lysStartogSlutt(){
  for (int i = 0; i < 12; i++) {
    digitalWrite(ledPins[i], HIGH);  // Slår på LED
    if (i != 1){
      last = i -1;
      digitalWrite(ledPins[last], LOW);
    delay(500);
    }
 
}
 
 
// x antall ledlys
// når tids knapp trykkes starter fokustid
// pause knapp 5 minutter, tiden stopper, fortsetter etter 5 min gått (delay, millis)
// + knapp legger 5 minutter til
// lys animasjon
// start animasjon
// sensor som blinker når man er vekke 15 minutter og nullstiller ticen (u failed)
// ved ferdig går lysene en runde og du får en viktory sound
//
 
