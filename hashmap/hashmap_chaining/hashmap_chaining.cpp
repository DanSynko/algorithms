#include <iostream>
#include <utility>
//#include "algorithms_timer.h"

template<typename Key, typename Val>
class Hashmap {
private:
    struct Bucket {
        Key key;
        Val value;
        Bucket* next;
        size_t hash_code;
    };
    Bucket** buckets;
    size_t hm_size;
    size_t hm_capacity;



    size_t hash_function(Key bucket_key) {
        std::hash<Key> hash;
        return hash(bucket_key) % hm_capacity;
    }



    void rehashing() {
        Bucket** old_buckets = buckets;
        size_t old_capacity = hm_capacity;

        hm_capacity *= 1.5;
        buckets = new Bucket*[hm_capacity]();

        for (size_t i = 0; i < old_capacity; i++) {
            Bucket* current = old_buckets[i];

            while (current != nullptr) {
                Bucket* next_node = current->next;
                current->next = nullptr;

                size_t new_index = hash_function(current->key);
                current->hash_code = new_index;

                if (buckets[new_index] == nullptr) {
                    buckets[new_index] = current;
                }
                else {
                    Bucket* tail = buckets[new_index];
                    while (tail->next != nullptr) {
                        tail = tail->next;
                    }
                    tail->next = current;
                }
                current = next_node;
            }
        }
        delete[] old_buckets;
    }

    Bucket* check_dublication(const Key& arg_key) {
        Bucket* current = buckets[hash_function(arg_key)];
        while (current != nullptr) {
            if (current->key == arg_key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
public:
    Hashmap() : hm_capacity(3), hm_size(0) {
        buckets = new Bucket*[hm_capacity]();
    }
    Hashmap(std::initializer_list<std::pair<Key, Val>> hm) : hm_capacity(3), hm_size(0) {
        buckets = new Bucket*[hm_capacity]();
        for (const auto& [key, val] : hm) {
            insert(key, val);
        }
    }
    ~Hashmap() {
        Bucket* current_for_next = nullptr;
        for (int i = 0; i < hm_capacity; i++) {
            for (Bucket* current = buckets[i]; current != nullptr; current = current_for_next) {
                current_for_next = current->next;
                delete current;
            }
        }
        delete[] buckets;
        hm_capacity = 0;
        hm_size = 0;
    }

    // Time Complexity: 
    // insert, search, remove: O(1) Average, O(N) Worst

    void insert(const Key& arg_key, const Val& arg_val) {
        if (hm_capacity <= hm_size) {
            rehashing();
        }

        Bucket* dublicat = check_dublication(arg_key);
        if (dublicat != nullptr) {
            dublicat->value = arg_val;
        }
        else {
            size_t i = hash_function(arg_key);
            Bucket* newBucket = new Bucket{ arg_key, arg_val, buckets[i], i };
            buckets[i] = newBucket;
            hm_size++;
        }
    }
    void remove() {

    }
    Bucket* search(const Key& arg_key) {
        Bucket* current = buckets[hash_function(arg_key)];
        while (current != nullptr) {
            if (current->key == arg_key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main()
{
    std::cout << "There is an example of hashmap with chaining." << std::endl;
    Hashmap<std::string, std::string> hashmap = {
        {"Car", "BMW"},
        {"Word", "C++"},
        {"Rac", "Volkswagen"}
    };

    std::cout << "hashmap.insert('Website', 'GitHub');" << std::endl;
    hashmap.insert("Website", "GitHub");
    std::cout << "hashmap.insert('Website', 'Google');  (create a dublicat)" << std::endl;
    hashmap.insert("Website", "Google");
    std::cout << "hashmap.insert('Cra', 'Toyota');  (create a collision)" << std::endl;
    hashmap.insert("Cra", "Toyota");
    std::cout << "hashmap.insert('Cra', 'Toyota');  (create a collision)" << std::endl;
    hashmap.insert("Cra", "Toyota");
    std::cout << "hashmap.search('Cra'); " << std::endl;
    std::cout << "Address of this key: " << hashmap.search("Cra") << ". " << std::endl;
    return 0;
}