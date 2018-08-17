#include <M5Stack.h>
#include "const.h"

// M5Stack inferences N numerals started from s in MNIST dataset x[] which is pixel data of a handwritten numeral image.
const int s = 10, N = 10; 
float z1[N1], z2[N2], y[N3];

void Transmission(const float* input, float *output, int numInput, int numOutput, const float* W, const float* b, bool sigmoid) {
  for (int i = 0; i < numOutput; ++i) {
    for (int j = 0; j < numInput; ++j) output[i] += W[j * numOutput + i] * input[j];
    output[i] += b[i];
    if (sigmoid) output[i] = 1.0 / (1.0 + exp(-output[i]));
  }
}

void setup() {
  M5.begin();
  for (int j = 0; j < N; ++j) for (int i = 0; i < 784; ++i) 
    M5.Lcd.fillRect(i%28 + j*28, i/28 + 50, 1, 1, (int)(x[s + j][i]*31)*2048 + (int)(x[s + j][i]*63)*32 + (int)(x[s + j][i]*31));
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("\n\n\n\n\n\n\n\nM5Stack's recognition : \n\n");
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < N1; ++i) z1[i] = 0;
    for (int i = 0; i < N2; ++i) z2[i] = 0;
    for (int i = 0; i < N3; ++i) y[i] = 0;
    Transmission(x[s + j], z1, N0, N1, (const float*)W1, b1, true);
    Transmission(z1, z2, N1, N2, (const float*)W2, b2, true);   
    Transmission(z2, y, N2, N3, (const float*)W3, b3, false);
    int p = 0;      // p is inferenced numerals.
    for (int i = 0; i < N3; ++i) p = (y[i] > y[p] ? i : p);   
    M5.Lcd.print(p);
  }
}

void loop() {
}
