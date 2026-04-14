# 🔐 Haseeb Zahid Password Manager

> A secure, local password vault built with **C++ and Qt** — featuring XOR encryption, SHA-256 master password hashing, and a clean dark-themed GUI.

**Developed by Haseeb Zahid**

---

## 📸 Screenshots

| Login Screen | Main Dashboard | Add Password |
|---|---|---|
| Dark login with master password field | Full vault table with reveal/copy buttons | Clean modal with password generator |

*(Screenshots available after building the project)*

---

## ✨ Features

- **🔑 Master Password Authentication**
  - First-run setup creates and hashes your master password (SHA-256)
  - All subsequent logins verify against the stored hash
  - Master password is never saved — only its hash is on disk

- **🗄️ Password Vault**
  - Store website/app name, username, and password
  - All passwords saved encrypted — never in plain text
  - Live search to filter entries instantly

- **🔒 Encryption**
  - XOR cipher with master password as key
  - Base64 encoding for safe file storage
  - Passwords only decrypted in memory, on demand

- **🎨 Modern Dark GUI**
  - Frameless login dialog with animated feedback
  - Full-featured dashboard table
  - Reveal / Hide password toggle per entry
  - One-click copy to clipboard (auto-clears button text)
  - Delete with confirmation dialog

- **⚡ Password Generator**
  - Built-in 16-character strong password generator
  - Uses uppercase, lowercase, numbers, and symbols

---

## 📁 Project Structure

```
PasswordManager/
│
├── main.cpp                  # Entry point — boots login then dashboard
│
├── encryption.h/.cpp         # XOR cipher + SHA-256 hashing
├── password_manager.h/.cpp   # Core logic — auth, vault CRUD
├── file_handler.h/.cpp       # File I/O — read/write master hash & vault
│
├── login_dialog.h/.cpp       # Login / first-run setup dialog (Qt)
├── add_password_dialog.h/.cpp# Add new entry dialog (Qt)
├── main_window.h/.cpp        # Main dashboard window (Qt)
│
├── password_manager.pro      # qmake project file
├── CMakeLists.txt            # CMake build file
└── README.md
```

---

## 🛠️ Tech Stack

| Component | Choice |
|---|---|
| Language | C++17 |
| GUI Framework | Qt 5 / Qt 6 |
| Encryption | Custom XOR cipher |
| Hashing | SHA-256 via Qt's `QCryptographicHash` |
| Data Storage | Local `.dat` files (tab-separated) |
| Build System | qmake or CMake |

---

## 🚀 Getting Started

### Prerequisites

- **Qt 5.12+** or **Qt 6.x** installed
- A C++17-compatible compiler (GCC, MSVC, or Clang)
- `qmake` or `cmake` available in your PATH

### Option 1 — Build with qmake

```bash
# 1. Clone the repo
git clone https://github.com/haseebzahid/password-manager.git
cd password-manager

# 2. Generate Makefile
qmake password_manager.pro

# 3. Compile
make          # Linux / macOS
mingw32-make  # Windows (MinGW)

# 4. Run
./PasswordManager        # Linux / macOS
PasswordManager.exe      # Windows
```

### Option 2 — Build with CMake

```bash
git clone https://github.com/haseebzahid/password-manager.git
cd password-manager

mkdir build && cd build
cmake ..
cmake --build .

./PasswordManager
```

### Option 3 — Qt Creator (easiest)

1. Open **Qt Creator**
2. File → Open Project → select `password_manager.pro`
3. Configure with your Qt kit
4. Press **Run** (▶)

---

## 🗃️ Data Files

The app stores two files in your system's app data directory:

| File | Purpose |
|---|---|
| `master.dat` | SHA-256 hash of your master password |
| `vault.dat` | Tab-separated encrypted password entries |

On **Windows**: `C:\Users\<you>\AppData\Roaming\Haseeb Zahid\PasswordManager\`  
On **Linux**: `~/.local/share/Haseeb Zahid/PasswordManager/`  
On **macOS**: `~/Library/Application Support/Haseeb Zahid/PasswordManager/`

> ⚠️ **Important**: If you forget your master password, your vault cannot be recovered. There is no backdoor by design.

---

## 🔐 Security Notes

| Aspect | Implementation |
|---|---|
| Master password | SHA-256 hashed; never stored in plain text |
| Vault passwords | XOR-encrypted with master password as key |
| Memory | Master password kept in RAM only while app is open |
| File format | Only encrypted ciphertext (Base64) is written to disk |

> This is a learning/portfolio project. For production-grade security, consider libsodium or OpenSSL.

---

## 🔮 Future Improvements

- [ ] Password strength indicator on the add dialog
- [ ] AES-256 encryption (via OpenSSL) for stronger security
- [ ] Password categories / tags
- [ ] Auto-lock after inactivity timeout
- [ ] Export vault as encrypted backup file
- [ ] Dark/Light theme toggle
- [ ] Browser extension integration
- [ ] Biometric authentication (Windows Hello / Touch ID)
- [ ] Cross-platform sync (optional, encrypted)

---

## 🤝 Contributing

Pull requests are welcome! Please:

1. Fork the repo
2. Create your feature branch: `git checkout -b feature/my-feature`
3. Commit your changes: `git commit -m 'Add my feature'`
4. Push: `git push origin feature/my-feature`
5. Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Haseeb Zahid**  
GitHub: [@haseebzahid](https://github.com/haseebzahid9)

---

<p align="center">Built with ❤️ in C++ by Haseeb Zahid</p>
