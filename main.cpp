#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>  // For Windows API
#include <curl/curl.h>

// Callback function to write the fetched data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    }
    catch (std::bad_alloc &e) {
        // Handle memory allocation errors
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return 0;
    }
    return newLength;
}

// Function to create a filename from URL
std::string createFilename(const std::string& url) {
    std::string filename = url;
    // Replace invalid characters with underscores
    std::replace(filename.begin(), filename.end(), ':', '_');
    std::replace(filename.begin(), filename.end(), '/', '_');
    std::replace(filename.begin(), filename.end(), '?', '_');
    std::replace(filename.begin(), filename.end(), '=', '_');
    std::replace(filename.begin(), filename.end(), '&', '_');
    filename += ".html";
    return filename;
}

// Function to ensure the scraps directory exists
void ensureScrapsDirectory() {
    std::string dirPath = "scraps";
    if (!CreateDirectory(dirPath.c_str(), NULL)) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            std::cerr << "Failed to create directory: " << dirPath << std::endl;
        }
    }
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string url;

    // Ensure the scraps directory exists
    ensureScrapsDirectory();

    std::cout << "Enter the URL: ";
    std::getline(std::cin, url); // Read the entire URL

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Convert string to C-style string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Enable verbose output for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::string filename = createFilename(url);
            std::string filePath = "scraps/" + filename;

            // Open file stream
            std::ofstream outFile(filePath);
            if (outFile.is_open()) {
                outFile << readBuffer;
                outFile.close();
                std::cout << "HTML content saved to: " << filePath << std::endl;
            } else {
                std::cerr << "Failed to create file: " << filePath << std::endl;
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }
    return 0;
}
