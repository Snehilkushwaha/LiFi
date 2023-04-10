int del = 25;
// Define the generator polynomials for the two convolutional codes
const uint8_t g1[] = {1, 0, 1, 1, 1}; // [5 7]
const uint8_t g2[] = {1, 1, 1, 0, 1}; // [7 5]

// Define the interleaver permutation indices
const uint8_t perm[] = {0, 2, 4, 1, 3, 5};

// Turbo encode a binary sequence using two 3-bit convolutional codes
void turbo_encode(const uint8_t* input, int len, uint8_t* output) {
  uint8_t state1 = 0, state2 = 0;
  for (int i = 0; i < len; i++) {
    // Encode using the first convolutional code
    uint8_t in1 = input[i] ^ (state1 >> 2);
    uint8_t out1 = 0;
    for (int j = 0; j < 3; j++) {
      out1 |= ((in1 >> j) & 0x01) << (2 - j);
    }
    state1 = ((state1 << 1) & 0x06) | (input[i] & 0x01);

    // Encode using the second convolutional code
    uint8_t in2 = input[i] ^ (state2 >> 2);
    uint8_t out2 = 0;
    for (int j = 0; j < 3; j++) {
      out2 |= ((in2 >> j) & 0x01) << (2 - j);
    }
    state2 = ((state2 << 1) & 0x06) | (input[i] & 0x01);

    // Interleave the two codewords and store in the output buffer
    for (int j = 0; j < 3; j++) {
      output[perm[2*i+j]] = (out1 >> j) & 0x01;
      output[perm[2*i+j+3]] = (out2 >> j) & 0x01;
    }
  }
}

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
    char* binary;
    for (int i = 0; i < input.length(); i++) {
      // Convert each character to its binary equivalent
      String charBinary = String(input[i], BIN);
      // Add leading zeros to make sure each binary sequence has 8 digits
      for (int j = 0; j < (8 - charBinary.length()); j++) {
        *binary += "0";
      }
      *binary += charBinary;
      Serial.print(charBinary);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println(binary);
    char temp;
    // int count = 0;
    String output;
    turbo_encode(binary, binary.length(), output);
    for (int i = 0; i < output.length(); i++) {
      temp = output[i];
      // if (count == 8){
      //   count = 0;
      //   none();
      //   delay(del);
      // }
      //count++;
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
    none();
  }
}