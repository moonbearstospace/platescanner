#include <SoftTimer.h>

const int delayBetweenSteps = 15;

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

void do_mainStepProc(Task* me){
  bool forButton = digitalRead(2) == HIGH;
  bool bacButton = digitalRead(4) == HIGH;
  if(forButton == bacButton){
    return;
  }
  if(forButton){
    step(1);
  }
  if(bacButton){
    step(0);
  }
}

void do_slaveStepProc(Task* me){
  bool forButton = digitalRead(5) == HIGH;
  bool bacButton = digitalRead(6) == HIGH;
  if(forButton == bacButton){
    digitalWrite(10, LOW);
    return;
  }
  if(forButton){
    digitalWrite(10, HIGH);
    digitalWrite(7, HIGH);
  }
  if(bacButton){
    digitalWrite(10, HIGH);
    digitalWrite(7, LOW);
  }
}

void setup(){
  Serial.begin(9600);
  
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards???
  
  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);

  Task mainStepProc(10, do_mainStepProc);
  Task slaveStepProc(10, do_slaveStepProc);

  SoftTimer.add(&mainStepProc);
  SoftTimer.add(&slaveStepProc);
}

