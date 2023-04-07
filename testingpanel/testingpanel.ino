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
    String input2 = Serial.readString();
    char input = input2[0];
    if (input == '1') {
      both_on();
    } else if (input == '2') {
      one();
    } else if (input == '3') {
      both_off();
    } else {
    }
    delay(500);
    Serial.println(analogRead(panel));
  }
}

void both_on() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

void both_off() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void one() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
}


// values 
// 2 led on
// 1 led
// both led off

// with ambient light but close
// 303
// 286
// 251

// without ambiwnt light practical distance
// 272
// 140
// 32
// practical case
// 289
// 252
// 137