#pragma once

#include <string>
#include <termios.h>

namespace CH343 {

class SerialPort {
public:
    SerialPort();
    ~SerialPort();
    
    bool open(const std::string& device, int baudRate = 9600);
    void close();
    bool isOpen() const;
    
    int write(const std::string& data);
    std::string read(int maxBytes = 1024, int timeoutMs = 1000);
    
    // Configuration methods
    bool setBaudRate(int baudRate);
    bool setDataBits(int dataBits);
    bool setParity(char parity); // 'N', 'E', 'O'
    bool setStopBits(int stopBits);
    bool setFlowControl(bool enable);
    
private:
    int fd_;
    bool isOpen_;
    termios originalConfig_;
    
    bool configurePort(int baudRate);
    speed_t getBaudRateConstant(int baudRate);
};

} // namespace CH343
