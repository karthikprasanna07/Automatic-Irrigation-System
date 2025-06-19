🌱 Automatic Irrigation System (Arduino-based)

This project is a simulation of a smart irrigation system that automatically "waters" plants based on soil moisture levels. Due to limited time and resources, the motor was replaced with an LED to visually represent when the system would activate irrigation.

💡 Project Overview

The system uses a soil moisture sensor to measure the dryness of the soil. When the moisture level falls below a predefined threshold, the Arduino triggers an LED to indicate that irrigation would normally start (in place of an actual water pump).

🔧 Components Used

- Arduino Uno
- Soil Moisture Sensor
- LED (used to simulate motor)
- Jumper Wires
- Breadboard

⚙️ Working Principle

- The soil moisture sensor constantly checks the soil's moisture level.
- If the value drops below the threshold (indicating dry soil), the LED turns ON (simulating pump activation).
- If the soil is sufficiently moist, the LED remains OFF.

📋 Circuit Summary

- Moisture sensor → Analog pin of Arduino
- LED connected to Digital pin (e.g., pin 13)
- Threshold value set in the code to decide activation


