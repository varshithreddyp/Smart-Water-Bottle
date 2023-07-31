const int TRIG_PIN   = 3; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN   = 2; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int BUZZER_PIN = 4; // Arduino pin connected to Piezo Buzzer's pin
const int maxWaterLevel = 200;
const int minWaterLevel = 20;
const int emptyThreshold = 50; 
const int fullThreshold = 80;

void setup() {
  Serial.begin (9600);         // initialize serial port
  pinMode(TRIG_PIN, OUTPUT);   // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);    // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  long duration = pulseIn(ECHO_PIN, HIGH);
  int WaterLevel = duration/2/29.1;
   if(minWaterLevel > maxWaterLevel){
    digitalWrite(BUZZER_PIN, HIGH);} // turn on Piezo Buzzer
  else{
    digitalWrite(BUZZER_PIN, LOW);} // turn off Piezo Buzzer
   if (WaterLevel >= minWaterLevel && WaterLevel <= maxWaterLevel) {
    // Print the water level to the serial monitor
    Serial.print("Water level: ");
    Serial.print(WaterLevel);
    Serial.println(" mm");
      if (WaterLevel <= emptyThreshold) {
      Serial.println("The bottle is empty!");
      // Sound the buzzer to indicate low water level
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
    }
      if (WaterLevel >= fullThreshold) {
      Serial.println("The bottle is full!");
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);      
    }
  }  // calculate the distance
   delay(500);
}