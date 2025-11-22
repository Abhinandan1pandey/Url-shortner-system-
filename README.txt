C++ URL Shortener Web App
========================

This project lets you shorten URLs using hashing and collision handling, with a web interface.

---

**Requirements:**
- Windows
- MinGW-w64 (C++ compiler)
- Modern web browser (Chrome, Edge, Firefox, etc.)

---

**Setup Instructions:**

1. Install MinGW-w64:
   - Download from: https://www.mingw-w64.org/downloads/
   - Use the SourceForge link for Windows.
   - During install, choose:
     - Architecture: x86_64
     - Threads: posix
     - Exception: seh
     - Add MinGW to your system PATH (installer option)

2. Open a new Command Prompt or PowerShell window.

3. Go to the project directory:
   cd C:\path\to\your\directory

4. Compile the project:
   g++ main.cpp UrlShortener.cpp -o url_shortener.exe

5. Run the server:
   .\url_shortener.exe for Windows
   .\url_shortener.out for Linux

6. Open your browser and go to:
   http://localhost:8080

---

**How to Use:**
- Paste a long URL, select a hash algorithm, and click "Shorten" to get a short code.
- Paste a short code and click "Expand" to get the original URL.

---

If you have any issues, make sure MinGW-w64 is installed and in your PATH. If you get errors, copy them and ask for help! 