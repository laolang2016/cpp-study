#include <iostream>
#include <memory>

#include "person.h"


int main(){
    auto person = std::make_unique<Person>();
    std::cout << person->sayHello() << std::endl;
    return 0;
}
