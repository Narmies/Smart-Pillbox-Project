graph TD
    subgraph "Smart Pillbox System"
    ESP32[ESP32 Microcontroller - Central Hub]
    RTC[DS3231 RTC Module - Time Keeper]
    QR[QR Code - Setup Interface]
    Web[Web Server - UI]
    Buzzer[Buzzer - Alarm]
    Solenoid[Solenoid Locks - Security]
    Switch[Limit Switches - Feedback]
    Power[12V/5V Power Supply]
    end

    QR --> Web
    Web <--> ESP32
    RTC --> ESP32
    ESP32 --> Buzzer
    ESP32 --> Solenoid
    Switch --> ESP32
    Power --> ESP32
    Power --> Solenoid# Smart-Pillbox-Project
