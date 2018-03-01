//
// Created by Vincent PICOT on 01/03/2018.
//

#include <iostream>
#include "Map.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "./" << argv[0] << " [entry file]" << std::endl;
        return 1;
    }
    Map map(argv[1]);

    map.parse();
    return 0;
}
