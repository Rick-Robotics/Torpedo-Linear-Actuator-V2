
//Torpedo BTS7960 motor driver sketch


 // Rotary Encoder Inputs
 #define inputCLK 2
 #define inputDT 3
  
 int counter = 0; 
 int currentStateCLK;
 int previousStateCLK; 
 
 String encdir ="";
 
//    BTS7960 motor driver

//int L_IS = 3; // For reading current from Motor Driver
//int R_IS = 4; // For reading current from Motor Driver

int R_PWM = 5; 
int L_PWM = 6;   
int L_EN = 9;  
int R_EN = 10;   


const int buttonIn = 11;     // End_Stop for Retract
const int buttonOut = 12;     // End_Stop for Extend

int potpin = A0;  // analog pin used to connect the potentiometer

// Splits the Pot Range into Forward and Reverse. Threshold is the Center.
const int threshold = 0;   // an arbitrary threshold level that's in the range of the analog input


// variables:
int buttonInState = 0;         // variable for reading the pushbutton status
int buttonOutState = 0;         // variable for reading the pushbutton status

int val;    // variable to read the value from the analog pin


void setup() {
 // Encoder Setup
 // Set encoder pins as inputs  
 pinMode (inputCLK,INPUT);
 pinMode (inputDT,INPUT);
 
 // Read the initial state of inputCLK
 // Assign to previousStateCLK variable
 previousStateCLK = digitalRead(inputCLK);

  // Driver Setup
 pinMode(R_EN, OUTPUT);
 pinMode(R_PWM, OUTPUT); 
 pinMode(L_EN, OUTPUT);
 pinMode(L_PWM, OUTPUT);
 digitalWrite(R_EN, HIGH);
 digitalWrite(L_EN, HIGH);

  // initialize the pushbutton pin as an input:
  pinMode(buttonIn, INPUT);
  pinMode(buttonOut, INPUT);

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
 {
 
    //  Pot Reading
    val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, -255, 255);     // scale it for use with the PWM (value between 0 and 255)
  
   // Button Reading
  // read the state of the End_Stop button value:
    buttonInState = digitalRead(buttonIn);
    buttonOutState = digitalRead(buttonOut);

  
  // Read the current state of inputCLK
   currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) { 
       counter --;
       encdir ="CCW";
      
     } else {
       // Encoder is rotating clockwise
       counter ++;
       encdir ="CW";
    }
     Serial.print("Direction: ");
     Serial.print(encdir);
     Serial.print(" -- Value: ");
     Serial.println(counter);
   } 
   // Update previousStateCLK with the current state
   previousStateCLK = currentStateCLK;    
 }
 

  if (val > threshold) {  

    if (buttonInState == LOW) {
      analogWrite(R_PWM, val);
      analogWrite(L_PWM, 0);
  } else {
      analogWrite(R_PWM, 0);
      analogWrite(L_PWM, 0);
    
  }
  } else {
    if (buttonOutState == LOW) {
      analogWrite(R_PWM, 0);
      analogWrite(L_PWM, -val); 
 } else {
      analogWrite(R_PWM, 0);
      analogWrite(L_PWM, 0);       
  }

  }
// print the speed value results to the Serial Monitor:
//  Serial.print("val = ");
//  Serial.println(val);
 delay(10);        // delay in between reads for stability

}
