#include <iostream>
#include <memory>

#include "calc/calc.h"
#include "xmlparser/xmlparser.h"

int main(){

    auto calc_sum = std::make_unique<Sum>();
    std::cout << calc_sum->add(1,2) << std::endl;

    auto xmlparser_document = std::make_unique<Document>();
    std::cout << xmlparser_document->parse() << std::endl;

    std::cout << "hello world" << std::endl;

    std::cout << std::endl << "------------------" << std::endl;


    return 0;
}