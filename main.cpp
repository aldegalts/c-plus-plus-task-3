#include <iostream>
#include <string>
#include "AssociativeArray.h"

void demoPhonebook() {
    std::cout << "=== AssociativeArray<int, string> ===" << std::endl;

    AssociativeArray<int, std::string> phonebook;

    phonebook.insert(1, "Alice");
    phonebook.insert(2, "Bob");
    phonebook.insert(3, "Charlie");

    std::cout << "After insert:" << std::endl;
    phonebook.print();

    std::cout << "Get key 2: " << phonebook.get(2) << std::endl;

    phonebook[4] = "Diana";
    std::cout << "After operator[] for key 4:" << std::endl;
    phonebook.print();

    phonebook.insert(2, "Boris");
    std::cout << "After updating key 2:" << std::endl;
    phonebook.print();

    std::cout << "Contains key 3: " << (phonebook.contains(3) ? "yes" : "no") << std::endl;
    std::cout << "Contains key 10: " << (phonebook.contains(10) ? "yes" : "no") << std::endl;

    phonebook.remove(1);
    std::cout << "After removing key 1:" << std::endl;
    phonebook.print();

    std::cout << "Size: " << phonebook.size() << std::endl;
}

void demoWordCount() {
    std::cout << "\n=== AssociativeArray<string, int> ===" << std::endl;

    AssociativeArray<std::string, int> wordCount;

    std::string words[] = {"hello", "world", "hello", "c++", "world", "hello"};
    for (const auto& w : words) {
        if (wordCount.contains(w)) {
            wordCount[w]++;
        } else {
            wordCount.insert(w, 1);
        }
    }

    std::cout << "Word counts:" << std::endl;
    wordCount.print();

    std::cout << "\"hello\" appears " << wordCount.get("hello") << " times" << std::endl;

    wordCount.remove("c++");
    std::cout << "After removing \"c++\":" << std::endl;
    wordCount.print();
}

void demoConfig() {
    std::cout << "\n=== AssociativeArray<string, string> ===" << std::endl;

    AssociativeArray<std::string, std::string> config;
    config["host"] = "localhost";
    config["port"] = "8080";
    config["mode"] = "debug";

    std::cout << "Config:" << std::endl;
    config.print();

    AssociativeArray<std::string, std::string> configCopy = config;
    configCopy["port"] = "3000";
    std::cout << "Original after copy modified:" << std::endl;
    config.print();
    std::cout << "Copy:" << std::endl;
    configCopy.print();

    config.clear();
    std::cout << "After clear, empty: " << (config.empty() ? "yes" : "no") << std::endl;

    try {
        config.get("nonexistent");
    } catch (const std::runtime_error& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    demoPhonebook();
    demoWordCount();
    demoConfig();

    return 0;
}
