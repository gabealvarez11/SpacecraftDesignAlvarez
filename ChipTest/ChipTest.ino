// Starter code for each module copied from Xinabox Arduino library examples.

#include <xCore.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xSL01.h>
#include <xSW01.h>

xSI01 SI01;
xSN01 SN01;
xSL01 SL01;
xSW01 SW01;

const int DELAY_TIME = 5000;

void setup() {
  // Start the Serial Monitor at 115200 BAUD
  Serial.begin(115200);
  
  // Set the I2C Pins for CW01
  #ifdef ESP8266
    Wire.pins(2, 14);
    Wire.setClockStretchLimit(15000);
  #endif

  Wire.begin();
  SI01.begin();
  SN01.begin();
  SL01.begin();
  SW01.begin();

  // Delay for Sensor to normalise
  delay(DELAY_TIME);
  
  SI01.poll();
  SN01.poll();
  SL01.poll();
  SW01.poll();

  
}

void loop(){
// Delay for Sensor to normalise
  delay(DELAY_TIME/10);

  SI01.poll();

  printGyro();  // Print "G: gx, gy, gz"
  printAccel(); // Print "A: ax, ay, az"
  printMag();   // Print "M: mx, my, mz"
  printAttitude(); // Print Roll, Pitch and G-Force

  String time;
  long latitude = 0;
  long longitude = 0;
  String date;
  
  // Poll the sensor to read all available data
  SN01.poll();

  // Get the date from GPS
  date = SN01.getDate();
  
  // Get the time from the GPS 
  time = SN01.getTime();

  // Get the latitude from GPS
  latitude = SN01.getLatitude();

  // Get the longitude from GPS
  longitude = SN01.getLongitude();
  
  // Display the recorded data over the serial monitor
  Serial.print("GPS Time: ");
  Serial.println(time);
  Serial.print("GPS Date: ");
  Serial.println(date);
  Serial.print("GPS Latitude: ");
  Serial.println(latitude);
  Serial.print("GPS longitude: ");
  Serial.println(longitude);

  // Create a variable to store the incoming measurements
  // from SL01 sensor
  float lux;
  lux = 0;
  float uv;
  uv = 0;
  // Poll Sensor for collect data
  SL01.poll();

  // Request SL01 to return calculated UVB intensity
  lux = SL01.getLUX();
  // Display Data on the Serial monitor
  Serial.print("Ambient Light Level: ");
  Serial.print(lux);
  Serial.println(" LUX");
  //Request SL01 to return calculated UVB intensity
  uv = SL01.getUVA();
  // Display Data on the Serial monitor
  Serial.print("UVA Intersity: ");
  Serial.print(uv);
  Serial.println(" uW/m^2");
  
  // Request SL01 to return calculated UVB intensity
  uv = SL01.getUVB();
  // Display Data on the Serial monitor
  Serial.print("UVB Intensity: ");
  Serial.print(uv);
  Serial.println(" uW/m^2");

  // Request SL01 to return calculated UVB intensity
  uv = SL01.getUVIndex();
  // Display Data on the Serial monitor
  Serial.print("UVB Index: ");
  Serial.println(uv);

  // Create a variable to store the data read from SW01  
  float tempC;
  float tempF;
  tempC = tempF = 0;
  
  // Read and calculate data from SW01 sensor
  SW01.poll();
  
  // Request SW01 to get the temperature measurement and store in
  // the temperature variable   
  tempC = SW01.getTempC(); // Temperature in Celcuis
  tempF = SW01.getTempF(); // Temperature in Farenheit
  
  // Display the recoreded data over the Serial Monitor   
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" F"); 
  
  // Create a variable to store the data read from SW01
  float alt;
  alt = 0;
  
//  // Request SW01 to get the altitude measurement and store in
//  // the altitude variable  
//  alt = SW01.getAltitude(101325);
//  
//  // Display the recoreded data over the Serial Monitor 
//  Serial.print("Altitude: ");
//  Serial.print(alt);
//  Serial.println(" m");

  // Create a variable to store the data read from SW01
  float humidity;
  humidity = 0;
  
  // Request SW01 to get the humidity measurement and store in
  // the humidity variable  
  humidity = SW01.getHumidity();
  
  // Display the recoreded data over the Serial Monitor 
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

//  // Create a variable to store the data read from SW01
//  float pressure;
//  pressure = 0;
//  
//  // Request SW01 to get the pressure measurement and store in
//  // the pressure variable    
//  pressure = SW01.getPressure();
//  
//  // Display the recoreded data over the Serial Monitor 
//  Serial.print("Pressure: ");
//  Serial.print(pressure);
//  Serial.println(" Pa");
}

void printGyro(void) {
  Serial.print("G: ");
  Serial.print(SI01.getGX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getGY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getGZ(), 2);

}

void printAccel(void) {
  Serial.print("A: ");
  Serial.print(SI01.getAX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getAY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getAZ(), 2);
}

void printMag(void) {
  Serial.print("M: ");
  Serial.print(SI01.getMX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getMY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getMZ(), 2);

}

void printAttitude(void) {
  Serial.print("Roll: ");
  Serial.println(SI01.getRoll(), 2);
  Serial.print("Pitch :");
  Serial.println(SI01.getPitch(), 2);
  Serial.print("GForce :");
  Serial.println(SI01.getGForce(), 2);
}
