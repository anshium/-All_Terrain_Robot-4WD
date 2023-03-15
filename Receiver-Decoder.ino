//Receiver Decoder. Input 4-bit signal to motoR control
//(Receiver Code)
//15th March, 2023
//The goal is to write code that would control the 4 motors based on the command received
//The four motors are DC motors

//Pins for DC motors
//Left Side (Viewing from back)
int dcm_pin1 = 3;
int dcm_pin2 = 4;
//Right Side
int dcm_pin3 = 5;
int dcm_pin4 = 6;

//Defining pins for input signals from receiver
int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;

//Defining the input signals from receiver
int data1;
int data2;
int data3;
int data4;

//driver code
void setup() {
  //The input pins should ben defined as input
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);

  //The output pins for DC motors
  pinMode(dcm_pin1, OUTPUT);
  pinMode(dcm_pin2, OUTPUT);
  pinMode(dcm_pin3, OUTPUT);
  pinMode(dcm_pin4, OUTPUT);

  //also stop all DC motors
  digitalWrite(dcm_pin1, LOW);
  digitalWrite(dcm_pin2, LOW);
  digitalWrite(dcm_pin3, LOW);
  digitalWrite(dcm_pin4, LOW);

  Serial.begin(9600);
}

void loop() {
  //reading the received signal as input
  data1 = digitalRead(in1);
  data2 = digitalRead(in2);
  data3 = digitalRead(in3);
  data4 = digitalRead(in4);
  
  //handling FWD/BKW no turning scenarios
  //Putting this first means that FWD/BKW is being prioritised first.
  
  //if only fwd/bwd
  if(data2 == 1 && data4 == 0){
    //if forward
    if(data1 == 0){
      //left side
      digitalWrite(dcm_pin1, HIGH);
      digitalWrite(dcm_pin2, LOW);

      //right side
      digitalWrite(dcm_pin3, HIGH);
      digitalWrite(dcm_pin4, LOW);
    }
    else if(data2 == 1){
      //left side
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, HIGH);

      //right side
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, HIGH);
    }
  }
  //if only left/right
  else if(data4 == 1 && data2 == 0){
    //if only left
    if(data3 == 0){
      //left side (backward)
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, HIGH);

      //right side (forward)
      digitalWrite(dcm_pin3, HIGH);
      digitalWrite(dcm_pin4, LOW);
    } 
    //if only right
    else if(data3 == 1){
      //left side (forward)
      digitalWrite(dcm_pin1, HIGH);
      digitalWrite(dcm_pin2, LOW);

      //right side (backward)
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, HIGH);
    }
  }
  //if a combination of left and right
  else if(data2 == 1 && data4 == 1){
    //forward and left
    if(data1 == 0 && data3 == 0){
      //left side (stop)
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, LOW);

      //right side (forward)
      digitalWrite(dcm_pin3, HIGH);
      digitalWrite(dcm_pin4, LOW);
    }
    //forward and right
    else if(data1 == 0 && data3 == 1){
      //left side (forward)
      digitalWrite(dcm_pin1, HIGH);
      digitalWrite(dcm_pin2, LOW);

      //right side (stop)
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, LOW);
    }
    //backward and left
    else if(data2 == 1 && data4 == 0){
      //left side (stop)
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, LOW);

      //right side (backward)
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, HIGH);
    }
    //backward and right
    else if(data2 == 1 && data4 == 1){
      //left side (backward)
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, HIGH);

      //right side (stop)
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, LOW);
    }
  }
  else{
       //left side (stop)
      digitalWrite(dcm_pin1, LOW);
      digitalWrite(dcm_pin2, LOW);

      //right side (stop)
      digitalWrite(dcm_pin3, LOW);
      digitalWrite(dcm_pin4, LOW);
  }

  //printing the received values
  Serial.print(data4);
  Serial.print(data3);
  Serial.print(data2);
  Serial.println(data1);
}
