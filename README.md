# Flight Ticket System - Technical Report

## Table of Contents
- [Project Overview](#project-overview)
- [System Architecture](#system-architecture)
- [Core Components](#core-components)
- [User Interface](#user-interface)
- [Data Management](#data-management)
- [Authentication System](#authentication-system)
- [Build Configuration](#build-configuration)
- [Code Analysis](#code-analysis)
- [Features](#features)
- [Technical Specifications](#technical-specifications)

## Project Overview

The Flight Ticket System is a desktop application built using C++ and SFML (Simple and Fast Multimedia Library) that provides a comprehensive solution for managing flight bookings. The system supports two types of users: administrators and regular users, each with distinct functionalities.

### Key Objectives
- Provide an intuitive graphical user interface for flight booking
- Enable administrators to manage users and flights
- Allow users to search, filter, and purchase flight tickets
- Maintain persistent data storage for users and flights
- Implement secure authentication system

## System Architecture

The application follows an object-oriented design pattern with clear separation of concerns:

```
Flight Ticket System
├── Authentication Layer
├── User Management Layer
├── Flight Management Layer
├── User Interface Layer
└── Data Persistence Layer
```

### Architecture Principles
- **Modularity**: Each component handles specific functionality
- **Encapsulation**: Data and methods are properly encapsulated within classes
- **Separation of Concerns**: UI, business logic, and data access are separated
- **File-based Persistence**: Simple text file storage for data

## Core Components

### 1. User Management System

#### User Class (User.h, User.cpp)
The User class represents individual users in the system:

```cpp
class User {
    int id;
    std::string username;
    std::string password;
    std::string role;
    
    // Constructor and getter/setter methods
};
```

**Key Features:**
- Unique user ID generation
- Role-based access control (admin/user)
- Basic user information storage
- Getter and setter methods for all attributes

#### UserManager Class (UserManager.h, UserManager.cpp)
Manages all user-related operations:

```cpp
class UserManager {
    std::vector<User> users;
    std::string filePath;
    
    // CRUD operations and authentication
};
```

**Functionality:**
- **Authentication**: Validates username/password combinations
- **User CRUD Operations**: Create, read, update, delete users
- **File I/O**: Loads users from and saves users to text files
- **ID Generation**: Automatically generates unique user IDs

### 2. Flight Management System

#### Flight Structure (Flight.h)
Simple struct to represent flight information:

```cpp
struct Flight {
    char flightNo[10];    // Flight number
    char start[10];       // Departure location
    char end[10];         // Destination
    int duration;         // Flight duration in hours
    int totalTicket;      // Total available tickets
    int soldTicket;       // Tickets already sold
};
```

#### FlightManager Class (FlightManager.h, FlightManager.cpp)
Handles all flight-related operations:

**Core Functions:**
- `loadFlights()`: Reads flight data from file
- `saveFlights()`: Persists flight data to file
- `addFlight()`: Adds new flights to the system
- `deleteFlight()`: Removes flights by index
- `updateFlight()`: Modifies existing flight information
- **Search Operations**: Find flights by various criteria

### 3. User Interface Components

#### InputBox Class (InputBox.h, InputBox.cpp)
Custom input field implementation for SFML:

**Features:**
- Text input handling
- Password masking capability
- Visual feedback for active/inactive states
- Mouse and keyboard event handling
- Placeholder text support

#### AdminPanel Class (AdminPanel.h, AdminPanel.cpp)
Comprehensive administrative interface:

**Capabilities:**
- **Dual-Panel Design**: Switch between user and flight management
- **User Management**: Add, edit, delete users
- **Flight Management**: Complete CRUD operations for flights
- **Real-time Updates**: Changes are immediately saved to files
- **Interactive Selection**: Click-to-edit functionality

#### UserPanel Class (UserPanel.h, UserPanel.cpp)
Customer-facing interface for flight booking:

**Features:**
- **Flight Display**: Shows all available flights with details
- **Filtering System**: Filter by departure and destination
- **Ticket Purchase**: One-click ticket buying with availability checking
- **Real-time Updates**: Immediate ticket count updates
- **Success Messages**: Visual feedback for purchases

## User Interface

### Login Screen
The main entry point features a modern, animated login interface:

- **Gradient Background**: Animated color transitions
- **Floating Elements**: Moving decorative circles
- **Input Focus**: Visual feedback for active input fields
- **Hover Effects**: Smooth button animations
- **Role-based Routing**: Automatic redirection based on user role

### Admin Panel Interface
Split-screen design for comprehensive management:

**User Management Side:**
- User list with inline editing
- Add/Edit user forms
- Delete confirmation
- Real-time user list updates

**Flight Management Side:**
- Complete flight information forms
- Flight list with full details
- Edit/Delete operations
- Immediate file persistence

### User Panel Interface
Customer-focused design for easy booking:

- **Flight Catalog**: Clean list of available flights
- **Filter Controls**: Easy-to-use departure/destination filters
- **Purchase Buttons**: Prominent buy buttons for each flight
- **Status Messages**: Clear feedback for purchase attempts
- **Availability Display**: Real-time ticket availability

## Data Management

### File Structure
The system uses simple text files for data persistence:

**users.txt Format:**
```
<id> <username> <password> <role>
1 admin admin123 admin
2 user1 pass123 user
```

**flights.txt Format:**
```
<flightNo> <start> <end> <duration> <totalTicket> <soldTicket>
AA123 Paris Tokyo 12 200 50
BB456 London NYC 8 300 75
```

### Data Validation
- **Input Validation**: Ensures all required fields are filled
- **Type Checking**: Converts strings to appropriate numeric types
- **File I/O Error Handling**: Graceful handling of file operations
- **Data Integrity**: Maintains consistency between memory and file storage

## Authentication System

### Security Features
- **Username/Password Authentication**: Basic credential verification
- **Role-based Access Control**: Different interfaces for admin/user roles
- **Session Management**: Maintains user state during application use
- **Input Sanitization**: Prevents basic input-related issues

### Authentication Flow
1. User enters credentials on login screen
2. System validates against stored user data
3. Role determination redirects to appropriate interface
4. Session maintains user context throughout application use

## Build Configuration

### CMakeLists.txt Analysis
The project uses CMake for build configuration:

```cmake
cmake_minimum_required(VERSION 3.14)
project(FlyTicketSystem)
set(CMAKE_CXX_STANDARD 17)

# SFML Integration
set(SFML_ROOT "C:/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Executable Configuration
add_executable(FlyTicketSystem [source_files])
target_link_libraries(FlyTicketSystem sfml-graphics sfml-window sfml-system)
```

**Build Requirements:**
- CMake 3.14 or higher
- C++17 standard
- SFML 2.5 library
- Compatible C++ compiler

## Code Analysis

### Design Patterns Used
- **Manager Pattern**: UserManager and FlightManager classes
- **Data Access Object**: File-based persistence layer
- **Model-View Separation**: Business logic separated from UI
- **Factory Pattern**: User ID generation

### Code Quality Aspects

**Strengths:**
- Clear class responsibilities
- Consistent naming conventions
- Proper encapsulation
- File-based persistence

**Areas for Improvement:**
- Hard-coded file paths
- Limited error handling
- No input validation for numeric fields
- Password stored in plain text
- Missing data backup mechanisms

### Memory Management
- Uses RAII principles with SFML objects
- Vector containers for dynamic data storage
- Automatic cleanup of local objects
- No dynamic memory allocation complications

## Features

### Administrator Features
- **User Management**: Complete CRUD operations for users
- **Flight Management**: Add, edit, delete flights
- **Real-time Updates**: Changes immediately reflected in files
- **Dual Interface**: Easy switching between management functions

### User Features
- **Flight Browsing**: View all available flights
- **Advanced Filtering**: Filter by departure and destination
- **Instant Booking**: One-click ticket purchasing
- **Availability Checking**: Real-time ticket availability
- **Purchase Feedback**: Clear success/failure messages

### System Features
- **Persistent Storage**: All data saved to files
- **Authentication**: Secure login system
- **Role-based Access**: Different interfaces for different users
- **Real-time Updates**: Immediate reflection of changes
- **Intuitive UI**: User-friendly graphical interface

## Technical Specifications

### Dependencies
- **SFML 2.5**: Graphics, window management, and event handling
- **C++ Standard Library**: File I/O, containers, strings
- **CMake**: Build system configuration

### System Requirements
- **Operating System**: Windows (paths are Windows-specific)
- **Compiler**: C++17 compatible compiler
- **Graphics**: SFML-compatible graphics system
- **Storage**: Minimal disk space for data files

### File Dependencies
- **Font File**: arial.ttf for text rendering
- **Data Files**: users.txt and flights.txt for persistence
- **Configuration**: Hard-coded paths in source code

### Performance Characteristics
- **Startup Time**: Quick loading of user and flight data
- **Response Time**: Immediate UI responses
- **Memory Usage**: Minimal memory footprint
- **File I/O**: Efficient text-based storage

## Conclusion

The Flight Ticket System represents a well-structured desktop application that successfully demonstrates object-oriented programming principles while providing practical functionality for flight booking management. The system effectively separates concerns between user management, flight operations, and user interface components.

The application serves as an excellent example of combining C++ programming with graphical user interface development using SFML, creating an intuitive and functional system for both administrators and end users.

### Future Enhancement Opportunities
- Database integration for better data management
- Enhanced security with encrypted passwords
- Network functionality for multi-user access
- Advanced reporting and analytics features
- Mobile application compatibility
- Integration with external flight APIs
