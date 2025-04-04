# 🛰️ ShootEmRocks
*Quick Prototype of the classic game Asteroids in C++ and SFML*

[![Watch the Gameplay Video](https://vumbnail.com/1072605696.jpg)](https://vimeo.com/1072605696)
---

## 🎮 Gameplay
🚀 Control your spaceship and blast incoming asteroids before they destroy you!  
🔥 Survive as long as possible and rack up high scores.  

---

### 🕹️ Controls
- **Arrow Keys / WASD** → Move the spaceship  
- **Spacebar** → Fire bullets  
- **Escape** → Pause / Quit  

---

## 🛠️ Installation & Running the Game

### 🔹 Download & Play
1. Go to the **[Releases](https://github.com/soummy21/ShootEmRocks/releases)** page.  
2. Download the latest **ShootEmRocks_Windows.zip** file.  
3. Extract the ZIP folder.  
4. Double-click `ShootEmRocks.exe` to play! 🎮  

💡 Note: Make sure all `.dll` files are in the same folder as the `.exe` for the game to run correctly.  
⚠ Windows Warning: When running the `.exe`, Windows may show a security warning about an unknown publisher. Click **'More Info' → 'Run Anyway'** to proceed.
---

## ⚙️ Systems Design
The game is built around modular components that interact in real-time using SFML's rendering and event systems:

### 🔸 Core Systems
- **Game Loop:** A fixed timestep loop ensures consistent updates across systems.
- **Event Handling:** Uses SFML’s event polling to process input efficiently.
- **Collision Detection:** Uses SFML's built-in sprite bounding boxes to detect collisions.
- **Entity Management:** Entities (Player, Asteroids, Bullets) are stored in vectors and updated each frame.
- **Rendering System:** Uses SFML sprites and textures for visuals.

### 🔸 Gameplay Systems
- **Asteroid Spawner:** Spawns asteroids with random sizes and velocities.
- **Bullet Pooling:** Dynamically adds bullets with a lifetime and updates their position.
- **Score Manager:** Increments score based on asteroid hits.
- **Health System:** Tracks player health and triggers game-over logic.


---

## 🖥️ Building from Source
If you want to compile the game yourself:

### 🔹 Requirements
- **C++ Compiler** (MSVC, MinGW, or Clang)  
- **SFML 2.5.1** (or later)  
- **Visual Studio 2022** (or any C++ IDE)  

### 🔹 Steps
1. Clone the repository:  
   ```sh
   git clone https://github.com/soummy21/ShootEmRocks.git
   cd ShootEmRocks
   ```
2. Open `ShootEmRocks.sln` in Visual Studio.  
3. Set **build configuration** to `Release`.  
4. Click **Build → Build Solution (Ctrl + Shift + B)**.  
5. Run the compiled `.exe` from `x64/Release/`.  

---
