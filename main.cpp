#include <crow.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <string>

using namespace web;
using namespace web::http;
using namespace web::http::client;

// Function to fetch a random cat fact from the API
void fetchCatFact(std::string& catFact) {
    // Create an HTTP client to send requests to the cat fact API
    http_client client(U("https://catfact.ninja/fact"));
    
    // Send a GET request to the API
    client.request(methods::GET).then([&catFact](http_response response) {
        // Check if the response status is OK (200)
        if (response.status_code() == status_codes::OK) {
            // Extract the JSON content from the response
            return response.extract_json();
        }
        // Return an empty JSON value if the status is not OK
        return pplx::task_from_result(json::value());
    }).then([&catFact](pplx::task<json::value> previousTask) {
        try {
            // Get the JSON value from the previous task
            json::value const &v = previousTask.get();
            // Extract the "fact" field from the JSON and convert it to a string
            catFact = utility::conversions::to_utf8string(v.at(U("fact")).as_string());
        } catch (http_exception const &e) {
            // Print any exceptions that occur
            std::wcout << e.what() << std::endl;
        }
    }).wait(); // Wait for the asynchronous operations to complete
}

// Function to generate HTML content with the cat fact
std::string generateHtml(const std::string& catFact) {
    // HTML template with placeholders for the cat fact
    std::string html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Random Cat Fact</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
        .container { max-width: 600px; margin: 0 auto; }
        h1 { color: #333; }
        p { font-size: 18px; color: #666; margin: 20px 0; }
        form { margin-top: 20px; }
        button { padding: 10px 20px; font-size: 16px; cursor: pointer; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Random Cat Fact</h1>
        <p>)";
    
    // Insert the cat fact into the HTML
    html += catFact;
    
    // Close the HTML tags
    html += R"(</p>
        <form method="post">
            <button type="submit">Get New Fact</button>
        </form>
    </div>
</body>
</html>
)";

    // Return the generated HTML
    return html;
}

int main() {
    // Create a Crow application
    crow::SimpleApp app;

    // Define a route for the root URL (GET request)
    CROW_ROUTE(app, "/")
    ([](const crow::request& req) {
        std::string catFact;
        // Fetch a cat fact
        fetchCatFact(catFact);
        // Generate and return the HTML response
        return crow::response(generateHtml(catFact));
    });

    // Define a route for the root URL (POST request)
    CROW_ROUTE(app, "/").methods("POST"_method)
    ([](const crow::request& req) {
        std::string catFact;
        // Fetch a cat fact
        fetchCatFact(catFact);
        // Generate and return the HTML response
        return crow::response(generateHtml(catFact));
    });

    // Print a message indicating the server is starting
    std::cout << "Starting web server at http://localhost:18080" << std::endl;
    // Start the web server on port 18080 with multithreading enabled
    app.port(18080).multithreaded().run();

    return 0;
}
