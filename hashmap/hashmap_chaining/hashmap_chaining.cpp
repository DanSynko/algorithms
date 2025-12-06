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
        
    }
public:
    Hashmap() : hm_capacity(32), hm_size(0) {
        buckets = new Bucket*[hm_capacity]();
    }
    Hashmap(std::initializer_list<std::pair<Key, Val>> hm) : hm_capacity(32), hm_size(0) {
        buckets = new Bucket*[hm_capacity]();
        for (const auto& [key, val] : hm) {
            Bucket* newBucket = new Bucket{ key, val, nullptr };
            size_t rand_index = hash_function(key);

            if (buckets[rand_index] != nullptr) {
                Bucket* current = buckets[rand_index];
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newBucket;
            }
            else {
                buckets[rand_index] = newBucket;
            }
            newBucket->hash_code = rand_index;
            hm_size++;
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

    void insert(Bucket* newBucket) {

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
        {"Car", "Volkswagen"}
    };

    return 0;
}