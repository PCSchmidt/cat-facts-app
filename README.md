# C++ Cat Facts App

This is a simple C++ web application that fetches and displays random cat facts. It uses the Crow web framework for C++ to create a web server and the C++ REST SDK (cpprestsdk) to make HTTP requests to an external API.

## Features

- Fetches random cat facts from the [Cat Fact Ninja API](https://catfact.ninja/)
- Displays cat facts on a simple, responsive HTML page
- Provides a button to fetch new facts without refreshing the page
- Uses modern C++ (C++17) features
- Implements a lightweight web server using Crow

## Dependencies

This project relies on the following libraries:

- [Crow](https://github.com/CrowCpp/Crow): A C++ microframework for web
- [C++ REST SDK (cpprestsdk)](https://github.com/Microsoft/cpprestsdk): A cross-platform web API framework for C++

The project uses vcpkg for managing these dependencies.

## Prerequisites

- CMake (version 3.10 or higher)
- A C++17 compatible compiler (like Visual Studio 2017 or later on Windows, or GCC 7+ on Linux)
- vcpkg package manager

## Build Instructions

1. Make sure you have [vcpkg](https://github.com/Microsoft/vcpkg) installed and integrated with your development environment.

2. Install the required packages using vcpkg:
   ```
   vcpkg install crow cpprestsdk
   ```

3. Clone this repository:
   ```
   git clone https://github.com/yourusername/cpp-quote-app.git
   cd cpp-quote-app
   ```

4. Generate the build files using CMake:
   ```
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
   ```
   Replace `[path to vcpkg]` with the actual path to your vcpkg installation.

5. Build the project:
   ```
   cmake --build build --config Release
   ```

## Usage

After building the project, you can run the executable:

```
.\build\Release\quote_app.exe  # On Windows
./build/quote_app  # On Unix-like systems
```

The application will start a web server on `http://localhost:18080`. Open this URL in your web browser to see a random cat fact. Click the "Get New Fact" button to fetch and display a new fact.

## Project Structure

- `main.cpp`: Contains the main application logic, including the web server setup and API requests.
- `CMakeLists.txt`: CMake configuration file for building the project.
- `README.md`: This file, containing project information and instructions.

## Troubleshooting

If you encounter any issues:

1. Make sure all dependencies are correctly installed via vcpkg.
2. Check that your CMake version is 3.10 or higher.
3. Ensure that your compiler supports C++17.
4. On Windows, make sure you're using a compatible version of Visual Studio with C++17 support.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available under the [MIT License](LICENSE).