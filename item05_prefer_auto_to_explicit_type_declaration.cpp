//
// Created by marcin on 15.01.17.
//

#include <iostream>
#include <functional>
#include <unordered_map>
#include "item05_prefer_auto_to_explicit_type_declaration.h"

void item5_prefer_auto_to_explicit_type_declaration::run() {

    auto fn = []() {std::cout << "\nInside closudre\n";};
    fn();

    std::function<void()> fn2 = []() { std::cout << "inside function closure\n"; };
    fn2();

    // auto captured closure takse only 1 byte
    std::cout << "sizeof fn : " << sizeof(fn) << "\n";

    // std::function capture closure takes 32 bytes, and might allocate heap memory.
    std::cout << "sizeof fn2 : " << sizeof(fn2) << "\n";

    std::unordered_map<std::string, std::string> amap {{"a", "b"}, {"c", "d"}};
    using map_type = std::unordered_map<std::string, std::string>;
    for (std::pair<const std::string,std::string>& key : amap) {
        std::cout << key.first << " : " << key.second << "\n";
    }
}
