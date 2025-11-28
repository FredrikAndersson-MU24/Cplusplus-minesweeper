# C++ Minesweeper
## Assignment
Implement a text-based mine sweeper game in C++. The game should be played through the console and have basic
functionality to let the user play the game by revealing tiles, flagging mines and trying to avoid stepping on a mine.

[Full assignment description (swedish)](https://gist.github.com/davidsvson/2977e7f2583ce489a1f68ee728060811)

## Project description
The project has been developed with structure, extensibility and abstraction in mind, breaking down problems into small 
reusable functions, and trying to avoid repetition.  

Memory management has been a central part of the project, taking actions to avoid memory leaks by using smart pointers
to control the life cycle of instantiated objects.

## Project structure

The main classes are `Cell` and `GameBoard`, where GameBoard holds a vector of `Cell` objects. The size of the vector is 
determined by the size that the user chooses for the `GameBoard` when starting a new game. Although there are three preset 
board sizes in the game menu, the function has been designed to handle dynamic sizing, given that the total number of 
cells is a perfect square. Each cell has several member variables to, for example, keep track of if it has a mine or not. 

Two utility classes are implemented to separate their respective logic from other classes and promote reusable code and 
abstraction:
- `InputHandlers`: Contains functions to handle and validate user input. 
- `Menus`: Contains all menus, where the main menu function is static and therefore can be invoked from main.cpp without 
being instantiated. The underlying menus and helper functions are under private access specifier to ensure encapsulation. 

```
project_root/
├── inc/
│   ├── Cell.h
│   └── GameBoard.h
├── src/
│   ├── Cell.cpp
│   └── GameBoard.cpp
├── utils/
│   ├── inc/
│   │   ├── InputHandlers.h
│   │   └── Menus.h
│   └── src/
│       ├── InputHandlers.cpp
│       └── Menus.cpp
├── main.cpp
└── CMakeLists.txt
```

- `inc/`: Contains header files for the main classes.
- `src/`: Contains the implementation files for the main classes.
- `utils/inc/`: Contains header files for utility classes.
- `utils/src/`: Contains the implementation files for utility classes.
- `main.cpp`: The main entry point of the application.
- `CMakeLists.txt`: CMake configuration file for building the project.


## Compiling
To ensure that the project will compile regardless of operating system, a `CMakeLists.txt` file has been provided. 
Make sure you have CMake installed.  
Use this command to compile the project in a directory called `build`:
```
cmake --build build
```
Run the executable:
```
./build/minesweeper
```

## Reflection/Final thoughts 
During the project I have been able to use my knowledge of C++, particularly memory management in C++, and also both 
prior and new knowledge of Object-Oriented Programming (OOP). 
By using relevant smart pointers the life cycle of allocated heap memory is controlled. Part of the memory managemnet has
also been to decide in which scope each smart pointer should live, implementing them in relevant scopes to have them
deleted when going out of scope when they are no longer needed.

Breaking down problems into smaller single purpose functions fits the concept of OOP well as it promotes 
encapsulation and also keeping the code DRY(Don't Repeat Yourself).

I have explored using CMakeLists to structure the project and to make sure it will compile on any operating system, 
as long as CMake is installed.