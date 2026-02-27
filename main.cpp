#include <iostream>
#include <string>
#include <stdexcept>

template <typename K, typename V>
class AssociativeArray {
private:
    struct Pair {
        K key;
        V value;
    };

    Pair* data;
    int count;
    int capacity;

    void resize() {
        capacity *= 2;
        Pair* newData = new Pair[capacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    int findIndex(const K& key) const {
        for (int i = 0; i < count; i++) {
            if (data[i].key == key) {
                return i;
            }
        }
        return -1;
    }

public:
    AssociativeArray() : count(0), capacity(4) {
        data = new Pair[capacity];
    }

    AssociativeArray(const AssociativeArray& other) : count(other.count), capacity(other.capacity) {
        data = new Pair[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    AssociativeArray& operator=(const AssociativeArray& other) {
        if (this != &other) {
            delete[] data;
            count = other.count;
            capacity = other.capacity;
            data = new Pair[capacity];
            for (int i = 0; i < count; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~AssociativeArray() {
        delete[] data;
    }

    void insert(const K& key, const V& value) {
        int idx = findIndex(key);
        if (idx != -1) {
            data[idx].value = value;
            return;
        }
        if (count == capacity) {
            resize();
        }
        data[count].key = key;
        data[count].value = value;
        count++;
    }

    V& get(const K& key) {
        int idx = findIndex(key);
        if (idx == -1) {
            throw std::runtime_error("Key not found");
        }
        return data[idx].value;
    }

    const V& get(const K& key) const {
        int idx = findIndex(key);
        if (idx == -1) {
            throw std::runtime_error("Key not found");
        }
        return data[idx].value;
    }

    V& operator[](const K& key) {
        int idx = findIndex(key);
        if (idx == -1) {
            if (count == capacity) {
                resize();
            }
            data[count].key = key;
            data[count].value = V();
            count++;
            return data[count - 1].value;
        }
        return data[idx].value;
    }

    bool remove(const K& key) {
        int idx = findIndex(key);
        if (idx == -1) {
            return false;
        }
        for (int i = idx; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
        return true;
    }

    bool contains(const K& key) const {
        return findIndex(key) != -1;
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    void clear() {
        count = 0;
    }

    void print() const {
        std::cout << "{ ";
        for (int i = 0; i < count; i++) {
            std::cout << data[i].key << ": " << data[i].value;
            if (i < count - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }
};

int main() {
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

    // --- Пример 3: string -> string (конфигурация) ---
    std::cout << "\n=== AssociativeArray<string, string> ===" << std::endl;

    AssociativeArray<std::string, std::string> config;
    config["host"] = "localhost";
    config["port"] = "8080";
    config["mode"] = "debug";

    std::cout << "Config:" << std::endl;
    config.print();

    // Проверка копирования
    AssociativeArray<std::string, std::string> configCopy = config;
    configCopy["port"] = "3000";
    std::cout << "Original after copy modified:" << std::endl;
    config.print();
    std::cout << "Copy:" << std::endl;
    configCopy.print();

    // Проверка очистки
    config.clear();
    std::cout << "After clear, empty: " << (config.empty() ? "yes" : "no") << std::endl;

    // Проверка исключения
    try {
        config.get("nonexistent");
    } catch (const std::runtime_error& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
