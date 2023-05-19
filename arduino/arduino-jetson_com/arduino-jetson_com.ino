void setup() {
  Serial1.begin(9600);  // UART1 communication with Jetson Nano
  Serial.begin(9600);   // Serial monitor for debugging
}

void loop() {
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(data);
    
    // Echo back the received data
    Serial1.print(data);
  }
  
  // Send data from Arduino to Jetson Nano
  Serial1.println("Hello from Arduino!");
  
  delay(1000);
}