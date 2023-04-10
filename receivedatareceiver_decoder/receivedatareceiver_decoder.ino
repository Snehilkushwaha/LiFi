//kashish
int ambient, one, zero;
int del = 25;

// Define the generator polynomials for the two convolutional codes
const uint8_t g1[] = {1, 0, 1, 1, 1}; // [5 7]
const uint8_t g2[] = {1, 1, 1, 0, 1}; // [7 5]

// Turbo decode an interleaved binary sequence using two 3-bit convolutional codes
void turbo_decode(const uint8_t* input, int len, uint8_t* output) {
  // Initialize the decoder with an estimate of the transmitted codeword
  uint8_t state1 = 0, state2 = 0;
  uint8_t estimate1[len], estimate2[len];
  for (int i = 0; i < len; i++) {
    estimate1[i] = 0;
    estimate2[i] = 0;
  }

  // Perform soft-decision decoding using the generator polynomials
  for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
    // Soft-decision decode the first codeword using the generator polynomial of the second code as the feedback polynomial
    for (int i = 0; i < len; i++) {
      // Compute the soft-decision estimate of the first codeword
      uint8_t in1 = input[2*i] ^ (state2 >> 2);
      uint8_t out1 = 0;
      for (int j = 0; j < 3; j++) {
        out1 |= ((in1 >> j) & 0x01) << (2 - j);
      }
      uint8_t estimate = (out1 >> 1) & 0x01;
      if ((out1 & 0x04) != 0) estimate = 1 - estimate;
      estimate1[i] = estimate;

      // Update the state of the first convolutional code
      state1 = ((state1 << 1) & 0x06) | (estimate & 0x01);

      // De-interleave the second codeword and compute the soft-decision estimate using the first code as the feedback polynomial
      uint8_t in2 = input[perm[2*i+3]] ^ (state1 >> 2);
      uint8_t out2 = 0;
      for (int j = 0; j < 3; j++) {
        out2 |= ((in2 >> j) & 0x01) << (2 - j);
      }
      estimate = (out2 >> 1) & 0x01;
      if ((out2 & 0x04) != 0) estimate = 1 - estimate;
      estimate2[i] = estimate;

            // Update the state of the second convolutional code
      state2 = ((state2 << 1) & 0x06) | (estimate & 0x01);
    }

    // Interleave the resulting soft-decision estimates
    uint8_t interleaved[len];
    for (int i = 0; i < len; i++) {
      interleaved[perm[i]] = estimate2[i];
    }

    // Soft-decision decode the second codeword using the generator polynomial of the first code as the feedback polynomial
    for (int i = 0; i < len; i++) {
      // Compute the soft-decision estimate of the second codeword
      uint8_t in2 = interleaved[i] ^ (state1 >> 2);
      uint8_t out2 = 0;
      for (int j = 0; j < 3; j++) {
        out2 |= ((in2 >> j) & 0x01) << (2 - j);
      }
      uint8_t estimate = (out2 >> 1) & 0x01;
      if ((out2 & 0x04) != 0) estimate = 1 - estimate;

      // Update the state of the second convolutional code
      state2 = ((state2 << 1) & 0x06) | (estimate & 0x01);

      // Interleave the resulting soft-decision estimates
      output[perm[i]] = estimate1[i];
    }

    // Check for convergence
    bool converged = true;
    for (int i = 0; i < len; i++) {
      if (estimate1[i] != output[i]) {
        converged = false;
        break;
      }
    }
    if (converged) break;
  }
}



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
  while (analogRead(A0) > (ambient+20)){
    if (analogRead(A0) > (one-20) && analogRead(A0) < (one+20)) //one
    {
      binary += "1";
      delay(del);
    }
    else if (analogRead(A0) > (zero-20))
    {
      binary += "0";
      delay(del);
    }

  }
  String output_decoder;
  turbo_decoder(binary, binary.length(), output_decoder);
  for (int i = 0; i < output_decoder.length(); i += 8) {
    String charBinary = output_decoder.substring(i, i + 8);
    char charOutput = strtol(charBinary.c_str(), NULL, 2);
    output += charOutput;
  }
  if (output.length()){
    
  Serial.print("Output string: ");
  Serial.println(output);
  //Serial.println(binary);
  }

}
