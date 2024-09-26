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

## Project Structure and Code Explanation

The project consists of a single main.cpp file that contains all the application logic. Here's a breakdown of its structure:

1. **Header Inclusions**: The file includes necessary headers for Crow, cpprestsdk, and standard C++ libraries.

2. **fetchCatFact Function**: This function uses cpprestsdk to make an HTTP GET request to the Cat Fact Ninja API. It handles the response asynchronously and extracts the cat fact from the JSON response.

3. **generateHtml Function**: This function creates an HTML template with embedded CSS for styling. It takes a cat fact as input and inserts it into the HTML structure.

4. **Main Function**: 
   - Creates a Crow application
   - Sets up two routes:
     - GET route for the root URL: Fetches a cat fact and returns the HTML page
     - POST route for the root URL: Handles the "Get New Fact" button click, fetches a new fact, and returns the updated HTML page
   - Starts the web server on port 18080 with multithreading enabled

The application uses modern C++ features and asynchronous programming to handle HTTP requests efficiently.

## App Functionality

1. When a user accesses the root URL, the server fetches a random cat fact from the Cat Fact Ninja API.
2. The server generates an HTML page with the fetched cat fact and sends it to the client.
3. The HTML page displays the cat fact along with a "Get New Fact" button.
4. When the user clicks the "Get New Fact" button, a POST request is sent to the server.
5. The server then fetches a new cat fact and returns a new HTML page with the updated fact.
6. This process can be repeated to get new facts without refreshing the entire page.

## Ideas for Further Enhancements

1. **Caching**: Implement a caching mechanism to store recently fetched cat facts, reducing API calls and improving response times.

2. **Error Handling**: Add more robust error handling for API requests and display user-friendly error messages.

3. **Multiple Facts**: Allow users to specify the number of facts they want to see at once.

4. **Categories**: If the API supports it, add an option for users to choose fact categories (e.g., behavior, history, science).

5. **Styling Options**: Allow users to customize the appearance of the page (e.g., dark mode, different color schemes).

6. **Fact Saving**: Implement a feature to let users save their favorite facts.

7. **Share Feature**: Add buttons to easily share facts on social media platforms.

8. **Localization**: Add support for multiple languages, both in the UI and potentially fetching translated facts if available.

9. **Rate Limiting**: Implement rate limiting to prevent abuse of the API and your server resources.

10. **Metrics**: Add logging and metrics to track usage patterns and performance.

11. **Unit Tests**: Develop a suite of unit tests to ensure reliability as the application grows.

12. **Containerization**: Create a Dockerfile to containerize the application for easier deployment and scaling.

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