int del = 10;
void both() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
}
void one() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
}
void none() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  both();
  delay(2000);
  one();
  delay(2000);
  none();
  delay(2000);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    Serial.print("Binary sequence: ");
    String binary = "";
    for (int i = 0; i < input.length(); i++) {
      // Convert each character to its binary equivalent
      String charBinary = String(input[i], BIN);
      // Add leading zeros to make sure each binary sequence has 8 digits
      for (int j = 0; j < (8 - charBinary.length()); j++) {
        binary += "0";
      }
      binary += charBinary;
      Serial.print(charBinary);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println(binary);
    char temp;


    for (int i = 0; i < binary.length(); i += 8) {
      String charBinary = binary.substring(i, i + 8);
      for (int j = 0; j < charBinary.length(); j++) {
        temp = charBinary[j];
        if (temp == '0') {
          one();
          delay(del);
        } else if (temp == '1') {
          both();
          delay(del);
        } else {
          none();
          delay(del);
        }
      }
      delay(del * 5);
    }
    none();
  }
}