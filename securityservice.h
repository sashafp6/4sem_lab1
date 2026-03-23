#ifndef SECURITYSERVICE_H
#define SECURITYSERVICE_H

#include "rulerepository.h"
#include <iostream>
#include <memory>

using namespace std;

class SecurityService {
private:
    RuleRepository& repository;
    
    bool isValidAction(const string& action) const {
        return action == "ALLOW" || action == "DENY" || action == "CHALLENGE";
    }
    
    bool isValidPriority(int priority) const {
        return priority >= 1 && priority <= 100;
    }
    
public:
    explicit SecurityService(RuleRepository& repo) : repository(repo) {}
    
    unique_ptr<Rule> createRule(const string& pattern, const string& action, int priority) {
        if (!isValidAction(action)) {
            cerr << "Ошибка: действие должно быть ALLOW, DENY или CHALLENGE" << endl;
            return nullptr;
        }
        
        if (!isValidPriority(priority)) {
            cerr << "Ошибка: приоритет должен быть от 1 до 100" << endl;
            return nullptr;
        }
        
        if (repository.existsByPattern(pattern)) {
            cerr << "Ошибка: правило с паттерном '" << pattern << "' уже существует" << endl;
            return nullptr;
        }
        
        if (action == "DENY" && pattern == "127.0.0.1") {
            cerr << "Ошибка: нельзя заблокировать localhost" << endl;
            return nullptr;
        }
        
        Rule saved = repository.save(pattern, action, priority);
        return make_unique<Rule>(saved);
    }
    
    vector<Rule> getAllRules() const {
        return repository.findAll();
    }
    
    bool deleteRule(int id) {
        auto rule = repository.findById(id);
        if (!rule) {
            cerr << "Ошибка: правило с ID " << id << " не найдено" << endl;
            return false;
        }
        
        if (rule->priority == 1) {
            cerr << "Ошибка: нельзя удалить системное правило (приоритет 1)" << endl;
            return false;
        }
        
        return repository.deleteById(id);
    }
};

#endif
