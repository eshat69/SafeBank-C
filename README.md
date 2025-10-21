# 🏦 SafeBank-C  
**A Console-Based Bank Management System built in C**

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/Status-Active-success.svg)]()
[![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)]()
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue.svg)]()

---

### 💡 **Overview**
**SafeBank-C** is a lightweight **Bank Management System** implemented in the C programming language.  
It allows users to create accounts, deposit and withdraw money, check balances, delete accounts, and view transaction histories — all through a console interface using file-based data storage.

---

### ⚙️ **Features**
- 🧾 Create, delete, and list user accounts  
- 💰 Deposit and withdraw money securely  
- 📊 Check account balance instantly  
- 🕒 Maintain detailed transaction logs with timestamps  
- 💾 Data stored persistently using binary files  

---

### 🧱 **Tech Stack**
- **Language:** C  
- **Libraries:** `stdio.h`, `string.h`, `time.h`, `stdlib.h`  
- **Storage:** Binary file handling (`.dat` and `.txt` files)  

---
### **📘 Project Structure**
SafeBank-C/
│
├── bank.c              # Main source code
├── account.dat         # Stores account data (auto-generated)
├── transaction.txt     # Stores transaction logs (auto-generated)
└── README.md           # Project documentation
---
### 🚀 **How to Run**
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/SafeBank-C.git
   cd SafeBank-C
