#ifndef RULEREPOSITORY_H
#define RULEREPOSITORY_H

#include "rule.h"
#include <vector>
#include <algorithm>
#include <optional>

using namespace std;

class RuleRepository {
private:
    vector<Rule> storage;
    int nextId;
    
public:
    RuleRepository() : nextId(1) {}
    
    Rule save(const string& pattern, const string& action, int priority) {
        Rule rule(nextId++, pattern, action, priority);
        storage.push_back(rule);
        return rule;
    }
    
    vector<Rule> findAll() const {
        return storage;
    }
    
    optional<Rule> findById(int id) const {
        auto it = find_if(storage.begin(), storage.end(),
            [id](const Rule& r) { return r.id == id; });
        
        if (it != storage.end()) {
            return *it;
        }
        return nullopt;
    }
    
    bool existsByPattern(const string& pattern) const {
        return any_of(storage.begin(), storage.end(),
            [&pattern](const Rule& r) { return r.pattern == pattern; });
    }
    
    bool deleteById(int id) {
        auto it = remove_if(storage.begin(), storage.end(),
            [id](const Rule& r) { return r.id == id; });
        
        if (it != storage.end()) {
            storage.erase(it, storage.end());
            return true;
        }
        return false;
    }
};

#endif
