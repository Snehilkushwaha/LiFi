//kashish
int ambient, one, zero;
int del = 10;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  delay(1000);
  one = analogRead(A0);
  delay(2000);
  zero = analogRead(A0);
  delay(2000);
  ambient = analogRead(A0);
  delay(1000);

  Serial.println(ambient);
  Serial.println(zero);
  Serial.println(one);
}

void loop() {
  // Convert the binary sequence back to a string
  String output = "";
  String binary = "";
  int count = 0;
  while (analogRead(A0) > (ambient + 20)) {
    count++;
    if (count == 8) {
      count = 0;
      delay(del * 5);
    } else {
      if (analogRead(A0) > (one - 20) && analogRead(A0) < (one + 20))  //one
      {
        binary += "1";
        delay(del);
      } else if (analogRead(A0) > (zero - 20)) {
        binary += "0";
        delay(del);
      }
    }
  }

  for (int i = 0; i < binary.length(); i += 8) {
    String charBinary = binary.substring(i, i + 8);
    char charOutput = strtol(charBinary.c_str(), NULL, 2);
    output += charOutput;
  }
  if (output.length()) {

    Serial.print("Output string: ");
    Serial.println(output);
    Serial.println(binary);
  }
}
