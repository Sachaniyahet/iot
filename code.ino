#include <DHT.h>

#define DHTPIN 7        // Pin where the DHT11 sensor is connected
#define DHTTYPE DHT11   // DHT 11 sensor

#define IN1 11          // Motor driver IN1 pin
#define IN2 10          // Motor driver IN2 pin
#define ENA 9           // Motor driver ENA pin (PWM pin for speed control)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial monitor
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Ensure motor is initially off
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void loop() {
  // Read temperature from the DHT11 sensor
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }

  // Print temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  int motorSpeed = 0;  // Variable to store the motor speed (PWM value)

  // Control fan speed based on temperature
  if (temperature < 30) {
    // Low temperature, slow fan speed
    motorSpeed = 100;  // PWM value (0-255)
    analogWrite(ENA, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } 
  else if (temperature >= 30 && temperature <= 35) {
    // Moderate temperature, medium fan speed
    motorSpeed = 150;  // PWM value (0-255)
    analogWrite(ENA, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } 
  else {
    // High temperature, fast fan speed
    motorSpeed = 255;  // PWM value (0-255)
    analogWrite(ENA, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  // Display motor speed on the serial monitor
  Serial.print("Motor Speed (PWM): ");
  Serial.println(motorSpeed);

  // Wait for a while before taking the next reading
  delay(2000);  // 2 seconds delay
}
