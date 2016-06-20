//basics for left side of the bot
const int lsc = 6; // PWM pin for speed control
const int lw1 = 2;
const int lw2 = 4;

//basics for right side of bot
const int rsc = 9;
const int rw1 = 7;
const int rw2 = 8;

//light sensors
const int lldr = A0;
const int rldr = A1;

//ultrasonic
const int trig = 10;
const int echo = 11;

void robotLeft() {
  Serial.print("robot_left");
  // left motor reverse
  digitalWrite(lw1, LOW);
  digitalWrite(lw2, HIGH);
  // right motor forwards
  digitalWrite(rw1, HIGH);
  digitalWrite(rw2, LOW);
}

void robotRight() {
  Serial.print("robot_right");
  //left motor forwards
  digitalWrite(lw1, HIGH);
  digitalWrite(lw2, LOW);
  //right motor reverse
  digitalWrite(rw1, LOW);
  digitalWrite(rw2, HIGH);
}

void robotForwards() {
  Serial.print("robot_forwards");
  //left motor forwards
  digitalWrite(lw1, HIGH);
  digitalWrite(lw2, LOW);
  //right motor forwards
  digitalWrite(rw1, HIGH);
  digitalWrite(rw2, LOW);
}

void robotBackwards() {
  Serial.print("robot_backwards");
  //left motor reverse
  digitalWrite(lw1, LOW);
  digitalWrite(lw2, HIGH);
  //right motor reverse
  digitalWrite(rw1, LOW);
  digitalWrite(rw2, HIGH);
}


void setup () {
  //activate left motor
  pinMode (lsc, OUTPUT);
  pinMode(lw1, OUTPUT);
  pinMode(lw2, OUTPUT);

  //activate right motor
  pinMode (rsc, OUTPUT);
  pinMode(rw1, OUTPUT);
  pinMode(rw2, OUTPUT);

  // activate photocells
  analogWrite (lsc, 200);
  analogWrite (rsc, 200);

  Serial.begin(9600);
}

void loop () {

  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;

  if ( distance >= 10) {
    analogRead(lldr);
    analogRead(rldr);
  }
  else if (analogRead(lldr) > analogRead(rldr)) {
    robotLeft();
    delay(150);
    robotForwards();
    delay(1000);
  }
  else if (analogRead(lldr) < analogRead(rldr)) {
    robotRight();
    delay(500);
    robotForwards();
    delay(1000);
  }
  else {
    robotBackwards();
    delay(500);

    robotRight();

    delay(500);
  }
}
