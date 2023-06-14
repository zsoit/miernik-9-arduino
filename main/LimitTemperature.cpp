// class LimitTemperature
// {
// private:
//   int Min;
//   int Max;
//   int SIA;
//   int SIB;
//   int choose;

//   int a = 1;
//   int b = 1;
//   int t = 0;

// public:
//   LimitTemperature(int detectPress) : Min(0), Max(0), SIA(2), SIB(3), Btn(4) {
//   }

//   void setup()
//   {
//     pinMode(SIB, INPUT);
//     pinMode(SIA, INPUT);
//   }

//   void setMin(int newMin) { Min = newMin; }
//   void setMax(int newMax) { Max = newMax; }

//   int getMin() { return Min; }
//   int getMax() { return Max; }

//   void EncoderUsing()
//   {
//     Btn.update();

//     int choose = Btn.detectPress();

//     if (choose == 1)
//     {
//       a = digitalRead(SIA);
//       if ((b == 1) && (a == 0) && ((millis() - t) > 50))
//       {
//         t = millis();
//         if (digitalRead(SIB) == 1)
//         {
//           setMax(getMax() + 1);
//           Serial.println("MAX: " + String(getMax()));
//         }
//         else
//         {
//           setMax(getMax() - 1);
//           Serial.println("MAX: " + String(getMax()));
//         }
//       }
//     }

//     if (choose == 0)
//     {
//       a = digitalRead(SIA);
//       if ((b == 1) && (a == 0) && ((millis() - t) > 50))
//       {
//         t = millis();
//         if (digitalRead(SIB) == 1)
//         {
//           setMin(getMin() + 1);
//           Serial.println("MIN: " + String(getMin()));
//         }
//         else
//         {
//           setMin(getMin() - 1);
//           Serial.println("MIN: " + String(getMin()));
//         }
//       }
//     }
//   }
// };