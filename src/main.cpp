#include <Arduino.h>

#ifndef SERIAL_TO_TEST
#define SERIAL_TO_TEST Serial
#endif

#ifndef BAUDRATE
#define BAUDRATE 115200
#endif

void setup() { SERIAL_TO_TEST.begin(BAUDRATE); }

void printWithScaleChar(float val) {
  if (val >= 1000000) {
    SERIAL_TO_TEST.print(val / 1000000);
    SERIAL_TO_TEST.print("M");
  } else if (val >= 1000) {
    SERIAL_TO_TEST.print(val / 1000);
    SERIAL_TO_TEST.print("K");
  } else {
    SERIAL_TO_TEST.print(val);
  }
}

// String chars100 = String("0aaaaaaaaa") + "1aaaaaaaaa" + "2aaaaaaaaa" +
//                   "3aaaaaaaaa" + "4aaaaaaaaa" + "5aaaaaaaaa" + "6aaaaaaaaa" +
//                   "7aaaaaaaaa" + "8aaaaaaaaa" + "9aaaaaaaaa";

// String chars1000 = chars100 + chars100 + chars100 + chars100 + chars100 +
//                    chars100 + chars100 + chars100 + chars100 + chars100;

String chars10 = "abcdefghij";
// String chars20 = chars10 + chars10;

void printKiloBytes(uint32_t kiloBytes) {
  auto start = millis();
  // for (int i = 0; i < kiloBytes * 1000; ++i) {
  //   SERIAL_TO_TEST.print("a");
  // }
  for (int i = 0; i < kiloBytes * 100; ++i) {
    SERIAL_TO_TEST.print(chars10);
  }
  // for (int i = 0; i < kiloBytes * 50; ++i) {
  //   SERIAL_TO_TEST.print(chars20);
  // }
  // for (int i = 0; i < kiloBytes * 10; ++i) {
  //   SERIAL_TO_TEST.print(chars100);
  // }
  // for (int i = 0; i < kiloBytes; ++i) {
  //   SERIAL_TO_TEST.print(chars1000);
  // }
  Serial.println();
  auto diffMs = millis() - start;
  SERIAL_TO_TEST.println("print " + String(kiloBytes) + "K for " +
                         String(diffMs) + "ms");
  if (diffMs == 0) {
    SERIAL_TO_TEST.println("so fast not to measure speed");
  } else {
    auto bytePerSec = (double)kiloBytes * 1000 * 1000 / diffMs;
    printWithScaleChar(bytePerSec);
    SERIAL_TO_TEST.println(" byte/s");
    auto bitPerSec = bytePerSec * 10;
    printWithScaleChar(bitPerSec);
    SERIAL_TO_TEST.println(" bit/s");
  }
  SERIAL_TO_TEST.flush();
}

void loop() {
  printKiloBytes(10);
  delay(1000);
  printKiloBytes(1);
  delay(1000);
}
