#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
};

bool isValidPhoneNumber(const string &phoneNumber) {
    return (phoneNumber.length() >= 10) || (phoneNumber[0] == '+');
}

void addNewContact(fstream &file) {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact.name);
    
    do {
        cout << "Enter phone number: ";
        cin >> newContact.phoneNumber;
        if (!isValidPhoneNumber(newContact.phoneNumber)) {
            cout << "Invalid phone number. Please enter a valid phone number." << endl;
        }
    } while (!isValidPhoneNumber(newContact.phoneNumber));
    
    file << newContact.name << "," << newContact.phoneNumber << endl;
    cout << "Contact added successfully!" << endl;
}

void searchContact(fstream &file) {
    string searchName;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, searchName);
    
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        string name = line.substr(0, pos);
        if (name == searchName) {
            found = true;
            cout << "Contact found: " << line << endl;
            break;
        }
    }
    
    if (!found) {
        cout << "Contact not found." << endl;
    }
}

void listAllContacts(fstream &file) {
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void modifyContact(fstream &file) {
    string searchName;
    cout << "Enter name to modify: ";
    cin.ignore();
    getline(cin, searchName);
    
    fstream tempFile("temp.txt", ios::out);
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        size_t pos = line.find(',');
        string name = line.substr(0, pos);
        
        if (name == searchName) {
            found = true;
            Contact modifiedContact;
            modifiedContact.name = name;
            
            cout << "Enter new phone number: ";
            cin >> modifiedContact.phoneNumber;
            
            if (isValidPhoneNumber(modifiedContact.phoneNumber)) {
                tempFile << modifiedContact.name << "," << modifiedContact.phoneNumber << endl;
                cout << "Contact modified successfully!" << endl;
            } else {
                cout << "Invalid phone number. Contact modification failed." << endl;
                tempFile << line << endl;
            }
        } else {
            tempFile << line << endl;
        }
    }
    
    if (!found) {
        cout << "Contact not found for modification." << endl;
    }
    
    file.close();
    tempFile.close();
    
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");
}

void deleteContact(fstream &file) {
    string searchName;
    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, searchName);
    
    fstream tempFile("temp.txt", ios::out);
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        size_t pos = line.find(',');
        string name = line.substr(0, pos);
        
        if (name == searchName) {
            found = true;
            cout << "Contact deleted: " << line << endl;
        } else {
            tempFile << line << endl;
        }
    }
    
    if (!found) {
        cout << "Contact not found for deletion." << endl;
    }
    
    file.close();
    tempFile.close();
    
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");
}

int main() {
    fstream file("phonebook.txt", ios::in | ios::out | ios::app);
    
    int choice;
    do {
        cout << "\nPhone Book Menu:\n";
        cout << "1. Add New\n";
        cout << "2. Search\n";
        cout << "3. List all\n";
        cout << "4. Modify\n";
        cout << "5. Delete\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addNewContact(file);
                break;
            case 2:
                searchContact(file);
                break;
            case 3:
                listAllContacts(file);
                break;
            case 4:
                modifyContact(file);
                break;
            case 5:
                deleteContact(file);
                break;
            case 6:
                cout << "Exiting Phone Book. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (choice != 6);
    
    file.close();
    
    return 0;
}
