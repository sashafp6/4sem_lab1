#ifndef RULE_H
#define RULE_H

#include <string>

using namespace std;

struct Rule {
    int id;
    string pattern;
    string action;
    int priority;
    
    Rule() : id(0), priority(0) {}
    
    Rule(int id, const string& pattern, const string& action, int priority)
        : id(id), pattern(pattern), action(action), priority(priority) {}
};

#endif
