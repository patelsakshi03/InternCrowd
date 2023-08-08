#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

struct Birthday {
    std::string name;
    std::string date;
};

std::vector<Birthday> birthdayList;

bool isValidDate(const std::string& date) {
    std::istringstream dateStream(date);
    int day, month, year;
    char delimiter1, delimiter2;
    dateStream >> day >> delimiter1 >> month >> delimiter2 >> year;

    if (delimiter1 != '/' || delimiter2 != '/' ||
        day < 1 || day > 31 ||
        month < 1 || month > 12 ||
        year < 1900 || year > 2100) {
        return false;
    }

    return true;
}

void addBirthday() {
    Birthday newBirthday;
    std::cout << "Enter name: ";
    std::cin >> newBirthday.name;

    std::string newDate;
    do {
        std::cout << "Enter date (dd/mm/yyyy): ";
        std::cin >> newDate;
        if(!isValidDate(newDate)){
           std::cout << "Please enter vailid date \n";
        }
    } while (!isValidDate(newDate));

    newBirthday.date = newDate;
    birthdayList.push_back(newBirthday);
    std::cout << "Birthday added successfully.\n";
}

void displayBirthdays() {
    if (birthdayList.empty()) {
        std::cout << "No birthdays found.\n";
        return;
    }

    std::cout << "Birthday List:\n";
    for (const auto& birthday : birthdayList) {
        std::cout << birthday.name << ": " << birthday.date << '\n';
    }
}

void searchBirthdayByName() {
    std::string searchName;
    std::cout << "Enter the name to search: ";
    std::cin >> searchName;

    auto it = std::find_if(birthdayList.begin(), birthdayList.end(), 
                           [searchName](const Birthday& b) { return b.name == searchName; });

    if (it != birthdayList.end()) {
        std::cout << "Birthday found:\n";
        std::cout << it->name << ": " << it->date << '\n';
    } else {
        std::cout << "Birthday not found for the given name.\n";
    }
}

void displayMonthlyBirthdays() {
    std::string searchMonth;
    std::cout << "Enter the month (MM): ";
    std::cin >> searchMonth;

    std::cout << "Birthdays in " << searchMonth << ":\n";
    for (const auto& birthday : birthdayList) {
        if (birthday.date.substr(3, 2) == searchMonth) {
            std::cout << birthday.name << ": " << birthday.date << '\n';
        }
    }
}

int main() {
    char choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Birthday\n";
        std::cout << "2. Display All Birthdays\n";
        std::cout << "3. Search Birthday by Name\n";
        std::cout << "4. Display Monthly Birthdays\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                addBirthday();
                break;
            case '2':
                displayBirthdays();
                break;
            case '3':
                searchBirthdayByName();
                break;
            case '4':
                displayMonthlyBirthdays();
                break;
            case '5':
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '5');

    return 0;
}
