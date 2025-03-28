#include "FS.h" // File System library for accessing files on SD card

#include "SD.h" // SD card library for SPI-based communication

#include "SPI.h" // SPI library for managing SPI communication

// Define SD card connection pins for SPI communication
#define SD_MOSI     23  // Master Out Slave In (MOSI)
#define SD_MISO     19  // Master In Slave Out (MISO)
#define SD_SCLK     18  // Serial Clock (SCLK)
#define SD_CS       5   // Chip Select (CS)

File myFile; // File object for handling file operations

// Setup function for initializing serial communication and SD card
void setup()
{
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate
  while (!Serial) 
  {
    ; // Wait for serial port to connect. Required for native USB ports
  }

  Serial.println("Setup start");

  // Initialize SPI communication with defined pins
  SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);

  // Try to mount the SD card using the defined CS pin
  if (!SD.begin(SD_CS)) 
  {
    Serial.println("SD Card MOUNT FAIL"); // Print error if mounting fails
  } 
  else 
  {
    Serial.println("SD Card MOUNT SUCCESS"); // Print success message if mounting succeeds
    Serial.println("");

    // Get and display the SD card size in MB
    uint32_t cardSize = SD.cardSize() / (1024 * 1024);
    String str = "SDCard Size: " + String(cardSize) + "MB";
    Serial.println(str);

    // Get and print the SD card type
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE)
    {
      Serial.println("No SD card attached"); // Print error if no card is detected
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC)
    {
        Serial.println("MMC"); // MultiMedia Card
    } 
    else if(cardType == CARD_SD)
    {
        Serial.println("SDSC"); // Standard Capacity SD Card
    } 
    else if(cardType == CARD_SDHC)
    {
        Serial.println("SDHC"); // High Capacity SD Card
    } 
    else 
    {
        Serial.println("UNKNOWN"); // Unknown card type
    }

    // Open the root directory and print directory contents
    myFile = SD.open("/");
    printDirectory(myFile, 0);
    myFile.close();
    Serial.println("");

    // Create a new file named 'helloworld.txt' and close it
    Serial.println("Creating helloworld.txt...");
    myFile = SD.open("/helloworld.txt", FILE_WRITE);

    // Check if the file exists
    if (SD.exists("/helloworld.txt")) 
    {
      Serial.println("helloworld.txt exists.");
    } 
    else 
    {
      Serial.println("helloworld.txt doesn't exist.");
    }

    // Delete the file and verify deletion
    Serial.println("Removing helloworld.txt...");
    SD.remove("/helloworld.txt");
    if (SD.exists("/helloworld.txt")) 
    {
      Serial.println("helloworld.txt exists.");
    } 
    else 
    {
      Serial.println("helloworld.txt doesn't exist.");
    }
    myFile.close();
    Serial.println("");

    // Open 'test.txt' in write mode
    myFile = SD.open("/test.txt", FILE_WRITE);

    // Check if the file was successfully opened
    if (myFile) 
    {
      Serial.print("Writing to test.txt...");
      myFile.println("testing 1, 2, 3."); // Write sample data to the file
      
      myFile.close(); // Close the file after writing
      Serial.println("done.");
    } 
    else 
    {
      // Print an error if the file couldn't be opened
      Serial.println("error opening test.txt");
    }

    // Re-open the file for reading
    myFile = SD.open("/test.txt");
    if (myFile) 
    {
      Serial.println("test.txt:");
      
      // Read and print file contents until EOF
      while (myFile.available()) 
      {
        Serial.write(myFile.read());
      }
      
      myFile.close(); // Close the file after reading
    } 
    else 
    {
      // Print an error if the file couldn't be opened
      Serial.println("error opening test.txt");
    }
    myFile.close();
  }

  // End the SD card and SPI operations
  SD.end();
  SPI.end();
  Serial.println("INFO: Setup complete");
}

// Main loop - No operations performed here
void loop() 
{
  // Nothing to do here.
}

// Function to print directory contents with indentation for subdirectories
void printDirectory(File dir, int numTabs) 
{
  while (true) 
  {
    File entry = dir.openNextFile(); // Get the next file or directory entry
    if (!entry) 
    {
      break; // Exit loop when no more files are found
    }

    // Print tabs for visual representation of directory depth
    for (uint8_t i = 0; i < numTabs; i++) 
    {
      Serial.print('t');
    }

    Serial.print(entry.name()); // Print the file or directory name
    
    if (entry.isDirectory()) 
    {
      Serial.println("/"); // Indicate a directory
      printDirectory(entry, numTabs + 1); // Recursive call for subdirectories
    } 
    else 
    {
      Serial.print("tt");
      Serial.println(entry.size(), DEC); // Print file size in bytes
    }
    entry.close(); // Close the current file or directory entry
  }
}
