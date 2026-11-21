int mode = 0, lastBtn = LOW;
unsigned long t = 0;
bool on = false;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int btn = digitalRead(2);
  if (btn == HIGH && lastBtn == LOW) {
    mode = (mode + 1) % 4;
    on = false;
    t = millis();
    delay(30);
  }
  lastBtn = btn;

  int d[] = {0, 1000, 400, 120};
  if (mode > 0 && millis() - t >= d[mode]) { t = millis(); on = !on; }
  digitalWrite(3, mode == 0 ? LOW : on);
}