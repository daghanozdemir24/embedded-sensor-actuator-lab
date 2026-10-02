// 1. ADIM: Pinleri Tanımlıyoruz
const int trigPin = 9;   // Sensörün "Bağır" (Trig) ucu Pin 9'da
const int echoPin = 10;  // Sensörün "Dinle" (Echo) ucu Pin 10'da
const int ledPin = 13;   // LED ve Direnç Pin 13'te

// Hesaplamalar için kutular (değişkenler) hazırlıyoruz
long duration; // Sesin gidip gelme süresi için
int distance; // Santimetre cinsinden mesafe için

void setup() {
  // 2. ADIM: Giriş ve Çıkış Kapılarını Ayarlıyoruz
  pinMode(trigPin, OUTPUT); // Ses göndereceğimiz için çıkış
  pinMode(echoPin, INPUT);  // Yankıyı duyacağımız için giriş
  pinMode(ledPin, OUTPUT);   // Işık yakacağımız için çıkış

  // Leonardo bilgisayarla konuşabilsin diye seri iletişimi başlatıyoruz
  Serial.begin(9600);
  
  // Leonardo'nun bağlantısının tam oturmasını bekliyoruz
  while (!Serial) {
    ; 
  }
  Serial.println("Sistem Hazir! Engel kontrolü basliyor...");
}

void loop() {
  // 3. ADIM: Ses Dalgası Gönderiyoruz
  digitalWrite(trigPin, LOW); // Önce bir temizlik yap, sus
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // 10 mikrosaniye boyunca bağır
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // Tekrar sus

  // 4. ADIM: Yankıyı Bekle ve Süreyi Ölç
  duration = pulseIn(echoPin, HIGH);

  // 5. ADIM: Süreyi Santimetreye Çevir (Matematik Kısmı)
  distance = duration * 0.034 / 2;

  // 6. ADIM: Mesafeyi Bilgisayar Ekranına Yazdır
  Serial.print("Engel Mesafesi: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 7. ADIM: KARAR MEKANİZMASI (Drone Engel Algılama Mantığı)
  if (distance > 0 && distance < 50) { 
    // Eğer 50 cm'den yakın bir şey varsa uyar!
    
    digitalWrite(ledPin, HIGH); // Işığı yak
    
    /* Buradaki delay, mesafe azaldıkça kısalır. 
       Mesafe 10cm ise 50ms bekler (çok hızlı çakar).
       Mesafe 40cm ise 200ms bekler (yavaş çakar). */
    delay(distance * 5); 
    
    digitalWrite(ledPin, LOW); // Işığı söndür
    delay(distance * 5); 
  } 
  else {
    // Mesafe 50 cm'den uzaksa veya engel yoksa ışığı kapalı tut
    digitalWrite(ledPin, LOW);
  }

  // Sistemi çok yormamak için kısa bir ara ver
  delay(50);
}