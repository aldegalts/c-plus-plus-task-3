#include <iostream>
#include <string>
#include <windows.h>
#include "AssociativeArray.h"

void demoPhonebook() {
    std::cout << "=== Ассоциативный массив <int, string> ===" << std::endl;

    AssociativeArray<int, std::string> phonebook;

    phonebook.insert(1, "Alice");
    phonebook.insert(2, "Bob");
    phonebook.insert(3, "Charlie");

    std::cout << "После вставки:" << std::endl;
    phonebook.print();

    std::cout << "Получение ключа 2: " << phonebook.get(2) << std::endl;

    phonebook[4] = "Diana";
    std::cout << "После operator[] для ключа 4:" << std::endl;
    phonebook.print();

    phonebook.insert(2, "Boris");
    std::cout << "После обновления ключа 2:" << std::endl;
    phonebook.print();

    std::cout << "Содержит ключ 3: " << (phonebook.contains(3) ? "да" : "нет") << std::endl;
    std::cout << "Содержит ключ 10: " << (phonebook.contains(10) ? "да" : "нет") << std::endl;

    phonebook.remove(1);
    std::cout << "После удаления ключа 1:" << std::endl;
    phonebook.print();

    std::cout << "Размер: " << phonebook.size() << std::endl;
}

void demoWordCount() {
    std::cout << "\n=== Ассоциативный массив <string, int> ===" << std::endl;

    AssociativeArray<std::string, int> wordCount;

    std::string words[] = {"hello", "world", "hello", "c++", "world", "hello"};
    for (const auto& w : words) {
        if (wordCount.contains(w)) {
            wordCount[w]++;
        } else {
            wordCount.insert(w, 1);
        }
    }

    std::cout << "Частота слов:" << std::endl;
    wordCount.print();

    std::cout << "\"hello\" встречается " << wordCount.get("hello") << " раз" << std::endl;

    wordCount.remove("c++");
    std::cout << "После удаления \"c++\":" << std::endl;
    wordCount.print();
}

void demoConfig() {
    std::cout << "\n=== Ассоциативный массив <string, string> ===" << std::endl;

    AssociativeArray<std::string, std::string> config;
    config["host"] = "localhost";
    config["port"] = "8080";
    config["mode"] = "debug";

    std::cout << "Конфигурация:" << std::endl;
    config.print();

    AssociativeArray<std::string, std::string> configCopy = config;
    configCopy["port"] = "3000";
    std::cout << "Оригинал после изменения копии:" << std::endl;
    config.print();
    std::cout << "Копия:" << std::endl;
    configCopy.print();

    config.clear();
    std::cout << "После очистки, пуст: " << (config.empty() ? "да" : "нет") << std::endl;

    try {
        config.get("nonexistent");
    } catch (const std::runtime_error& e) {
        std::cout << "Исключение поймано: " << e.what() << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(65001);

    demoPhonebook();
    demoWordCount();
    demoConfig();

    return 0;
}
