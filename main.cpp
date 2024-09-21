#include <crow.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <string>

using namespace web;
using namespace web::http;
using namespace web::http::client;

void fetchCatFact(std::string& catFact) {
    http_client client(U("https://catfact.ninja/fact"));
    
    client.request(methods::GET).then([&catFact](http_response response) {
        if (response.status_code() == status_codes::OK) {
            return response.extract_json();
        }
        return pplx::task_from_result(json::value());
    }).then([&catFact](pplx::task<json::value> previousTask) {
        try {
            json::value const &v = previousTask.get();
            catFact = utility::conversions::to_utf8string(v.at(U("fact")).as_string());
        } catch (http_exception const &e) {
            std::wcout << e.what() << std::endl;
        }
    }).wait();
}

std::string generateHtml(const std::string& catFact) {
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
    
    html += catFact;
    
    html += R"(</p>
        <form method="post">
            <button type="submit">Get New Fact</button>
        </form>
    </div>
</body>
</html>
)";

    return html;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](const crow::request& req) {
        std::string catFact;
        fetchCatFact(catFact);
        return crow::response(generateHtml(catFact));
    });

    CROW_ROUTE(app, "/").methods("POST"_method)
    ([](const crow::request& req) {
        std::string catFact;
        fetchCatFact(catFact);
        return crow::response(generateHtml(catFact));
    });

    std::cout << "Starting web server at http://localhost:18080" << std::endl;
    app.port(18080).multithreaded().run();

    return 0;
}
