
/*
 * moisture_sensor.ino
 */

 #include <math.h>

#define MOISTURE_SENSOR A0
#define DRY_VALUE 570
#define WET_VALUE 300

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6

int leds[] = {LED1, LED2, LED3, LED4, LED5};
int numLeds = sizeof(leds) / sizeof(int);


void initLedArray(){
  for( int i = 0; i < numLeds; i++){
    pinMode( leds[i], OUTPUT );
    Serial.println( leds[i], DEC );
  }
}

void setLedArray( int val ){
  for( int i = 0; i < numLeds; i++ ){
    if( i <= val ){
      digitalWrite( leds[i], HIGH );
    }else{
      digitalWrite( leds[i], LOW );
    }
  }
}

/*
 * Converts an analog reading into a integer value (for use in a led scale, for instance)
 *
 * It will apply the formula: 
 *       /                                                           \
 *       |              /    (reading - lowValue)                   \|
 * round |outputRange - | -------------------------- * outputRange  ||
 *       |              \    (DRY_VALUE - lowValue)                 /|
 *       \                                                           /
 *
 *
 */
int convertMoistureReading( int reading, int outputRange ){

  return round( outputRange - ( (reading - WET_VALUE ) / (DRY_VALUE - WET_VALUE) ) * outputRange );

}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  initLedArray();
}

void loop() {
  int moistureReading = analogRead(MOISTURE_SENSOR);
  
  // Print the value to the serial monitor
  Serial.print("Analog output: ");
  Serial.println(moistureReading, DEC);

  digitalWrite(LED_BUILTIN, HIGH);
  setLedArray( convertMoistureReading( moistureReading, numLeds ) );
  delay(1500);
  setLedArray( -1 );
  delay(1500);
  Serial.println("continuamos");
}
