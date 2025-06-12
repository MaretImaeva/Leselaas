long tidIgjen = 0;
long valgtTid = 0;  //60, 45, 30 eller 15 min

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

const int ledPins[] = {
  led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12
};

const int hoytaler = 13;

boolean laas = false;

const int button15 = A0;
const int button30 = A1;
const int button45 = A2;
const int button60 = A3;
const int buttonPause = A4;
const int buttonPluss = A5;


// noter
int C4  = 261;
int Cs4 = 277;
int D4  = 293;
int Ds4 = 311;
int E4  = 330;
int F4  = 349;
int Fs4 = 370;
int G4  = 392;
int Gs4 = 415;
int nA4 = 440;
int As4 = 466;
int B4  = 493;
int C5  = 523;

unsigned long lastMinutt = 0;
int sisteLed = -1;

void setup() {
  
  Serial.begin(9600);

  for (int i = 0; i < 11; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(hoytaler, OUTPUT);

  // Buttons er koblet til analoge pinner, men brukes som digitale
  pinMode(button15, INPUT_PULLUP);
  pinMode(button30, INPUT_PULLUP);
  pinMode(button45, INPUT_PULLUP);
  pinMode(button60, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  pinMode(buttonPluss, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(button15) == LOW) {
    knappTrykket(1);
  } else if (digitalRead(button30) == LOW) {
    knappTrykket(3);
  } else if (digitalRead(button45) == LOW) {
    knappTrykket(45);
  } else if (digitalRead(button60) == LOW) {
    knappTrykket(60);
  } else if (digitalRead(buttonPluss) == LOW) {
    Serial.println("5 min lagt til");
    leggTilTid(5);
    delay(200);
  } else if (digitalRead(buttonPause) == LOW) {
    Serial.println("Pause aktivert");
    pause();
  }

  // Trekker tid hvert minutt uten å fryse loop
  if (tidIgjen > 0 && millis() - lastMinutt >= 60000) {
    tidIgjen -= 60000;
    lastMinutt = millis();
    Serial.print("Tid igjen: ");
    Serial.println((tidIgjen / 60000.0, 2));
    Serial.println("Valgt tid:");
    Serial.println(valgtTid / 60000.0, 2);
    lysLeds();
    if (tidIgjen <= 0) {
      Serial.println("Tid ferdig");
      ferdig();
    }
  }
  
  lysLeds(); //oppdaterer lysene hver gang

  // Sjekker og teller sist bevegelse:
  //int bevegelse = digitalRead(sensor);

  //sjekkBevegelse();
 


}

void knappTrykket(int min){ //registrerer trykkene
  Serial.println(min + " minutter valgt");
    tidIgjen = 0;
    valgtTid = min*60*1000;
    leggTilTid(min);
    delay(200);
    laas = true;
    lysStartogSlutt();
}




void leggTilTid(int inputMin) {
  long minutter = (long)inputMin * 60 * 1000;
  tidIgjen += minutter;
  Serial.print("Tid som gjenstår (min): ");
  Serial.println((float)tidIgjen / 60000.0, 2);
}



void pause() {
  lyd();
  Serial.println("Pauser i 5 minutter...");
  delay(300000);  // 5 min pause
  lyd();
  Serial.println("Pause ferdig");
}


void ferdig() {
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], LOW);}
  Serial.println("Fullført! Starter avslutningseffekter.");
  lysStartogSlutt();
  victoryFanfare();
  laas = false;

}

void lysLeds() {


  if (valgtTid == 0) return;

  int lysSomSkalLyse = (valgtTid - tidIgjen) + 1;

  for (int detteLed = 2; detteLed < 13; detteLed++){
    if (detteLed < lysSomSkalLyse){
      digitalWrite(ledPins[detteLed], HIGH);
    } else {
      digitalWrite(ledPins[detteLed], LOW);
    }

  }
}


void lysStartogSlutt() {

  // Fremover
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], HIGH);
    if (sisteLed != 11) {
      digitalWrite(ledPins[sisteLed], LOW);
    }
    sisteLed = i;
    delay(100);
  }

  // Viktig: nullstill sisteLed
  sisteLed = -1;

  // Bakover
  for (int i = 10; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    if (sisteLed != -1) {
      digitalWrite(ledPins[sisteLed], LOW);
    }
    sisteLed = i;
    delay(100);
  }

  // Slå av alle LED etterpå
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Skulle gått en runde her");
}





void victoryFanfare() {
  int melody[] = {nA4, nA4, nA4, nA4, F4, G4, nA4, G4, nA4};
  int noteDurations[] = {200, 200, 200, 700, 700, 700, 400, 200, 1500};

  for (int i = 0; i < 9; i++) {
    tone(hoytaler, melody[i], noteDurations[i]);
    delay(noteDurations[i] + 20);
  }
  noTone(hoytaler);
  Serial.println("Burde ha spilt av musikk");
}

void lyd() {
  tone(hoytaler, nA4, 200);
  delay(200);
  noTone(hoytaler);
  Serial.println("enkel lyd ferdig");
}

void failedLyd() {
  int melody[] = {G4, G4, G4, Ds4};
  int noteDurations[] = {200, 200, 200, 600};

  for (int i = 0; i < 4; i++) {
    tone(hoytaler, melody[i], noteDurations[i]);
    delay(noteDurations[i] + 20);
  }
  noTone(hoytaler);
  Serial.println("dun dun dun duuuun");
  
}

void failedLys(){
    int fadeLeds[] = {3, 5, 6, 9, 10, 11};

  for (int r = 0; r < 3; r++) { // blink 3 ganger
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      for (int i = 0; i < 5; i++) {
        analogWrite(fadeLeds[i], brightness);
      }
      delay(10);
    }
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
      for (int i = 0; i < 5; i++) {
        analogWrite(fadeLeds[i], brightness);
      }
      delay(10);
    }
    Serial.println("Blinker d eller?");
  }


  // Slå av LED-ene etterpå
  for (int i = 0; i < 5; i++) {
    analogWrite(fadeLeds[i], 0);
  }
}


//sjekkBevegelse(){
//    if (motion == HIGH) {
//    Serial.println("Bevegelse oppdaget!");
//    lastMotionTime = millis();  // Oppdater siste aktivitet
//  } else {
//    // Sjekk hvor lenge det har vært stille
//    if (millis() - lastMotionTime >= timeout) {
//      Serial.println("Ingen bevegelse på 15 minutter.");
//      tidIgjen = valgtTid;
//      failedLyd();
//      digitalWrite
//    }
//  }






//sjekkBevegelse(){
//    if (motion == HIGH) {
//    Serial.println("Bevegelse oppdaget!");
//    lastMotionTime = millis();  // Oppdater siste aktivitet
//  } else {
//    // Sjekk hvor lenge det har vært stille
//    if (millis() - lastMotionTime >= timeout) {
//      Serial.println("Ingen bevegelse på 15 minutter.");
//      tidIgjen = valgtTid;
//      failedLyd();
//      digitalWrite
//    }
//  }

//  delay(1000); // Sjekk hvert sekund
//}



 

// x antall ledlys
// når tids knapp trykkes starter fokustid
// pause knapp 5 minutter, tiden stopper, fortsetter etter 5 min gått (delay, millis)
// + knapp legger 5 minutter til
// lys animasjon
// start animasjon
// sensor som blinker når man er vekke 15 minutter og nullstiller ticen (u failed)
// ved ferdig går lysene en runde og du får en viktory sound
// 
