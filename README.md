# arduino-color-sorting-conveyor
Arduino-based color sorting system using TCS3200 sensor, servo motors, and conveyor belt. Arduino color sorting conveyor project by The Arab Inventor.

# 🎨 Arduino Color Sorting Conveyor (TCS3200 + IR + L298N + Servos)

مشروع **المخترع العربي | The Arab Inventor**  
نظام فرز ألوان يعمل على سير ناقل (Conveyor Belt) باستخدام Arduino.  
يقرأ اللون بواسطة حساس **TCS3200**، ويتأكد من وجود القطعة بحساس **IR**، ثم يشغل السير عبر **L298N + DC Motor** ويقوم بالفرز بواسطة **2 Servo Motors** لمسارين (RED / BLUE). اللون الأبيض يمر بدون فرز (قابل للتعديل).

---

## ✅ Features
- Object detection using IR Sensor  
- RGB reading using TCS3200  
- Color classification: **RED / BLUE / WHITE**  
- Conveyor control using L298N (DC Motor)  
- Sorting gates using 2 Servo motors  
- Serial output for calibration

---

## 🧰 Components
- Arduino Uno (or compatible)
- TCS3200 Color Sensor
- IR Sensor
- L298N Motor Driver + DC Motor (Conveyor)
- 2x Servo motors
- External power for motor/servos (recommended) + common GND

---

## 🔌 Wiring (Pins)

### TCS3200
- S0 → D3  
- S1 → D4  
- S2 → D5  
- S3 → D6  
- OUT → D7  

### L298N + Motor
- ENA → D8 (PWM)  
- IN1 → D11  
- IN2 → D12  

### IR Sensor
- OUT → D2  
> In this code: **LOW = object detected** (change if your sensor is opposite).

### Servos
- Servo RED → D9  
- Servo BLUE → D10  

---

## ⚙️ How it works
1. IR sensor detects an object on the conveyor  
2. TCS3200 reads RGB values  
3. Arduino classifies the color  
4. Conveyor runs and the correct servo gate moves to sort the object

---

## 🧪 Calibration
RGB readings depend on lighting and distance.  
Open Serial Monitor at **9600** and observe:
