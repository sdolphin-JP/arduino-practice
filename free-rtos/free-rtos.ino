#include <Arduino_FreeRTOS.h>

void TaskBlink(void* pvParameters)
{
  (void)pvParameters;

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);        // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
    digitalWrite(LED_BUILTIN, LOW);         // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
  }
}

void setup()
{
  Serial.begin(9600);

  xTaskCreate(
    TaskBlink
    , "Blink"   // A name just for humans
    , 128       // This stack size can be checked & adjusted by reading the Stack Highwater
    , NULL
    , 2         // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    , NULL);
}

void loop()
{
  // Empty. Things are done in Tasks.
}
