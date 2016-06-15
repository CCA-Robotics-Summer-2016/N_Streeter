const int numberOfReadings = 600;
int measurements[numberOfReadings] ;
const int ldrPin = A0;

void
 
void setup() {
  Serial.begin(9600);
}
 
 
void loop() {
 
  for (int readings = 0; readings < numberOfReadings/60; readings++) {
    measurements[readings] = analogRead(ldrPin);
    delay(.1);
  }
 
 
  // calculate the average
  int sum = 0;
  
  for (int readings = 0; readings < numberOfReadings/60; readings++) {
    sum = sum + measurements[readings];
  }
 
  int average = sum / numberOfReadings/60;
 
  // what's the difference between print() and println()?
  Serial.print("the highest reading is ");
  Serial.println(measurements[highestReading()]);
  Serial.print("the highest reading is");
  Serial.println(measurements[averageReading()]);
  Serial.print("the maximum is");
  Serial.println(measurements[maximumReading()];
}
 
// return the index of the highest reading
// if there are multiple readings return one of them
int highestReading() {
 
  int latestHighestReading = 0;
 
  for (int readings = 0; readings < numberOfReadings/60; readings++) 
  { 
    if (measurements[readings] > measurements[latestHighestReading]) 
    {
      latestHighestReading = readings;
    }
  }
  return latestHighestReading;
 
}

int averageReading() {
 
  int latestAverageReading = 0;
 
  for (int readings = 0; readings < numberOfReadings/60; readings++) 
  { 
      latestAverageReading = readings/(numberOfReadings/60);
    }
}

int maximumReading() {
 
  int latestMaximumReading = 0;
 
  for (int readings = 0; readings < numberOfReadings/60; readings++) 
  { 
      latestMaximumReading = measurements[readings];
    }
}
