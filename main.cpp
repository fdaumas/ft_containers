#include "vector.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>

int main ()
{
    ft::vector<int> vector_int;
    

    for(size_t index = 0; index != 50; index++)
        vector_int.push_back(index);
    // vector_int.resize(25);
    ft::vector<int>::iterator it = vector_int.begin();
    it += 10;
    vector_int.insert(it, 99999);
    // vector_int.resize(50, 68);
    it = vector_int.begin();
    for(; it != vector_int.end(); it++)
        std::cout << *it << std::endl;
    return 0;
}
