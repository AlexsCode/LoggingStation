  /* IR basic sensor- by alex tuddenham 2020 */
  
  const int ir_A0 =A0; //Assign IR sensor Analogue in to Arduino pin A0
  const int ir_D0 =8; // Assign IR sensor Digital in to Arduino pin 8
  
void setup() {
  
  pinMode (ir_A0 ,INPUT);
  pinMode (ir_D0 ,INPUT); //assigns as input pins (will read operations only)
  Serial.begin(9600);

}

float analog_read_value;
bool digital_read_value;

void loop() { //constantly runs
  analog_read_value = analogRead(ir_A0); //read analogue pin 
   digital_read_value =  digitalRead(ir_D0); //read digital pin

  Serial.print("Analogue Reading:");
  Serial.println(analog_read_value);
  Serial.print("Digital Reading:");
  Serial.println(digital_read_value);

  delay(1500);

  

}
