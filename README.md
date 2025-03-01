# BenchmarkOne

BenchmarkOne is a C++ application designed for performance testing and benchmarking various computational tasks. It utilizes the GTK library for graphical user interface elements and allows users to execute and compare different mathematical and algorithmic operations efficiently.

## 📌 Features
- Benchmarking of matrix multiplication.
- Prime number calculations using the Sieve of Eratosthenes.
- Floating-point precision tests using Pi calculations.
- Interactive GTK-based user interface.
- Real-time results display and progress tracking.

## 🚀 Technologies Used
- **C++**
- **GTK** for GUI
- **CMake** for build automation
- **Git** for version control

## 📂 Project Structure
```
BenchmarkOne/
│── cmake-build-debug/   # Build directory
│── src/
│   ├── main.cpp         # Main application logic
│   ├── benchmarks/      # Benchmarking algorithms
│── CMakeLists.txt       # CMake configuration
│── README.md            # This file
```

## ⚡ Installation & Running
1. Clone the repository:
   ```sh
   git clone https://github.com/RaresTDS/BenchmarkOne.git
   cd BenchmarkOne
   ```
2. Build the project using CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the application:
   ```sh
   ./BenchmarkOne
   ```
4. Ensure you have **GTK** installed for GUI support:
   ```sh
   sudo apt install libgtk-3-dev  # Linux
   brew install gtk+3             # macOS
   ```

## 🛠 Contributing
If you want to contribute:
1. Fork the repository.
2. Create a new branch:
   ```sh
   git checkout -b new-feature
   ```
3. Make your changes and commit:
   ```sh
   git commit -m "Added a new benchmark feature!"
   ```
4. Push your changes:
   ```sh
   git push origin new-feature
   ```
5. Open a **Pull Request**!

---
🔹 *If you have any questions or suggestions, feel free to contribute or open an issue!* 😊
