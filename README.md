# OS-Simulator-Project# CPU Scheduling Algorithms Simulator
A simple Operating Systems project that implements four classic CPU scheduling algorithms in C:

- FCFS (First Come First Served)
- SJF (Shortest Job First, Non-preemptive)
- Priority Scheduling (Non-preemptive)
- Round Robin (with quantum)

The program calculates:
- Start time
- Finish time
- Waiting time
- Turnaround time
- Average waiting & turnaround times
- Gantt chart (text-based)

An optional frontend (`index.html`) provides a browser-based visualization, but the core requirement is fully covered by the C implementation.

---

## Features
- Beginner-friendly C code
- No external libraries required
- Works on Windows, macOS, and Linux
- Fully interactive console program
- Supports 1–100 processes
- Accurate scheduling simulation identical to OS textbook behavior

---

## Files
main.c # Main C program
index.html # Optional frontend visualizer (HTML/JS)


---

# How to Compile & Run

## macOS
macOS includes Clang by default.

### 1. Open Terminal
### 2. Navigate to your project folder:
```bash
cd path/to/project
```

### 3. Compile: 
```bash
clang cpu_scheduling.c -o scheduler
```

### 4. Run:
```bash
./scheduler
```

If you get a permission error:
```bash
chmod +x scheduler
./scheduler
```

### Windows

You need GCC. Install MinGW:

Download from:
https://sourceforge.net/projects/mingw/

Install mingw32-gcc-g++

Add MinGW to PATH

Open CMD

1. Navigate to project folder:
```bash
cd path\to\project
```

2. Compile:
```bash
gcc cpu_scheduling.c -o scheduler.exe
```

3. Run:
```bash
scheduler.exe
```

Conclusion

This project demonstrates four essential CPU scheduling algorithms through a clean C implementation.
It is fully functional, cross-platform, and suitable for Operating Systems coursework or demos.

If you want a PDF report, screenshots, or a more advanced version — just ask.
