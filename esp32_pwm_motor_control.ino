const int motorPin = 12;   // MOSFET Gate pinine bağlı
const int freq = 5000;     // 5 kHz frekans
const int resolution = 8;  // 8 bit (0-255 arası)

void setup() {
  Serial.begin(115200);
  
  // Yeni versiyonda sadece bu fonksiyon yeterli:
  // ledcAttach(pin, frekans, çözünürlük);
  ledcAttach(motorPin, freq, resolution);
  
  Serial.println("--- ESP32 (V3) Motor Test Sistemi ---");
  Serial.println("Hiz seviyesi girin (1-5 arasi, Durdurmak icin 0):");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    // Sadece rakam girilip girilmediğini kontrol et
    if (input >= '0' && input <= '5') {
      int level = input - '0';
      int pwmValue = 0;

      switch (level) {
        case 0: pwmValue = 0;   break;
        case 1: pwmValue = 50;  break;
        case 2: pwmValue = 100; break;
        case 3: pwmValue = 150; break;
        case 4: pwmValue = 200; break;
        case 5: pwmValue = 255; break;
      }

      // Yeni versiyonda kanal yerine doğrudan pini yazıyoruz
      ledcWrite(motorPin, pwmValue);
      
      Serial.print("Secilen Seviye: ");
      Serial.print(level);
      Serial.print(" -> PWM Degeri: ");
      Serial.println(pwmValue);
    }
  }
}