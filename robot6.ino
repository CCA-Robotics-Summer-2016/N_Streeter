//basics for left side of the bot
const int lsc = 9; // PWM pin for speed control
const int lw1 = 7;
const int lw2 = 8;

//basics for right side of bot
const int rsc = 4;
const int rw1 = 2;
const int rw2 = 6;

//light sensors
const int lldr = A0;
const int rldr = A1;

//ultrasonic
const int trig = 11;
const int echo = 12;

//turns robot left
void robotLeft() {
  Serial.println("robot_left");
  // left motor reverse
  digitalWrite(lw1, LOW);
  digitalWrite(lw2, HIGH);
  // right motor forwards
  digitalWrite(rw1, LOW);
  digitalWrite(rw2, HIGH);
}

//turn robot right
void robotRight() {
  Serial.println("robot_right");
  //left motor forwards
  digitalWrite(lw1, HIGH);
  digitalWrite(lw2, LOW);
  //right motor reverse
  digitalWrite(rw1, HIGH);
  digitalWrite(rw2, LOW);
}

//move robot forwards
void robotForwards() {
  Serial.println("robot_forwards");
  //left motor forwards
  digitalWrite(lw1, HIGH);
  digitalWrite(lw2, LOW);
  //right motor forwards
  digitalWrite(rw1, LOW);
  digitalWrite(rw2, HIGH);
}

//move robot backwards
void robotBackwards() {
  Serial.println("robot_backwards");
  //left motor reverse
  digitalWrite(lw1, LOW);
  digitalWrite(lw2, HIGH);
  //right motor reverse
  digitalWrite(rw1, HIGH);
  digitalWrite(rw2, LOW);
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

  //activate ultrasonic sensors
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // activate photocells
  analogWrite (lsc, 200);
  analogWrite (rsc, 200);

  Serial.begin(9600);
}

void loop () {

  long duration, distance;

  //sends pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //measure time between echos, tells how far away objects are
  duration = pulseIn(echo, HIGH);

  //calculates distance to object in cm
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
  Serial.print("cm");

  //actions if distance>10
  if ( distance >= 10) {
    robotForwards();
    delay(500);

    if (analogRead(lldr) > analogRead(rldr)) {
      Serial.println("left");
      robotLeft();
      delay(500);
      robotForwards();
      delay(2000);
    }
    else if (analogRead(lldr) < analogRead(rldr)) {
      Serial.println("right");
      robotRight();
      delay(500);
      robotForwards();
      delay(2000);
    }
  } // end of distnace > 10

  //actions if distance<10
  if ( distance <= 10) {
    Serial.println("reverse");
    robotBackwards();
    delay(3000);
    robotRight();
    delay(500);
  }
}
