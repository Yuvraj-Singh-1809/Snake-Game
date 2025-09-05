# Snake Game

A classic Snake game implementation built with **C++** and **SFML** (Simple and Fast Multimedia Library), featuring smooth gameplay, collision detection, and a complete game state management system.

## 🎮 Features

- **Classic Gameplay**: Navigate the snake to eat food and grow longer
- **Multiple Control Schemes**: Use arrow keys or WASD for movement
- **Collision Detection**: Wall boundaries and self-collision detection
- **Score System**: Real-time score tracking with visual display
- **Game States**: Complete menu system with main menu, gameplay, pause, and game over screens
- **Smooth Graphics**: Custom sprites for snake, food, walls, and background
- **State Management**: Professional game state architecture for seamless transitions

## 🛠️ Technologies Used

- **C++17**: Modern C++ features and standard library
- **SFML**: Cross-platform multimedia library for graphics, audio, and window management
- **Visual Studio**: Windows development environment
- **Object-Oriented Design**: Clean architecture with proper encapsulation

## 📁 Project Structure

```
Snake Game/
├── Main.cpp              # Entry point
├── Game.hpp/cpp          # Core game engine and main loop
├── State.hpp             # Abstract base class for game states
├── StateManager.hpp/cpp  # Manages game state transitions
├── Snake.hpp/cpp         # Snake entity with movement and collision logic
├── GamePlay.hpp/cpp      # Main gameplay state implementation
├── MainMenu.hpp/cpp      # Main menu state
├── GameOver.hpp/cpp      # Game over state
├── PauseGame.hpp/cpp     # Pause menu state
├── AssetManager.hpp/cpp  # Resource management for textures and fonts
├── Assets/
│   ├── snake.png         # Snake sprite
│   ├── food.png          # Food sprite
│   ├── wall.png          # Wall boundary sprite
│   ├── grass.png         # Background texture
│   └── DynaPuff-Regular.ttf # Game font
└── Snake Game.vcxproj    # Visual Studio project file
```

## 🎯 Core Components

### Snake Class
- **Dynamic Growth**: Linked list-based body management for efficient growth
- **Movement System**: Grid-based movement with direction validation
- **Collision Detection**: Self-intersection and boundary collision detection
- **Rendering**: Custom drawable implementation for SFML rendering

### Game States
- **Main Menu**: Welcome screen with game start options
- **Gameplay**: Core game mechanics and user interaction
- **Pause**: Pause functionality with resume capability
- **Game Over**: End screen with restart options

### Asset Management
- **Texture Loading**: Centralized texture management with ID-based access
- **Font Management**: Typography system for UI elements
- **Resource Optimization**: Efficient memory management for game assets

## 🚀 Getting Started

### Prerequisites
- **Visual Studio 2019/2022** with C++ development tools
- **SFML Library**: Download and configure SFML for your development environment
- **Windows OS**: Currently configured for Windows development

### Setup Instructions

1. **Clone the Repository**
   ```bash
   git clone https://github.com/Yuvraj-Singh-1809/Snake-Game.git
   cd Snake-Game
   ```

2. **Configure SFML**
   - Download SFML from [sfml-dev.org](https://www.sfml-dev.org/)
   - Set up the `SFML_PATH` environment variable pointing to your SFML installation
   - Ensure all required SFML libraries are accessible

3. **Build and Run**
   - Open `Snake Game.sln` in Visual Studio
   - Select your preferred configuration (Debug/Release, x64/x86)
   - Build and run the project (F5)

## 🎮 How to Play

- **Movement**: Use arrow keys or WASD to control the snake
  - `↑/W`: Move up
  - `↓/S`: Move down
  - `←/A`: Move left
  - `→/D`: Move right
- **Pause**: Press `Escape` to pause the game
- **Objective**: Eat food to grow longer and increase your score
- **Game Over**: Avoid hitting walls or the snake's own body

## 🏗️ Architecture Highlights

### State Management Pattern
The game implements a robust state management system allowing smooth transitions between different game screens and maintaining clean separation of concerns.

### Entity-Component Design
The Snake class follows modern C++ practices with RAII, smart pointers, and efficient STL container usage for body segment management.

### Resource Management
Centralized asset management ensures efficient loading and lifetime management of game resources.

## 🔧 Technical Implementation

- **Frame Rate**: 60 FPS with delta-time based updates
- **Grid System**: 16x16 pixel grid for consistent movement and collision
- **Memory Management**: Smart pointers and RAII for automatic resource cleanup
- **Collision System**: AABB (Axis-Aligned Bounding Box) collision detection
- **Rendering Pipeline**: Efficient sprite batching and state management

## 🚀 Future Enhancements

- [ ] High score persistence
- [ ] Multiple difficulty levels
- [ ] Sound effects and background music
- [ ] Power-ups and special food items
- [ ] Multiplayer support
- [ ] Cross-platform compatibility (Linux/macOS)
- [ ] Mobile port potential

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## 📄 License

This project is open source. Feel free to use, modify, and distribute as needed.

## 👨‍💻 Author

**Yuvraj Singh** - [GitHub Profile](https://github.com/Yuvraj-Singh-1809)

---

*Built with passion for classic gaming and modern C++ development practices.*