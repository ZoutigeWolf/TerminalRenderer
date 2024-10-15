#include <iostream>
#include <opencv2/videoio.hpp>

#include "../lib/AsciiRenderer.h"
#include "../lib/utils.h"

int selectPort() {
    const std::vector<std::tuple<int, std::string>> ports = AsciiRenderer::getPorts();

    for (auto port: ports) {
        std::cout << std::format("{}: {}", std::get<0>(port), std::get<1>(port)) << std::endl;
    }

    const int port = getInput("Select port: ");

    return port;
}

int main() {
    const int port = selectPort();
    const int ratio = getInput("Pixel ratio: ");

    AsciiRenderer renderer(port, ratio);
    renderer.start();

    return 0;
}
