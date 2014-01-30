/*
  OGRE Control 
*/

int inByte = 0;         // incoming serial byte
int ledPin0 = 12;
int ledPin1 = 8;

void setup()
{
  pinMode(ledPin0, OUTPUT);
  digitalWrite(ledPin0, LOW);
  
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  
  Serial.begin(115200);
  establishContact();  // send a byte to establish contact until receiver responds 
}

void establishContact() 
{
  while (Serial.available() <= 0) {
    Serial.println("Waiting");   // send an initial string
    delay(300);
  }
}

int valid = 1;
void loop()
{
  if (Serial.available() > 0) {
    valid = 1;
    
    // get incoming byte:
    inByte = Serial.read();
    if (inByte == 'a') {
      digitalWrite(ledPin0, LOW);
    } else if (inByte == 'q') {
      digitalWrite(ledPin0, HIGH);  
    } else if (inByte == 's') {
      digitalWrite(ledPin1, LOW);
    } else if (inByte == 'w') {
      digitalWrite(ledPin1, HIGH);  
    } else {
      valid = 0;
    }
  
    if (valid) {
      Serial.println("A");
    } else {
      Serial.println("N");               
    }
  }
}


