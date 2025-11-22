#include "UrlShortener.h"
#include "httplib.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    UrlShortener shortener;
    httplib::Server svr;

    // Serve the HTML frontend
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        ifstream html("index.html");
        string content((istreambuf_iterator<char>(html)), istreambuf_iterator<char>());
        res.set_content(content, "text/html");
    });

    // API to shorten URL
    svr.Post("/shorten", [&](const httplib::Request& req, httplib::Response& res) {
        string url = req.get_param_value("url");
        string algo = req.has_param("algo") ? req.get_param_value("algo") : "djb2";
        try {
            string code = shortener.shorten(url, algo);
            res.set_content(code, "text/plain");
        } catch (const exception& e) {
            res.status = 400;
            res.set_content(e.what(), "text/plain");
        }
    });

    // API to expand short code
    svr.Get(R"(/expand/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
        string code = req.matches[1];
        string url = shortener.retrieve(code);
        if (url != "URL not found")
            res.set_content(url, "text/plain");
        else
            res.status = 404;
    });

    cout << "Server running at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
} 