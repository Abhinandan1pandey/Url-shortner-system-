#include "UrlShortener.h"
#include <functional>

const std::string UrlShortener::chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

UrlShortener::UrlShortener() {}

std::string UrlShortener::hashUrl(const std::string& url, int attempt, const std::string& algo) {
    size_t hash = 0;
    std::string input = url + std::to_string(attempt);
    if (algo == "djb2") {
        hash = 5381;
        for (char c : input) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
    } else if (algo == "sdbm") {
        for (char c : input) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
    } else if (algo == "fnv") {
        // FNV-1a 64-bit
        hash = 14695981039346656037ull;
        for (char c : input) {
            hash ^= static_cast<unsigned char>(c);
            hash *= 1099511628211ull;
        }
    } else if (algo == "simple") {
        for (char c : input) {
            hash += static_cast<unsigned char>(c);
        }
    } else {
        // fallback to std::hash
        std::hash<std::string> hasher;
        hash = hasher(input);
    }
    std::string code;
    for (int i = 0; i < 6; ++i) {
        code += chars[hash % chars.size()];
        hash /= chars.size();
    }
    return code;
}

std::string UrlShortener::shorten(const std::string& longUrl, const std::string& algo) {
    if (urlToCode.count(longUrl))
        return urlToCode[longUrl];
    int attempt = 0;
    std::string code;
    do {
        code = hashUrl(longUrl, attempt++, algo);
    } while (codeToUrl.count(code)); // Linear probing for collision handling
    codeToUrl[code] = longUrl;
    urlToCode[longUrl] = code;
    return code;
}

std::string UrlShortener::retrieve(const std::string& shortCode) {
    if (codeToUrl.count(shortCode))
        return codeToUrl[shortCode];
    return "";
} 