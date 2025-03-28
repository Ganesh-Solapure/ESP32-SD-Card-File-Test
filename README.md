# ESP32 SD Card File Operations

This project demonstrates how to perform file operations on an SD card using the ESP32. The example includes mounting the SD card, creating, writing, reading, and deleting files. It also displays the SD card details like type and size.

## Table of Contents

- [Hardware Setup](#hardware-setup)
- [Installation](#installation)
- [Code Overview](#code-overview)
- [Expected Output](#expected-output)
- [Troubleshooting](#troubleshooting)
- [License](#license)

## Hardware Setup

To follow this project, connect an SD card module to your ESP32 as follows:

| SD Card Module | ESP32     |
|----------------|-----------|
| MOSI           | GPIO 23   |
| MISO           | GPIO 19   |
| SCLK           | GPIO 18   |
| CS             | GPIO 5    |
| VCC            | 3.3V or 5V|
| GND            | GND       |

## Installation

1.  Install the Arduino IDE.
2.  Install the ESP32 board support in Arduino IDE using the Board Manager.
3.  Install the required libraries:
    -   `FS.h` for file system handling.
    -   `SD.h` for SD card management.
    -   `SPI.h` for SPI communication.
4.  Connect the ESP32 to your computer via USB.
5.  Upload the code to your ESP32.

## Code Overview

-   **SD Card Initialization:** The code initializes SPI communication and mounts the SD card.
-   **File Management:** It creates, checks, deletes, and reads files (`helloworld.txt` and `test.txt`).
-   **Directory Management:** Prints the contents of the SD card root directory using a recursive function.
-   **Error Handling:** Provides clear error messages if file operations fail.

## Expected Output

When uploading and running the code, the Serial Monitor (set to 115200 baud rate) will display:

-   SD card initialization status (success or failure)
-   Card size and type
-   File creation, deletion, and read operations
-   File content for `test.txt`

## Troubleshooting

-   **SD Card Not Detected:**
    -   Ensure the wiring is correct.
    -   Confirm the SD card is properly formatted (FAT32).
-   **File Operation Errors:**
    -   Verify the card has sufficient space.
    -   Check the file paths and permissions.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
