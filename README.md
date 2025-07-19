# 🛒 Inventory Management System (C++)

A terminal-based inventory management system developed in C++ using Object-Oriented Programming (OOP), STL containers, and binary file I/O. The system helps manage stock items, update quantities, generate reports, and persist data between sessions.

---

## 🔧 Tech Stack

- ✅ C++11
- ✅ Classes & Objects
- ✅ STL vector, map
- ✅ File I/O (binary mode)
- ✅ CLI (Command-Line Interface)

---

## 💡 Features

- 🔐 Admin login authentication
- ➕ Add new products with ID, name, category, supplier, price, and quantity
- 📄 View all inventory items in a formatted table
- 🔁 Update stock quantities for any product
- ❌ Delete products from inventory
- ⚠ Low stock alerts (configurable threshold)
- 📊 Generate inventory value & category-based summary reports
- 💾 Data persistence using binary file storage (inventory.dat)

---

## 🚀 Getting Started

### 🛠 Compile
```bash
g++ -o inventory main.cpp
