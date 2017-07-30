/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "IRCommands.h"


// Include DHT Sensor Library
#include "DHT.h"



#define DHTPIN 12
#define IRPin 15
#define DHTTYPE DHT11
#define LEDPin 13

DHT dht(DHTPIN,DHTTYPE);

IRsend irsend(15);
IRCommands ircom;

int updateMode = 0;

// set up the 'counter' feed
AdafruitIO_Feed *snowflake = io.feed("snowflake");
AdafruitIO_Feed *snowflake_temp = io.feed("snowflake_temp");
AdafruitIO_Feed *snowflake_tempC = io.feed("snowflake_tempC");
AdafruitIO_Feed *snowflake_humidity = io.feed("snowflake_humidity");
AdafruitIO_Feed *snowflake_heatIndex = io.feed("snowflake_heatIndex");

void setup() {

  int timeOutCount = 0;
  int timeOut = 60;
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  //while(! Serial);

  Serial.println("\n\nConnecting to Adafruit IO");
  dht.begin();
  Serial.println("Beginning to monitor temperature");
  irsend.begin();
  Serial.println("Beginning IRSend");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the command feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  snowflake->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    timeOutCount++;
    Serial.print(".");
    delay(500);
    if(timeOutCount >= timeOut) {
      Serial.println();
      Serial.print("Time out on connecting to AIO");
      return;
    }
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  pinMode(LEDPin, OUTPUT);

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  float f = dht.readTemperature(true);
  float c = dht.readTemperature();
  float h = dht.readHumidity();
  float hif = dht.computeHeatIndex(f, h);
  
  // Alternate sensor reading to update to stay below throttle limits:
  switch (updateMode) {
    case 0:
      Serial.println("Sending Temp (F) update");
      snowflake_temp->save(f);
      updateMode = 1;
      break;
    case 1:
      Serial.println("Sending Temp (C) update");
      snowflake_tempC->save(c);
      updateMode = 2;
      break;
    case 2:
      Serial.println("Sending Humidity update");
      snowflake_humidity->save(h);
      updateMode = 3;
      break;
    case 3:
      Serial.println("Sending Heat Index update");
      snowflake_heatIndex->save(hif);
      updateMode = 0;
      break;
    default:
      Serial.println("Default case caught, no update made!");
    break;
  }
  

  // wait one second (1000 milliseconds == 1 second)
  delay(2500);

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("DEBUG: Received data->value ");
  Serial.println(data->value());
  int command = data->toInt();
  /*
   * 0 = Power
   * 2 = Fan up
   * 3 = Fan down
   * 4 = Temp up
   * 5 = Temp down
   * 6 = Cool Mode
   * 7 = Fan Only
   * 8 = Energy Saver
   * 9 = Auto Fan
   * 10 = Sleep
   * 11 = Timer
   */

  switch (command) {
    case 0:
      Serial.println("Got Power Button");
      irsend.sendRaw(ircom.power, 68, 38);
      flashLED();
      break;
    case 2:
      Serial.println("Got fan up");
      irsend.sendRaw(ircom.fanUp, 68, 38);
      flashLED();
      break;
    case 3:
      Serial.println("Got fan down");
      irsend.sendRaw(ircom.fanDown, 68, 38);
      flashLED();
      break;
    case 4:
      Serial.println("Got temp up");
      irsend.sendRaw(ircom.tempUp, 68, 38);
      flashLED();
      break;
    case 5:
      Serial.println("Got temp down");
      irsend.sendRaw(ircom.tempDown, 68, 38);
      flashLED();
      break;
    case 6:
      Serial.println("Got cool mode");
      irsend.sendRaw(ircom.coolMode, 68, 38);
      flashLED();
      break;
    case 7:
      Serial.println("Got fan only mode");
      irsend.sendRaw(ircom.fanOnlyMode, 68, 38);
      flashLED();
      break;
    case 8:
      Serial.println("Got energy saver mode");
      irsend.sendRaw(ircom.energySaverMode, 68, 38);
      flashLED();
      break;
    case 9:
      Serial.println("Got Auto Fan Mode");
      irsend.sendRaw(ircom.autoFanMode, 68, 38);
      flashLED();
      break;
    case 10:
      Serial.println("Got sleep button press");
      irsend.sendRaw(ircom.sleepButton, 68, 38);
      flashLED();
      break;
    case 11:
      Serial.println("Got timer button press");
      irsend.sendRaw(ircom.timerButton, 68, 38);
      flashLED();
      break;
    default:
      Serial.print("Got unrecognized command: ");
      Serial.println(command);
    break;
  }

}

void flashLED() {
  digitalWrite(LEDPin, HIGH);
  delay(100);
  digitalWrite(LEDPin, LOW);
}

