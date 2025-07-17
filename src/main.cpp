#include <iostream>
#include <string>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

class SerialPort {
private:
    int serial_port;
    struct termios tty;
    
public:
    SerialPort(const std::string& port_name) : serial_port(-1) {
        // Open the serial port
        serial_port = open(port_name.c_str(), O_RDWR);
        
        if (serial_port < 0) {
            std::cerr << "Error opening " << port_name << ": " << strerror(errno) << std::endl;
            return;
        }
        
        // Configure the port
        if (tcgetattr(serial_port, &tty) != 0) {
            std::cerr << "Error getting terminal attributes: " << strerror(errno) << std::endl;
            close(serial_port);
            serial_port = -1;
            return;
        }
        
        // Set baud rate to 9600
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);
        
        // Configure 8N1 (8 data bits, no parity, 1 stop bit)
        tty.c_cflag &= ~PARENB;        // No parity
        tty.c_cflag &= ~CSTOPB;        // 1 stop bit
        tty.c_cflag &= ~CSIZE;         // Clear data size bits
        tty.c_cflag |= CS8;            // 8 data bits
        tty.c_cflag &= ~CRTSCTS;       // No hardware flow control
        tty.c_cflag |= CREAD | CLOCAL; // Enable reading and ignore control lines
        
        // Configure input modes
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // No software flow control
        tty.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
        
        // Configure output modes
        tty.c_oflag &= ~OPOST; // Raw output
        
        // Set timeouts
        tty.c_cc[VMIN] = 0;   // Minimum characters to read
        tty.c_cc[VTIME] = 10; // Timeout in deciseconds (1 second)
        
        // Apply the configuration
        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            std::cerr << "Error setting terminal attributes: " << strerror(errno) << std::endl;
            close(serial_port);
            serial_port = -1;
        }
    }
    
    ~SerialPort() {
        if (serial_port >= 0) {
            close(serial_port);
        }
    }
    
    bool isOpen() const {
        return serial_port >= 0;
    }
    
    int writeData(const std::string& data) {
        if (serial_port < 0) return -1;
        return write(serial_port, data.c_str(), data.length());
    }
    
    std::string readData() {
        if (serial_port < 0) return "";
        
        char buffer[256];
        int bytes_read = read(serial_port, buffer, sizeof(buffer) - 1);
        
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            return std::string(buffer);
        }
        
        return "";
    }
};

int main() {
    std::cout << "COM Port Communication Test" << std::endl;
    std::cout << "===========================" << std::endl;
    
    // Initialize serial port
    SerialPort port("/dev/ttyACM0");
    
    if (!port.isOpen()) {
        std::cerr << "Failed to open serial port /dev/ttyACM0" << std::endl;
        return 1;
    }
    
    std::cout << "Serial port opened successfully!" << std::endl;
    std::cout << "Type messages to send (type 'quit' to exit):" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "quit") {
            break;
        }
        
        // Send the message
        input += "\n"; // Add newline
        int bytes_sent = port.writeData(input);
        std::cout << "Sent " << bytes_sent << " bytes" << std::endl;
        
        // Wait a moment for response
        usleep(100000); // 100ms
        
        // Read response (for loopback test)
        std::string response = port.readData();
        if (!response.empty()) {
            std::cout << "Received: " << response;
        }
    }
    
    std::cout << "Exiting..." << std::endl;
    return 0;
}
