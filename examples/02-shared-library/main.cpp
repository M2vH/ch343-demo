#include "../../common/include/serial_port.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

int main() {
    std::cout << "CH343 Shared Library Example" << std::endl;
    std::cout << "============================" << std::endl;
    
    CH343::SerialPort port;
    
    // Try to open the serial port
    if (!port.open("/dev/ttyACM0", 115200)) {
        std::cerr << "Failed to open serial port /dev/ttyACM0" << std::endl;
        return 1;
    }
    
    std::cout << "Serial port opened at 115200 baud!" << std::endl;
    
    // Test configuration changes
    std::cout << "Testing configuration changes..." << std::endl;
    
    // Test different baud rates
    std::vector<int> baudRates = {9600, 19200, 38400, 57600, 115200};
    for (int baud : baudRates) {
        std::cout << "Setting baud rate to: " << baud << std::endl;
        if (port.setBaudRate(baud)) {
            std::cout << "  ✓ Success" << std::endl;
            
            // Send a test message
            std::string testMsg = "Test at " + std::to_string(baud) + " baud\n";
            port.write(testMsg);
            
            // Brief delay
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Try to read response
            std::string response = port.read(1024, 500);
            if (!response.empty()) {
                std::cout << "  Received: " << response;
            }
        } else {
            std::cout << "  ✗ Failed" << std::endl;
        }
    }
    
    // Interactive mode
    std::cout << "\nEntering interactive mode..." << std::endl;
    std::cout << "Type messages to send (type 'quit' to exit):" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "quit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        
        // Send the message
        int bytesSent = port.write(input + "\n");
        if (bytesSent > 0) {
            std::cout << "Sent " << bytesSent << " bytes" << std::endl;
            
            // Try to read response
            std::string response = port.read(1024, 1000);
            if (!response.empty()) {
                std::cout << "Received: " << response;
            }
        } else {
            std::cerr << "Failed to send data" << std::endl;
        }
    }
    
    return 0;
}
