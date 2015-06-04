

#include "main.h"

using namespace maze;


int main(int argc, char** argv) {
    LineLoop loop;
    loop.emplace_back(0, 0);
    loop.emplace_back(2, 3);
    loop.emplace_back(4, 0);
    std::cout << loop << std::endl;
    loop.split(0, 1);
    std::cout << loop << std::endl;
    loop.merge(0, 1);
    std::cout << loop << std::endl;
    system("pause");
    return 0;
}
