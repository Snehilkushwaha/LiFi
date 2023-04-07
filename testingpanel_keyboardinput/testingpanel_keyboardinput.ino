#define led1 11
#define led2 10
#define panel A0

void setup() {
  Serial.begin(9600);
  pinMode(panel, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    if (input == '1') {
      both_on();
    } else if (input == '2') {
      one();
    } else if (input == '3') {
      both_off();
    }
  }
}

void both_on() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  delay(100);
  Serial.println(analogRead(panel));
}

void both_off() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(100);
  Serial.println(analogRead(panel));
}

void one() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(100);
  Serial.println(analogRead(panel));
}


// Serial.println(analogRead(panel));
// digitalWrite(led1, HIGH);
// digitalWrite(led2, HIGH);
// Serial.println(analogRead(panel));
// delay(500);
// digitalWrite(led2, LOW);
// Serial.println(analogRead(panel));
// delay(500);
// digitalWrite(led2, HIGH);
// Serial.println(analogRead(panel));
// delay(500);
// digitalWrite(led2, LOW);
// digitalWrite(led1, LOW);
// //Serial.println(analogRead(panel));
// delay(500);
