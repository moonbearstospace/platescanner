#include <SoftTimer.h>

int delayBetweenSteps = 5;

void step(int dir){
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B

  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delayBetweenSteps);
  
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  digitalWrite(13, dir == 0 ? HIGH : LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delayBetweenSteps);
  
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B

  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delayBetweenSteps);
    
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  digitalWrite(13, dir == 0 ? LOW : HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delayBetweenSteps);
}

void do_stepProc(Task* me){
  int step_ = digitalRead(4);
  int dir = digitalRead(2);

  if(step_ == HIGH){
    step(dir);
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  Task stepProc(10, do_stepProc);

  SoftTimer.add(&stepProc);
}
