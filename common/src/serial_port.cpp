#include "serial_port.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstring>
#include <iostream>

namespace CH343 {

SerialPort::SerialPort() : fd_(-1), isOpen_(false) {}

SerialPort::~SerialPort() {
    close();
}

bool SerialPort::open(const std::string& device, int baudRate) {
    if (isOpen_) {
        close();
    }
    
    fd_ = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd_ < 0) {
        std::cerr << "Error opening " << device << ": " << strerror(errno) << std::endl;
        return false;
    }
    
    // Save original configuration
    if (tcgetattr(fd_, &originalConfig_) != 0) {
        std::cerr << "Error getting terminal attributes: " << strerror(errno) << std::endl;
        ::close(fd_);
        fd_ = -1;
        return false;
    }
    
    if (!configurePort(baudRate)) {
        ::close(fd_);
        fd_ = -1;
        return false;
    }
    
    isOpen_ = true;
    return true;
}

void SerialPort::close() {
    if (isOpen_ && fd_ >= 0) {
        // Restore original configuration
        tcsetattr(fd_, TCSANOW, &originalConfig_);
        ::close(fd_);
        fd_ = -1;
        isOpen_ = false;
    }
}

bool SerialPort::isOpen() const {
    return isOpen_;
}

int SerialPort::write(const std::string& data) {
    if (!isOpen_) {
        return -1;
    }
    
    int bytes = ::write(fd_, data.c_str(), data.length());
    if (bytes < 0) {
        std::cerr << "Write error: " << strerror(errno) << std::endl;
    }
    return bytes;
}

std::string SerialPort::read(int maxBytes, int timeoutMs) {
    if (!isOpen_) {
        return "";
    }
    
    fd_set readfds;
    struct timeval timeout;
    
    FD_ZERO(&readfds);
    FD_SET(fd_, &readfds);
    
    timeout.tv_sec = timeoutMs / 1000;
    timeout.tv_usec = (timeoutMs % 1000) * 1000;
    
    int result = select(fd_ + 1, &readfds, nullptr, nullptr, &timeout);
    if (result <= 0) {
        return ""; // Timeout or error
    }
    
    char buffer[maxBytes];
    int bytes = ::read(fd_, buffer, maxBytes - 1);
    if (bytes < 0) {
        std::cerr << "Read error: " << strerror(errno) << std::endl;
        return "";
    }
    
    buffer[bytes] = '\0';
    return std::string(buffer, bytes);
}

bool SerialPort::configurePort(int baudRate) {
    termios config;
    
    if (tcgetattr(fd_, &config) != 0) {
        std::cerr << "Error getting terminal attributes: " << strerror(errno) << std::endl;
        return false;
    }
    
    // Set baud rate
    speed_t speed = getBaudRateConstant(baudRate);
    cfsetispeed(&config, speed);
    cfsetospeed(&config, speed);
    
    // Configure for 8N1 (8 data bits, no parity, 1 stop bit)
    config.c_cflag &= ~PARENB;    // No parity
    config.c_cflag &= ~CSTOPB;    // 1 stop bit
    config.c_cflag &= ~CSIZE;     // Clear data size bits
    config.c_cflag |= CS8;        // 8 data bits
    config.c_cflag &= ~CRTSCTS;   // No hardware flow control
    config.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines
    
    // Configure input modes
    config.c_iflag &= ~(IXON | IXOFF | IXANY); // No software flow control
    config.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    
    // Configure output modes
    config.c_oflag &= ~OPOST; // Raw output
    
    // Configure local modes
    config.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw mode
    
    // Set read timeouts
    config.c_cc[VMIN] = 0;   // Minimum characters to read
    config.c_cc[VTIME] = 10; // Timeout in deciseconds
    
    if (tcsetattr(fd_, TCSANOW, &config) != 0) {
        std::cerr << "Error setting terminal attributes: " << strerror(errno) << std::endl;
        return false;
    }
    
    return true;
}

speed_t SerialPort::getBaudRateConstant(int baudRate) {
    switch (baudRate) {
        case 9600: return B9600;
        case 19200: return B19200;
        case 38400: return B38400;
        case 57600: return B57600;
        case 115200: return B115200;
        case 230400: return B230400;
        case 460800: return B460800;
        case 921600: return B921600;
        default: return B9600;
    }
}

bool SerialPort::setBaudRate(int baudRate) {
    if (!isOpen_) {
        return false;
    }
    
    termios config;
    if (tcgetattr(fd_, &config) != 0) {
        return false;
    }
    
    speed_t speed = getBaudRateConstant(baudRate);
    cfsetispeed(&config, speed);
    cfsetospeed(&config, speed);
    
    return tcsetattr(fd_, TCSANOW, &config) == 0;
}

bool SerialPort::setDataBits(int dataBits) {
    if (!isOpen_) {
        return false;
    }
    
    termios config;
    if (tcgetattr(fd_, &config) != 0) {
        return false;
    }
    
    config.c_cflag &= ~CSIZE;
    switch (dataBits) {
        case 5: config.c_cflag |= CS5; break;
        case 6: config.c_cflag |= CS6; break;
        case 7: config.c_cflag |= CS7; break;
        case 8: config.c_cflag |= CS8; break;
        default: return false;
    }
    
    return tcsetattr(fd_, TCSANOW, &config) == 0;
}

bool SerialPort::setParity(char parity) {
    if (!isOpen_) {
        return false;
    }
    
    termios config;
    if (tcgetattr(fd_, &config) != 0) {
        return false;
    }
    
    switch (parity) {
        case 'N':
        case 'n':
            config.c_cflag &= ~PARENB;
            break;
        case 'E':
        case 'e':
            config.c_cflag |= PARENB;
            config.c_cflag &= ~PARODD;
            break;
        case 'O':
        case 'o':
            config.c_cflag |= PARENB;
            config.c_cflag |= PARODD;
            break;
        default:
            return false;
    }
    
    return tcsetattr(fd_, TCSANOW, &config) == 0;
}

bool SerialPort::setStopBits(int stopBits) {
    if (!isOpen_) {
        return false;
    }
    
    termios config;
    if (tcgetattr(fd_, &config) != 0) {
        return false;
    }
    
    switch (stopBits) {
        case 1:
            config.c_cflag &= ~CSTOPB;
            break;
        case 2:
            config.c_cflag |= CSTOPB;
            break;
        default:
            return false;
    }
    
    return tcsetattr(fd_, TCSANOW, &config) == 0;
}

bool SerialPort::setFlowControl(bool enable) {
    if (!isOpen_) {
        return false;
    }
    
    termios config;
    if (tcgetattr(fd_, &config) != 0) {
        return false;
    }
    
    if (enable) {
        config.c_cflag |= CRTSCTS;
    } else {
        config.c_cflag &= ~CRTSCTS;
    }
    
    return tcsetattr(fd_, TCSANOW, &config) == 0;
}

} // namespace CH343
