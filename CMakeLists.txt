cmake_minimum_required(VERSION 3.10)
project(QuoteApp)

set(CMAKE_CXX_STANDARD 17)

# Find cpprestsdk and Crow via vcpkg
find_package(cpprestsdk CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)

# Add the executable
add_executable(quote_app main.cpp)

# Link cpprestsdk and Crow to your executable
target_link_libraries(quote_app PRIVATE cpprestsdk::cpprest Crow::Crow)

# If you're using Windows, you might need to add this to avoid potential issues
if(MSVC)
    target_compile_options(quote_app PRIVATE /bigobj)
endif()

# Add preprocessor definition for _WIN32_WINNT
if(WIN32)
    target_compile_definitions(quote_app PRIVATE _WIN32_WINNT=0x0601)
endif()
