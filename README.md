# 🚗 Uber Clone (C++)

A console-based Uber-like ride booking system built using **C++**, **Object-Oriented Programming (OOP)**, and **basic Low-Level Design (LLD)** concepts.

This project simulates real-world ride booking flow including rider and driver management, ride lifecycle, fare calculation, payment, and rating system.

---

## 🔥 Features

### 👤 Rider Features
- Register and Login
- Book Ride (enter pickup, drop, distance)
- View Fare Estimate
- Cancel Ride
- View Ride History
- Rate Driver

### 🚗 Driver Features
- Register and Login
- Add Vehicle Details
- Set Online / Offline Status
- Accept / Reject Ride
- Start and Complete Ride
- View Earnings
- View Completed Rides
- Rate Rider

---

## ⚙️ Ride Management
- Auto driver assignment
- Ride lifecycle tracking:
  - Requested
  - Accepted
  - Started
  - Completed
  - Cancelled
- Active ride tracking
- Ride history support

---

## 💳 Payment System
- Payment creation after ride completion
- Cash / Online payment option
- Payment status tracking

---

## ⭐ Rating System
- Rider can rate driver
- Driver can rate rider
- Duplicate rating prevention
- Rating validation (1–5)

---

## 🧠 Concepts Used

- Object-Oriented Programming (OOP)
  - Encapsulation
  - Inheritance
  - Polymorphism
  - Abstraction
- STL
  - vector
  - unordered_map
- Exception Handling
- Enums for state management
- Modular design (Models + Services + Utils)

---

## 📂 Project Structure
UberClone/
│
├── main.cpp
├── enums/
├── exceptions/
├── models/
├── services/
└── utils/


---


---

## ▶️ How to Run

### 1. Open project folder

```bash
cd UberClone
2. Compile
g++ main.cpp utils/IdGenerator.cpp -I. -o uber_clone
3. Run
.\uber_clone

🔄 Project Flow
User registers as Rider or Driver
Driver adds vehicle and goes online
Rider books a ride
System assigns available driver
Driver accepts and starts ride
Ride completes
Payment is processed
Rider and driver give ratings
💪 Strengths
Clean modular structure
Proper use of OOP concepts
Beginner-friendly Low-Level Design
Easy to understand and extend
Good for interview discussion
⚠️ Limitations
No database (data stored in memory)
No real GPS/location tracking
No real payment gateway
No nearest driver matching logic
Data is lost after program ends
🚀 Future Improvements
Add database (MongoDB / MySQL)
Implement real driver matching logic
Add GUI or web version (MERN)
Improve fare calculation
Add authentication security
Add admin panel
🛠️ Tech Stack
Language: C++
Concepts: OOP, STL, LLD
Type: Console-based application

👨‍💻 Author
Ramgopal Katare


