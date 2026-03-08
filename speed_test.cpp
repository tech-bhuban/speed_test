
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>

class SpeedTest {
private:
    std::vector<std::string> servers;
    double downloadSpeed;
    double uploadSpeed;
    double ping;
    
    double simulateSpeed(double min, double max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    
public:
    SpeedTest() {
        servers = {"NYC Server", "LA Server", "London Server", 
                   "Tokyo Server", "Sydney Server"};
        downloadSpeed = 0;
        uploadSpeed = 0;
        ping = 0;
    }
    
    void testPing() {
        std::cout << "Testing ping... ";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dis(20, 5);
        ping = std::abs(dis(gen));
        
        std::cout << ping << " ms\n";
    }
    
    void testDownload() {
        std::cout << "Testing download speed...\n";
        std::string progress = "████████░░░░░░░░░░░░";
        
        for(int i = 0; i < 20; i++) {
            std::cout << "\r[" << progress.substr(0, i+1) 
                      << std::string(19-i, '░') << "] " 
                      << (i+1)*5 << "%" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        downloadSpeed = simulateSpeed(50, 200);
        std::cout << "\nDownload: " << std::fixed << std::setprecision(2) 
                  << downloadSpeed << " Mbps\n";
    }
    
    void testUpload() {
        std::cout << "Testing upload speed...\n";
        std::string progress = "████████░░░░░░░░░░░░";
        
        for(int i = 0; i < 20; i++) {
            std::cout << "\r[" << progress.substr(0, i+1) 
                      << std::string(19-i, '░') << "] " 
                      << (i+1)*5 << "%" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        uploadSpeed = simulateSpeed(10, 50);
        std::cout << "\nUpload: " << std::fixed << std::setprecision(2) 
                  << uploadSpeed << " Mbps\n";
    }
    
    void selectServer() {
        std::cout << "\nAvailable servers:\n";
        for(size_t i = 0; i < servers.size(); i++) {
            std::cout << i+1 << ". " << servers[i] << "\n";
        }
        std::cout << "Select server (1-5): ";
        int choice;
        std::cin >> choice;
        std::cout << "Connecting to " << servers[choice-1] << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    void runFullTest() {
        std::cout << "=== NETWORK SPEED TEST ===\n";
        selectServer();
        testPing();
        testDownload();
        testUpload();
        
        std::cout << "\n=== RESULTS ===\n";
        std::cout << "Ping: " << ping << " ms\n";
        std::cout << "Download: " << downloadSpeed << " Mbps\n";
        std::cout << "Upload: " << uploadSpeed << " Mbps\n";
        
        if(ping < 30 && downloadSpeed > 100) {
            std::cout << "Excellent connection! 🚀\n";
        } else if(ping < 50 && downloadSpeed > 50) {
            std::cout << "Good connection 👍\n";
        } else {
            std::cout << "Average connection 📡\n";
        }
    }
};

int main() {
    SpeedTest test;
    test.runFullTest();
    return 0;
}
