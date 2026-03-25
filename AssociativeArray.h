#ifndef ASSOCIATIVEARRAY_H
#define ASSOCIATIVEARRAY_H

#include <iostream>
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

#endif
