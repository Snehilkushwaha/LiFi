int ambient, one, zero;
void getbyte
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
  Serial.println(one);
  Serial.println(zero);

}

void loop() {
  // Convert the binary sequence back to a string
  
  String output = "";
  for (int i = 0; i < binary.length(); i += 8) {
    String charBinary = binary.substring(i, i + 8);
    char charOutput = strtol(charBinary.c_str(), NULL, 2);
    output += charOutput;
  }
  Serial.print("Output string: ");
  Serial.println(output);

}
