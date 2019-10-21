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

#ifdef DEBUG_MODE
  #define DEBUG_PRINT4(p1, p2, p3, p4) Serial.print(p1); Serial.print(p2); Serial.print(p3); Serial.println(p4);
#else
  #define DEBUG_PRINT4(p1, p2, p3, p4)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT6(p1, p2, p3, p4, p5, p6) Serial.print(p1); Serial.print(p2); Serial.print(p3); Serial.print(p4); Serial.print(p5); Serial.println(p6);
#else
  #define DEBUG_PRINT6(p1, p2, p3, p4, p5, p6)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT8(p1, p2, p3, p4, p5, p6, p7, p8) Serial.print(p1); Serial.print(p2); Serial.print(p3); Serial.print(p4); Serial.print(p5); Serial.print(p6); Serial.print(p7); Serial.println(p8);
#else
  #define DEBUG_PRINT8(p1, p2, p3, p4, p5, p6, p7, p8)
#endif

#ifdef DEBUG_MODE
  #define DEBUG_PRINT12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) Serial.print(p1); Serial.print(p2); Serial.print(p3); Serial.print(p4); Serial.print(p5); Serial.print(p6); Serial.print(p7); Serial.print(p8); Serial.print(p9); Serial.print(p10); Serial.print(p11); Serial.println(p12);
#else
  #define DEBUG_PRINT12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)
#endif

#endif //SHDC_DEBUG_H
