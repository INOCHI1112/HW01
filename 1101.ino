const int button = 2;
const int R = 3;
const int G = 4;
const int B = 5;

int color = 0;
bool pressed = false;
unsigned long pressStartTime = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  int state = digitalRead(button);

  // ⭐按鈕剛被按下
  if (state == LOW && !pressed) {
    pressed = true;
    pressStartTime = millis();  // 記錄按下時間

    // 短按時先跳一次
    color++;
    if (color > 6) color = 0;
    setColor(color);

    delay(20); // 簡易去彈跳
  }

  // ⭐維持長按 → 快速跳色
  if (state == LOW && pressed) {
    if (millis() - pressStartTime >= 1500) { // 長按1.5秒
      color++;
      if (color > 6) color = 0;
      setColor(color);
      delay(200); // 快速切色速度
    }
  }

  // ⭐放開按鈕 → 結束長按模式
  if (state == HIGH) {
    pressed = false;
  }
}


// 🎨 設定顏色
void setColor(int c) {
  switch (c) {
    case 0: digitalWrite(R, LOW); digitalWrite(G, LOW); digitalWrite(B, LOW); break; // White
    case 1: digitalWrite(R, LOW); digitalWrite(G, HIGH); digitalWrite(B, HIGH); break; // Red
    case 2: digitalWrite(R, HIGH); digitalWrite(G, LOW); digitalWrite(B, HIGH); break; // Green
    case 3: digitalWrite(R, HIGH); digitalWrite(G, HIGH); digitalWrite(B, LOW); break; // Blue
    case 4: digitalWrite(R, LOW); digitalWrite(G, LOW); digitalWrite(B, HIGH); break; // Yellow
    case 5: digitalWrite(R, LOW); digitalWrite(G, HIGH); digitalWrite(B, LOW); break; // Purple
    case 6: digitalWrite(R, HIGH); digitalWrite(G, LOW); digitalWrite(B, LOW); break; // Cyan
  }
}