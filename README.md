# Biometric-Algorithm-for-Heart-Rate-and-Blood-Pressure-Monitoring
Biometric Algorithm for Heart Rate and Blood Pressure Monitoring Using a Microcontroller

# Project Overview:
This project involved designing and implementing a compact and efficient biometric monitoring system to measure Heart Rate (HR) and estimate Blood Pressure (BP) in real-time. The system utilized a microcontroller, integrated sensor modules, and custom signal processing algorithms to provide accurate and reliable biometric measurements.

# Key Features:
Sensor Integration:

- Optical Heart Rate sensors (PPG sensors) were used for pulse wave acquisition.
- Blood Pressure estimation relied on pulse transit time (PTT) derived from ECG and PPG signals.

# Data Processing:

- The microcontroller processed raw data using digital filters (Like moving average and Butterworth) to eliminate noise and artifacts.
- Signal peaks were detected using custom algorithms to calculate HR and measure time intervals for BP estimation.

# Algorithm Development:

- Heart Rate was calculated by detecting the intervals between PPG signal peaks (R-R intervals).
- Blood Pressure was estimated using a machine learning model trained on PTT and demographic data, deployed on the microcontroller.

# User Interface:
- Real-time results were displayed on an OLED screen to a mobile application for remote monitoring.

# Power Efficiency:
- Optimized firmware ensured low-power operation for prolonged use in wearable applications.

# Technologies and Tools Used:
- Hardware: Microcontroller (Arduino), PPG sensor (MAX30102), ECG module (AD8232), and Bluetooth module.
- Software: Embedded C/C++, Python for model training, and libraries for signal processing.
- Algorithms: Signal filtering, peak detection, and machine learning for BP estimation.

# Achievements:
- Successfully measured HR with an accuracy of 95% compared to standard medical devices.
-  Developed a BP estimation algorithm achieving a mean absolute error (MAE) of ±5 mmHg for systolic and diastolic readings.
- Created a low-cost, portable solution with potential applications in wearable health monitoring
