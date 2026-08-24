const int StepX = 25;  
const int DirX  = 33;   

const int RoleX = 2;   

const int triPin = 27;  

const int RgbR = 16;    
const int RgbG = 17;    
const int RgbB = 21;     

const int sensorPin = 14;    // Dijital okuma yapılacak pin

const int analogPinBAT  = 26;   // BATARYA
const int analogPinLM35 = 13;   // LM35

const int buzzer = 4;    

const int fetPin = 32;   

int stepsX = 0;
int dutyCycle = 0;

void sendNextionCommand(const String& command) {
  Serial.print(command);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}


void setup() {
  // Serial haberleşmeyi aktif et
  Serial.begin(9600);

  // pinlerin in-out durumu
  pinMode(DirX, OUTPUT);
  pinMode(StepX, OUTPUT);
  pinMode(RoleX, OUTPUT);
  pinMode(triPin, OUTPUT);
  pinMode(RgbR, OUTPUT);
  pinMode(RgbG, OUTPUT);
  pinMode(RgbB, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fetPin, OUTPUT);

  // Buzzer ilk başta ötüp sussun
  digitalWrite(buzzer, HIGH);
  delay(5);
  digitalWrite(buzzer, LOW);

  // Timer 0, 50 Hz, 8-bit çözünürlük
  ledcSetup(0, 50, 8); ledcAttachPin(triPin, 0);
  ledcSetup(1, 5000, 8); ledcAttachPin(fetPin, 1);
}

void loop() {

  //Serial aktifken
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Satır sonuna kadar okuma
    input.trim();


    //Röle Menüsü
    if (input.startsWith("role")) {
      String tempValueRoleXStr = input.substring(4);   // "role" önekini kaldır
      int tempValueRoleX = tempValueRoleXStr.toInt();  // Tamsayıya dönüştür
      digitalWrite(RoleX, (tempValueRoleX > 0) ? HIGH : LOW);
    }


    //Triyak Menüsü
    if (input.startsWith("tri")) {
      String tempValueTriXStr = input.substring(3);  // "tri" önekini kaldır
      int dutyCycle = constrain(tempValueTriXStr.toInt(), 0, 255);
      ledcWrite(0, dutyCycle);
    }

    //MOSFET Menüsü
    if (input.startsWith("fet")) {
      String tempValueFETStr = input.substring(3);  // "fet" önekini kaldır
      int dutyCycle = constrain(tempValueFETStr.toInt(), 0, 255);
      ledcWrite(1, dutyCycle);
    }


    //RGB Led Menüsü
    if (input.startsWith("rgbr")) {
      String tempValueRgbRStr = input.substring(4);  // "rgbr" önekini kaldır
      int dutyR = constrain(tempValueRgbRStr.toInt(), 0, 255);
      analogWrite(RgbR, dutyR);
    }
    if (input.startsWith("rgbg")) {
      String tempValueRgbGStr = input.substring(4);  // "rgbg" önekini kaldır
      int dutyG = constrain(tempValueRgbGStr.toInt(), 0, 255);
      analogWrite(RgbG, dutyG);
    }
    if (input.startsWith("rgbb")) {
      String tempValueRgbBStr = input.substring(4);  // "rgbb" önekini kaldır
      int dutyB = constrain(tempValueRgbBStr.toInt(), 0, 255);
      analogWrite(RgbB, dutyB);
    }


    //Sensör Menüsü
    if (input.startsWith("sens")) {
      while (true) {
        // Çıkış komutunu sensör HIGH iken de kontrol et.
        if (Serial.available() > 0) {
          input = Serial.readStringUntil('\n');
          input.trim();
          if (input.startsWith("p4")) {
            break;
          }
        }

        int sensorValue = digitalRead(sensorPin);
        if (sensorValue == HIGH) {
          sendNextionCommand("p0.pic=5");
          delay(200);
          sendNextionCommand("n11.val=1");
          delay(200);
        } else {
          sendNextionCommand("p0.pic=4");
          delay(200);
          sendNextionCommand("n11.val=0");
          delay(200);
        }
      }
    }

    //Step Motor Menüsü
    if (input.startsWith("step")) {
      String tempValueXStr = input.substring(4);  // "step" önekini kaldır
      int tempValueX = tempValueXStr.toInt();     // Tamsayıya dönüştür
      if (tempValueX != 0) {
        digitalWrite(DirX, (tempValueX > 0) ? HIGH : LOW);
        stepsX = abs(tempValueX);

        for (int x = 0; x < stepsX; x++) {
          digitalWrite(StepX, HIGH);
          delayMicroseconds(1000);
          digitalWrite(StepX, LOW);
          delayMicroseconds(1000);
        }
      }
    }
  }
}
