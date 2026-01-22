int brakePin = 2;    
int hornPin = 3;     
int leftPin = 4;     
int rightPin = 5;     
int motorPin = 6;     // Motor control pin (PWM)
int brakeLed = 9;     
int leftLed = 10;     
int rightLed = 11;    
int buzzer = 12;      

char inputData;        // For serial data
int speedValue = 0;   
int speedkm=0; // PWM value (0–255)
bool brakeApplied = false;

void setup()  
{ 
  pinMode(motorPin, OUTPUT);   
  pinMode(brakePin, INPUT_PULLUP);
  pinMode(hornPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  
  pinMode(brakeLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);          
  Serial.println("Vehicle Control System ");
  Serial.println(" control motor gear:");
  Serial.println("0 = Neutral, 1 = 1st Gear, 2 = 2nd Gear, 3 = 3rd Gear, 4 = 4th Gear, 5 = Reverse Gear"); 
} 

void loop() { 
  // ===== SERIAL INPUT FOR GEAR CONTROL =====
  if (Serial.available() > 0) { 
    inputData = Serial.read();  

    if (inputData >= '0' && inputData <= '5') { 
      int gear = inputData - '0';

      switch (gear) {
        case 0: speedValue = 0;speedkm = 0;Serial.println("Neutral Gear - No acceleration"); break;
        case 1: speedValue = 230; speedkm = 20;Serial.println("1st Gear Engaged"); break;
        case 2: speedValue = 180;speedkm = 50;Serial.println("2nd Gear Engaged"); break;
        case 3: speedValue = 120;speedkm = 75;Serial.println("3rd Gear Engaged"); break;
        case 4: speedValue = 80;speedkm = 100;Serial.println("4th Gear Engaged"); break;
        case 5: speedValue = 230;speedkm = 10;Serial.println("Reverse Gear (Low Speed)"); break;
      }

      Serial.print("Speed(Km): "); 
      Serial.println(speedkm);
    }  
    else { 
      Serial.print("Invalid input: "); 
      Serial.println(inputData); 
    } 
  } 

  // ===== BRAKE CONTROL =====
  if (digitalRead(brakePin) == LOW) { 
    analogWrite(motorPin, 0);   // Stop motor 
    digitalWrite(brakeLed, HIGH); 
    if (!brakeApplied) {
      Serial.println("Brake Applied - Vehicle Stopped");
      brakeApplied = true;
    }
  } 
  else { 
    analogWrite(motorPin, speedValue); 
    digitalWrite(brakeLed, LOW); 
    brakeApplied = false;
  }

  // ===== HORN CONTROL =====
  if (digitalRead(hornPin) == LOW) { 
    digitalWrite(buzzer, HIGH); 
    Serial.println("Horn On");
    delay(1000);
  } 
  else { 
    digitalWrite(buzzer, LOW); 
  }

  // ===== LEFT INDICATOR =====
  if (digitalRead(leftPin) == LOW) { 
    digitalWrite(leftLed, HIGH); 
    Serial.println("Left Indicator On");
    delay(1000);
  } 
  else { 
    digitalWrite(leftLed, LOW); 
  }

  // ===== RIGHT INDICATOR =====
  if (digitalRead(rightPin) == LOW) { 
    digitalWrite(rightLed, HIGH); 
    Serial.println("Right Indicator On");
    delay(1000);
  } 
  else { 
    digitalWrite(rightLed, LOW); 
  }

  delay(1000); 
}

