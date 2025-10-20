
<div align="center">

# 🏦 **Bank Management System**
### 💻 *C++ Console Application with File-Based Storage*

---

🎯 **Manage clients, users, and transactions directly from the console.**  
🔐 **Login system with permission control.**  
📁 **Data stored safely in simple `.txt` files.**

---

</div>

## ⚙️ Features Overview

### 👥 **User Management**
- ➕ Add new users  
- 📋 Show all users  
- 🔍 Search for a user  
- ✏️ Update user info  
- 🗑️ Delete users  
- 🧠 Assign **permissions** using bitwise flags  

---

### 💳 **Client Management**
- ➕ Add new clients  
- 📋 View all clients in a clean table  
- 🔍 Find client by account number  
- ✏️ Update client information  
- 🗑️ Delete client  
- 💾 All stored in `Clients.txt`

---

### 💰 **Transactions**
- 💵 Deposit money  
- 💸 Withdraw funds  
- 📊 View total balances across all clients  

---

## 🧩 **Permission Bits**

| 🧱 Action | 🔢 Value |
|-----------|----------|
| Show Clients | 1 |
| Add Client | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |
| Full Access | -1 |

> 💡 Example: Permission `35` = Show (1) + Add (2) + Find (16) + Transactions (32)

---

## 🗂️ **Data Files**

### 📄 `Clients.txt`
```

1234/1111/Ahmed Ali/0101234567/5000.50
4567/2222/Mohamed Youssef/0112233445/2500.00

```

### 📄 `User.txt`
```
Admin/1234/-1
Cashier/1111/35

```

---

## ▶️ **How to Run**
1. 🧰 Keep `main.cpp`, `Clients.txt`, and `User.txt` in the same folder  
2. ⚙️ Compile and run `main.cpp`  
3. 🔑 Login using credentials from `User.txt`  
4. 🧭 Navigate through the main menu options  

---

## 🧠 **Core C++ Concepts Used**
- `fstream` — file read/write operations  
- `vector` & `struct` — data organization  
- `iomanip` — formatted console output  
- Bitwise logic — permission control  
- Menu-driven console UI  

---

## 👑 **Default Admin Account**

| 👤 Username | 🔑 Password | ⚙️ Permission |
|-------------|-------------|----------------|
| Admin | 1234 | -1 *(Full Access)* |

---

## 🧱 **Project Structure**
```



---

<div align="center">

## 🧑‍💻 **Coder**
**Abu**  
💬 *Programmer | C++ Developer*  
🕊️ “Clean code, honest logic, no hidden layers.”

</div>
```

---

it’ll pop nicely on GitHub — headers stand out, icons guide the eye, and it reads fast.
want me to add **color-coded shields** (like `Language: C++`, `Platform: Windows`, `License: MIT`) under the title bar? they make the top look professional without clutter.
