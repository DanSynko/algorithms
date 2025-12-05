#include <iostream>
//#include "algorithms_timer.h"

template<typename Key, typename Val>
class Hashmap {
private:
public:
    Hashmap() {}
    Hashmap(std::initializer_list<std::pair<Key, Val>> hm) {}
    ~Hashmap() {}
};

int main()
{
    std::cout << "There is an example of hashmap." << std::endl;

    return 0;
}