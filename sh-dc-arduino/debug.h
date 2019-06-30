//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_DEBUG_H
#define SHDC_DEBUG_H

#ifdef DEBUG_MODE
  #define DEBUG_INIT(p1) Serial.begin(9600); while (!Serial) {} ; Serial.println(p1);
#else
  #define DEBUG_INIT(p1)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT1(p1) Serial.println(p1);
#else
  #define DEBUG_PRINT1(p1)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT2(p1, p2) Serial.print(p1); Serial.println(p2);
#else
  #define DEBUG_PRINT2(p1, p2)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT3(p1, p2, p3) Serial.print(p1); Serial.print(p2); Serial.println(p3);
#else
  #define DEBUG_PRINT3(p1, p2, p3)
#endif

#endif //SHDC_DEBUG_H
