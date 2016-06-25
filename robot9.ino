//basics for left side of the bot
const int lsc = 9; // PWM pin for speed control
const int lw1 = 7;
const int lw2 = 8;

//basics for right side of bot
const int rsc = 4;
const int rw1 = 2;
const int rw2 = 6;

//light sensors
const int lldr = A1;
const int rldr = A0;

//ultrasonic
const int trig = 11;
const int echo = 12;

//records last movement command
int whatIDidLast; // 1 means forward and left
// 2 means reverse and left
// 3 means reverse and right
// 4 means forwards and right
const int forwardAndLeft = 1;
const int forwardAndRight = 2;
const int reverseAndRight = 3;
const int reverseAndLeft = 4;

//BASIC MOVEMENT COMMANDS

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
//END BASIC MOVEMENT COMMANDS

//FORWARD MOVEMENT COMMANDS
void robotVeerLeft() {
  int whatIDidLast = forwardAndLeft;
  Serial.println("veer left");
  //set motor power
  analogWrite(lsc, 90);
  analogWrite(rsc, 160);
  //forwards
  robotForwards();
  delay(250);
  //set motor power for course correction
  analogWrite(lsc, 110);
  analogWrite(rsc, 140);
  //forwards
  robotForwards();
  delay(250);
}

void robotVeerRight() {
  int whatIDidLast = forwardAndRight;
  Serial.println("veer right");
  //set motor power
  analogWrite(lsc, 160);
  analogWrite(rsc, 90);
  //forwards
  robotForwards();
  delay(250);
  //set motor power for course correction
  analogWrite(lsc, 140);
  analogWrite(rsc, 110);
  //forwards
  robotForwards();
  delay(250);
}

//REVERSE MOVEMENT COMMANDS
void robotReverseVeerRight() {
  int whatIDidLast = reverseAndRight;
  Serial.println("reverse veer right");
  //set motor power
  analogWrite(lsc, 160);
  analogWrite(rsc, 90);
  //reverse
  robotBackwards();
  delay(500);
  //set motor power for couse correction
  analogWrite(lsc, 140);
  analogWrite(rsc, 110);
  //reverse
  robotBackwards();
  delay(500);
  //turn right
  robotRight();
  delay(250);
}

void robotReverseVeerLeft() {
  int whatIDidLast = reverseAndLeft;
  Serial.println("reverse veer left");
  //set motor power
  analogWrite(lsc, 90);
  analogWrite(rsc, 160);
  //reverse
  robotBackwards();
  delay(500);
  //set motor power for course correction
  analogWrite(lsc, 110);
  analogWrite(rsc, 140);
  //reverse
  robotBackwards();
  delay(500);
  robotLeft();
  delay(250);
}
//END COMMANDS

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

  //if distance > 10cm activate and read photocells
  if (distance >= 10) {
    Serial.println("enough room");
    analogRead(lldr);
    analogRead(rldr);
  }

  //FORWARD COMMANDS

  //veer left while light is stronger on left and the distance is
  //greater than 10cm
  while (analogRead(lldr) >= (analogRead(rldr)) && (distance >= 10)) {
    robotVeerLeft();
    break;
    delay(500);
    //read photocells
    analogRead(lldr);
    analogRead(rldr);
    //if greatest light source has changed sides end code section
    if (analogRead(lldr) <= (analogRead(rldr))) {
      break;
    }
  }

  //veer right while light on right is stronger and the distance is
  //greater than 10cm
  while (analogRead(rldr) >= (analogRead(lldr)) && (distance >= 10)) {
    robotVeerRight();
    break;
    delay(500);
    //read photocells
    analogRead(lldr);
    analogRead(rldr);
    //if greatest light source has changed sides end code section
    if (analogRead(lldr) >= (analogRead(rldr))) {
      break;
    }
  }

  //REVERSE COMMANDS

  //reverse from greatest light source on left if distance is < than 10cm
  while (analogRead(lldr) >= (analogRead(rldr)) && (distance <= 10)) {
    if (whatIDidLast == reverseAndRight) {
      robotReverseVeerLeft();
    }
    else {
      robotReverseVeerRight();
    }
    break;
    delay(500);
    //read photocells
    analogRead(lldr);
    analogRead(rldr);
    //if greatest light source has changed sides end code section
    if (analogRead(lldr) <= (analogRead(rldr))) {
      break;
    }
  }

  //reverse from greatest light source on right if distance < 10cm
  while (analogRead(rldr) >= (analogRead(lldr)) && (distance <= 10)) {
    if (whatIDidLast == reverseAndLeft) {
      robotReverseVeerRight();
    }
    else {
      robotReverseVeerLeft();
    }
    break;
    delay(500);
    //read photocells
    analogRead(lldr);
    analogRead(rldr);
    //if greast light source has changed sides end code section
    if (analogRead(lldr) >= (analogRead(rldr))) {
      break;
    }
  }
}
