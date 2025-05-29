# Room Capacity Counter using Arduino Uno

This project is an automatic room occupancy monitor built with Arduino Uno. It uses two ultrasonic sensors (HC-SR04) to track people entering and exiting a room. The current number of occupants is displayed on a Nokia 5110 LCD. Red and green LEDs indicate entry and exit availability. When the maximum capacity is reached, entry is blocked.

---

## ⚙️ Features

- Real-time counting of people entering and exiting.
- LCD displays current room occupancy.
- LEDs signal allowed or blocked entry/exit.
- Max occupancy limit (default: 5 people).

---

## 📦 Components

| Component         | Description                        | Quantity |
|-------------------|------------------------------------|----------|
| Arduino Uno       | ATmega328P-based microcontroller   | 1        |
| HC-SR04           | Ultrasonic distance sensor         | 2        |
| Nokia 5110 LCD    | 84x48 pixel display (PCD8544)      | 1        |
| Red LED           | Entry/exit status indicator        | 2        |
| Green LED         | Entry/exit status indicator        | 2        |
| 1kΩ Resistor      | For LEDs                           | 4        |
| Breadboard        | Prototyping                        | 2        |
| Jumper wires      | Connections                        | -        |

---

## 🔌 Wiring Diagram

![Connection Diagram](Сonnection_diagram.png)

---

## 📈 Flowchart

```mermaid
---
config:
  theme: neo
  look: classic
---
flowchart TD
    A["Start"] --> B["Initialize LCD and serial"]
    B --> C["Set pin modes for sensors and LEDs"]
    C --> D["Loop Start"]
    D --> E["Turn ON entry and exit green LEDs"]
    E --> F{"Visitors count = 5?"}
    F -- Yes --> G["Block entry: turn ON red entry LED"]
    G --> H["Display: MAX 5 PERSON"]
    F -- No --> I["Allow entry: green ON, red OFF"]
    I --> J["Measure distance1 and distance2"]
    J --> K{"distance1 &lt; 10?"}
    K -- Yes --> L["Wait 1s, check distance2"]
    L --> M{"distance2 &lt; 10 AND visitor &lt; 5?"}
    M -- Yes --> N["visitor++ and display count"]
    M -- No --> Z["Do nothing"]
    K -- No --> O{"distance2 &lt; 10?"}
    O -- Yes --> P["Wait 1s, check distance1"]
    P --> Q{"distance1 &lt; 10 AND visitor &gt; 0?"}
    Q -- Yes --> R["visitor-- and display count"]
    Q -- No --> Z
    N --> S["Update LED states"]
    R --> S
    Z --> S
    S --> T["Display output"]
    T --> D
```

---

## 🚀 Getting Started

1. Connect all components following the wiring diagram.
2. Upload the `Room_Capacity_Counter.ino` code to your Arduino Uno using Arduino IDE.
3. Power the Arduino using USB or a 7–12V adapter.
4. LCD will show the current number of people in the room.
5. LEDs indicate entry (green/red) and exit (green/red) availability.

---

## 📝 Notes

- People must pass sensors sequentially to be counted correctly.
- Movement should be steady and within detection range.
- Adjust delays or distance threshold in code for sensitivity tuning.

---

## 📁 Files in this Repository

- `Room_Capacity_Counter.ino` – Arduino code for the project.
- `README.md` – This documentation with wiring, flowchart, and instructions.
- `Сonnection_diagram.png` – Visual schematic of the component connections.
