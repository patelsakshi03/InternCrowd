#include <iostream>
#include <map>
#include <string>
#include <vector>

// Voter registration data
std::map<std::string, std::string> voters = {
    {"vardan", "123"},
    {"sakshi", "234"},
    {"ram", "111"},
    {"shyam", "345"},
    {"kalicharan", "333"}
};

// Candidate structure
struct Candidate {
    std::string name;
    int votes = 0;
};
std::vector<Candidate> candidates = {
    {"modi", 0},
    {"rahul", 0}
};

int main() {
    while (true) {
        int choice;
        std::cout << "------------------\n";
        std::cout << "1. Login as Voter\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Exit\n";
        std::cout << "------------------\n";
        std::cout << "Enter your choice (1-5): ";
        
        std::cin >> choice;
        
        if (choice == 1) { // Voter Login
            std::string username, password;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;
            
            if (voters.find(username) != voters.end() && voters[username] == password) {
                std::cout << "Login successful!\n";
                std::cout << "Select a candidate:\n";
                for (size_t i = 0; i < candidates.size(); ++i) {
                    std::cout << i + 1 << ". " << candidates[i].name << "\n";
                }
                
                int candidateChoice;
                std::cin >> candidateChoice;
                
                if (candidateChoice >= 1 && candidateChoice <= candidates.size()) {
                    candidates[candidateChoice - 1].votes++;
                    std::cout << "Vote for " << candidates[candidateChoice - 1].name << " registered.\n";
                } else {
                    std::cout << "Invalid candidate choice.\n";
                }
            } else {
                std::cout << "Invalid username or password.\n";
            }
        } else if (choice == 2) { // Admin Login
            std::string adminUsername = "admin";
            std::string adminPassword = "adminpass";
            
            std::string username, password;
            std::cout << "Enter admin username: ";
            std::cin >> username;
            std::cout << "Enter admin password: ";
            std::cin >> password;
            
            if (username == adminUsername && password == adminPassword) {
                std::cout << "Admin login successful!\n";
                std::cout << "Candidate Votes:\n";
                for (const Candidate& candidate : candidates) {
                    std::cout << candidate.name << ": " << candidate.votes << " votes\n";
                }
            } else {
                std::cout << "Invalid admin username or password.\n";
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Please select again.\n";
        }
    }
    
    return 0;
}
