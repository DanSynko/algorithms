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
        hm_capacity *= 1.5;
        Bucket** new_hm = new Bucket*[hm_capacity]();
        Bucket* current_for_next = nullptr;
        for (int i = 0; i < hm_capacity; i++) {
            for (Bucket* current = buckets[i]; current != nullptr; current = current_for_next) {
                current_for_next = current->next;
                delete current;
            }
        }
        
        buckets = new_hm;
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
    Hashmap() : hm_capacity(32), hm_size(0) {
        buckets = new Bucket*[hm_capacity]();
    }
    Hashmap(std::initializer_list<std::pair<Key, Val>> hm) : hm_capacity(32), hm_size(0) {
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

    void insert(const Key& arg_key, const Val& arg_val) {
        Bucket* newBucket = new Bucket{ arg_key, arg_val, nullptr, hash_function(arg_key) };

        /*if (hm_capacity <= hm_size) {
            rehashing();
        }*/

        Bucket* dublicat = check_dublication(arg_key);
        if (dublicat != nullptr) {
            dublicat->value = newBucket->value;
            delete newBucket;
        }
        else {
            if (buckets[newBucket->hash_code] == nullptr) {
                buckets[newBucket->hash_code] = newBucket;
            }
            else {
                Bucket* current = buckets[newBucket->hash_code];
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newBucket;
                hm_size++;
            }
        }
    }
    void remove() {

    }
    void search() {

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
    std::cout << "hashmap.insert('Website', 'Google');  (create a collision)" << std::endl;
    hashmap.insert("Cra", "Toyota");
    return 0;
}