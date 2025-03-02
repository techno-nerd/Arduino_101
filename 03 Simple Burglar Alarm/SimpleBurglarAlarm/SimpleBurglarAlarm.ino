const int LED_PIN = 2; //LED for flashing lights
const int BUZZER_PIN = 3; //Buzzer for alarm sound
const int BEEP_FREQ = 200;  //Time (milliseconds) between each beep and flash
bool actuatorActive = false;

const int TRIG_PIN = 9; //For Ultrasonic sensor output
const int ECHO_PIN = 10; //For Ultrasonic sensor input

const int BUTTON_PIN = 7; //For reset button

const int MIN_DISTANCE = 10; //Distance (cm) before alarm rings

float duration; //In microseconds
float distance; //In centimeters  

bool alarmActivated = false;
long alarmTime;

void setup() {
  Serial.begin(9600);
  alarmTime = millis();
  distance = 3.4028235E+38; //Maximum value for float to begin with

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT); //Sends a pulse
  pinMode(ECHO_PIN, INPUT); //Recieves the echo

  pinMode(BUTTON_PIN, INPUT_PULLUP);
    
}

void loop() {
  
  distance = measureDistance();
  Serial.println(distance);

  if(distance < MIN_DISTANCE) { //Intruder detected! Sound the alarm
    alarmActivated = true;
    alarmActivated = millis();
  }
  else { //No intruder (or the intruder ran away)
    reset();
  }

  if(alarmActivated) {
    if((millis() - alarmTime) >= BEEP_FREQ) {
      toggleActuators();
      alarmTime = millis();
    }
  }

  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Reset manually");
    reset();
    delay(5000); //Delay to prevent alarm from reactivating immediately
  }

}

/*
  Measures and returns distance using ultrasonic sensor
*/
double measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); //Sends a pulse for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  double dist = (duration*0.0343)/2;
  return dist > 0 ? dist : distance; //Ternary operator: Think of it as if(dist > 0), then return dist, otherwise return the global variable distance
}

/*
  Turns LED and buzzer on if off, and vica-versa
*/
void toggleActuators() {
  if(actuatorActive) { //Already on, so turn both off
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
  else { //Off, so turn both on
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 85);
  }

  actuatorActive = !actuatorActive; //Flip the actuatorActive variable
}

void reset() {
  alarmActivated = false;
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
}
