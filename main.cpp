#include "securityservice.h"
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

string toUpper(string str) {
    for (char& c : str) {
        c = toupper(static_cast<unsigned char>(c));
    }
    return str;
}

int readInt() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int value;
    ss >> value;
    return value;
}

void displayRules(const vector<Rule>& rules) {
    if (rules.empty()) {
        cout << "No rules found" << endl;
        return;
    }
    
    cout << "\nRules list:" << endl;
    for (const auto& rule : rules) {
        cout << "ID: " << rule.id 
             << ", Pattern: " << rule.pattern 
             << ", Action: " << rule.action 
             << ", Priority: " << rule.priority << endl;
    }
}

int main() {
    RuleRepository repository;
    SecurityService service(repository);
    
    repository.save("192.168.1.*", "ALLOW", 10);
    repository.save("10.0.0.1", "DENY", 5);
    
    while (true) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Add rule" << endl;
        cout << "2. Show all rules" << endl;
        cout << "3. Delete rule" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            string pattern, action;
            int priority;
            
            cout << "Pattern (IP or subnet): ";
            getline(cin, pattern);
            
            cout << "Action (ALLOW/DENY/CHALLENGE): ";
            getline(cin, action);
            action = toUpper(action);
            
            cout << "Priority (1-100): ";
            priority = readInt();
            
            auto newRule = service.createRule(pattern, action, priority);
            
            if (newRule) {
                cout << "Rule created! ID: " << newRule->id << endl;
            } else {
                cout << "Error creating rule" << endl;
            }
        }
        else if (choice == "2") {
            auto rules = service.getAllRules();
            displayRules(rules);
        }
        else if (choice == "3") {
            cout << "Enter ID to delete: ";
            int id = readInt();
            
            if (service.deleteRule(id)) {
                cout << "Rule " << id << " deleted" << endl;
            } else {
                cout << "Delete failed" << endl;
            }
        }
        else if (choice == "4") {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
    
    return 0;
}
