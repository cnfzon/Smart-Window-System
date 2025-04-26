#  Smart Window System | Windows Keeper

A smart air-quality-aware window control system built with **ESP32**, **Arduino UNO**, and various **gas sensors**.  
It can automatically decide whether to open or close the window based on environmental conditions, and **notify the user via LINE Notify**.

---

##  Features
- Automatically detects **rain**, **indoor/outdoor air quality**, and **window state**
- Sends real-time reports through **LINE Notify**
- Controls **exhaust fans**, **air purifiers**, and **window motors**
- Uses **multi-device communication** (ESP32 → Arduino UNO)

---

##  Hardware Used

| Component      | Purpose |
|----------------|---------|
| ESP32          | Gas sensing & wireless communication    |
| Arduino UNO x2 | Window & motor control logic            |
| MQ-135         | Detects harmful gases (e.g. CO2, NH3)   |
| MQ-7           | Detects CO (carbon monoxide)            |
| FC-37          | Rain detection sensor                   |
| L298N Module   | Motor driver                            |
| GA12-N20       | Gear motor (for window opening/closing) |

---

##  System Flow (簡易邏輯)
1. ESP32 偵測氣體 → 傳送給主板（UNO）
2. 主板決定是否開窗／開啟抽風機／清淨機
3. 把狀態＋偵測結果傳送到 **LINE Notify**

---

##  LINE Notify Demo
