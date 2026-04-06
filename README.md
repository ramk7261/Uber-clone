# 🚗 Uber Clone (C++)

A console-based Uber-like ride booking system built using **C++**, **Object-Oriented Programming (OOP)**, and **basic Low-Level Design (LLD)** concepts.

This project simulates a real-world ride booking system including rider and driver management, ride lifecycle, fare calculation, payment handling, and rating system.

---

## 🔥 Features

### 👤 Rider Features
- Register and Login
- Book Ride (pickup, drop, distance)
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
- Automatic driver assignment
- Ride lifecycle tracking:
  - Requested
  - Accepted
  - Started
  - Completed
  - Cancelled
- Active ride tracking
- Ride history management

---

## 💳 Payment System
- Payment generated after ride completion
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
- STL (Standard Template Library)
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

## ▶️ How to Run

1. Open project folder

cd UberClone

2. Compile

g++ main.cpp utils/IdGenerator.cpp -I. -o uber_clone

3. Run

.\uber_clone

---

## 🔄 Project Flow

1. User registers as Rider or Driver  
2. Driver adds vehicle and goes online  
3. Rider books a ride  
4. System assigns an available driver  
5. Driver accepts and starts the ride  
6. Ride is completed  
7. Payment is processed  
8. Rider and driver give ratings  

---

## 💪 Strengths
- Clean and modular structure  
- Proper use of OOP concepts  
- Beginner-friendly Low-Level Design  
- Easy to understand and extend  
- Suitable for interviews  

---

## ⚠️ Limitations
- No database (data stored in memory)  
- No real GPS/location tracking  
- No real payment gateway  
- No nearest driver matching logic  
- Data is lost after program ends  

---

## 🚀 Future Improvements
- Add database (MongoDB / MySQL)  
- Implement real driver matching logic  
- Add GUI or web version (MERN)  
- Improve fare calculation  
- Add authentication security  
- Add admin panel  

---

## 🛠️ Tech Stack
- Language: C++  
- Concepts: OOP, STL, LLD  
- Type: Console-based application  

---

## 👨‍💻 Author
Ramgopal Katare
