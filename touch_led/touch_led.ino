#define LED_PIN          33
#define TOUCH_SENSOR_PIN 32

int lastState = LOW;
int currentState;

bool led_light = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  currentState = digitalRead(TOUCH_SENSOR_PIN);
  if (lastState == LOW && currentState == HIGH) {
    led_light = !led_light;
    digitalWrite(LED_PIN, led_light);
  }
  lastState = currentState;
}
