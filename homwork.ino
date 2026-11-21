// --- Pin Definitions (Matches your wiring diagram) ---
const int BTN_PIN = 2;
const int R_PIN = 11; // Green wire -> D11
const int G_PIN = 9;  // Blue wire -> D9
const int B_PIN = 10; // Red wire -> D10

// Modes: 0=Constant, 1=Blink, 2=Breathe, 3=Rainbow, 4=Heartbeat (Double-click)
int mode = 0, prevMode = 0, colorIdx = 0;
const int colors[5][3] = {{255,0,0}, {0,255,0}, {0,0,255}, {255,255,0}, {180,0,255}};

// Button timing & states (Active HIGH for button module)
int lastBtn = LOW, btnState = LOW;
unsigned long debounceTime = 0, pressTime = 0, releaseTime = 0, animTime = 0;
bool longPressed = false, waitSecondClick = false;
int step = 0;

void setup() {
  pinMode(BTN_PIN, INPUT); // Changed from INPUT_PULLUP to INPUT
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  handleButton();
  updateLED();
}

void handleButton() {
  unsigned long now = millis();
  int reading = digitalRead(BTN_PIN);
  if (reading != lastBtn) debounceTime = now;

  if (now - debounceTime > 30 && reading != btnState) {
    btnState = reading;
    if (btnState == HIGH) { // Pressed = HIGH
      pressTime = now;
      longPressed = false;
    } else if (!longPressed) { // Released = LOW
      if (waitSecondClick && now - releaseTime <= 350) {
        waitSecondClick = false;
        if (mode != 4) { prevMode = mode; mode = 4; } else mode = prevMode;
        step = 0;
      } else {
        waitSecondClick = true;
        releaseTime = now;
      }
    }
  }

  // Single short click: change color
  if (waitSecondClick && now - releaseTime > 350) {
    waitSecondClick = false;
    colorIdx = (colorIdx + 1) % 5;
  }

  // Long press (800ms): cycle modes 0 -> 1 -> 2 -> 3 -> 0
  if (btnState == HIGH && !longPressed && now - pressTime >= 800) {
    longPressed = true;
    waitSecondClick = false;
    mode = ((mode == 4 ? prevMode : mode) + 1) % 4;
    step = 0;
  }
  lastBtn = reading;
}

void updateLED() {
  unsigned long now = millis();
  int r = colors[colorIdx][0], g = colors[colorIdx][1], b = colors[colorIdx][2];

  if (mode == 0) { // Constant
    setColor(r, g, b);
  } 
  else if (mode == 1) { // Blink (300ms)
    if (now - animTime >= 300) { animTime = now; step = !step; }
    setColor(step ? r : 0, step ? g : 0, step ? b : 0);
  } 
  else if (mode == 2) { // Breathing
    if (now - animTime >= 20) { animTime = now; step = (step + 5) % 510; }
    int bright = step <= 255 ? step : 510 - step;
    setColor((r * bright) / 255, (g * bright) / 255, (b * bright) / 255);
  } 
  else if (mode == 3) { // Rainbow
    if (now - animTime >= 15) { animTime = now; step = (step + 3) % 768; }
    int x = step % 256;
    if (step < 256) setColor(255 - x, x, 0);
    else if (step < 512) setColor(0, 255 - x, x);
    else setColor(x, 0, 255 - x);
  } 
  else if (mode == 4) { // Heartbeat (Double-click)
    const int d[4] = {120, 80, 120, 680};
    if (now - animTime >= d[step]) { animTime = now; step = (step + 1) % 4; }
    bool on = (step == 0 || step == 2);
    setColor(on ? r : 0, on ? g : 0, on ? b : 0);
  }
}

void setColor(int r, int g, int b) {
  // Inverted for Common Anode RGB module (connected to 3.3V)
  analogWrite(R_PIN, 255 - r);
  analogWrite(G_PIN, 255 - g);
  analogWrite(B_PIN, 255 - b);
}