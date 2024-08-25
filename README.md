# Web Scraper Using C++

A simple command-line web scraper written in C++ that fetches HTML content from a given URL and saves it to an HTML file in a `scraps` directory.

## Features

- Fetches HTML content from a user-specified URL.
- Saves the HTML content to an HTML file in a `scraps` directory.
- Handles invalid characters in URLs to create valid filenames.

## Prerequisites

- **C++17 or later**: Ensure your compiler supports C++17. Update project settings if needed.
- **libcurl**: The project depends on the libcurl library for making HTTP requests. Make sure it is installed on your system.

## Installation

### Cloning the Repository

```sh
git clone https://github.com/adhikareeprayush/WebScraper.git
cd WebScraper
```

### Building the Project

1. **Install libcurl**:
    - On **Windows**, you can download the pre-built binaries from the [curl website](https://curl.se/windows/).
    - On **Linux**, you can install it using your package manager:
      ```sh
      sudo apt-get install libcurl4-openssl-dev
      ```

2. **Create a Build Directory**:
   ```sh
   mkdir build
   cd build
   ```

3. **Generate the Build System with CMake**:
   ```sh
   cmake ..
   ```

4. **Build the Project**:
   ```sh
   cmake --build .
   ```

## Usage

1. Run the executable from the build directory:
   ```sh
   ./Debug/WebScraper
   ```

2. Enter the URL when prompted. The HTML content will be fetched and saved to a file in the `scraps` directory.

   Example:
   ```
   Enter the URL: https://www.example.com
   HTML content saved to: scraps/https___www_example_com.html
   ```

## Code Overview

- **main.cpp**: Contains the main logic of the web scraper, including fetching HTML content and saving it to a file.

### Key Functions

- `WriteCallback`: Callback function to handle the fetched data.
- `createFilename`: Generates a valid filename from the URL.
- `ensureScrapsDirectory`: Creates the `scraps` directory if it does not exist.

## Troubleshooting

- **libcurl Errors**: Ensure libcurl is properly installed and linked. Check the `CMakeLists.txt` file for correct configuration.
- **URL Format**: Make sure the URL is correctly formatted. The program currently does not handle all possible URL formats.

## License

This project is licensed under the MIT License. See the [MIT LICENSE](LICENSE) file for details.

## Contributing

Feel free to submit issues and pull requests. Contributions are welcome!
