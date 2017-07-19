/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

// Include DHT Sensor Library
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int mode = 0;

// set up the 'counter' feed
AdafruitIO_Feed *snowflake = io.feed("snowflake");
AdafruitIO_Feed *snowflake_temp = io.feed("snowflake_temp");
AdafruitIO_Feed *snowflake_tempC = io.feed("snowflake_tempC");
AdafruitIO_Feed *snowflake_humidity = io.feed("snowflake_humidity");
AdafruitIO_Feed *snowflake_heatIndex = io.feed("snowflake_heatIndex");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("\n\nConnecting to Adafruit IO");
  dht.begin();
  Serial.println("Beginning to monitor temperature");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the command feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  snowflake->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

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
  switch (mode) {
    case 0:
      Serial.println("Sending Temp (F) update");
      snowflake_temp->save(f);
      mode = 1;
      break;
    case 1:
      Serial.println("Sending Temp (C) update");
      snowflake_tempC->save(c);
      mode = 2;
      break;
    case 2:
      Serial.println("Sending Humidity update");
      snowflake_humidity->save(h);
      mode = 3;
      break;
    case 3:
      Serial.println("Sending Heat Index update");
      snowflake_heatIndex->save(hif);
      mode = 0;
      break;
    default:
      Serial.println("Default case caught, no update made!");
    break;
  }
  

  // wait one second (1000 milliseconds == 1 second)
  delay(2000);

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
