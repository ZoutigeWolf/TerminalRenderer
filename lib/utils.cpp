#include "utils.h"

#include <iostream>

void clr() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

int getInput(const std::string &s) {
    int n;

    std::cout << s;
    std::cin >> n;

    return n;
}

int map(const int v, const int a1, const int b1, const int a2, const int b2) {
    return a2 + (v - a1) * (b2 - a2) / (b1 - a1);
}
