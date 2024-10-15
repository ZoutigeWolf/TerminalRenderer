#include "opencv2/opencv.hpp"

#include "AsciiRenderer.h"

#include "utils.h"

AsciiRenderer::AsciiRenderer(const int port, const int pixel_ratio) {
    this->port = port;
    this->pixel_ratio = pixel_ratio;
    this->chars = " .,:-=+*#%@";

    init();
}

void AsciiRenderer::init() {
    this->capture = cv::VideoCapture(port);
}

char AsciiRenderer::lumToChar(const uchar lum) const {
    const int index = map(lum, 0, 255, 0, static_cast<int>(this->chars.length()) - 1);
    return this->chars[index];
}


RenderedFrame AsciiRenderer::renderFrame(cv::Mat frame) const {
    if (!this->capture.has_value()) {
        throw std::runtime_error("Capture is not initialized");
    }

    RenderedFrame res {};

    for (int y = 0; y < capture.value().get(cv::CAP_PROP_FRAME_HEIGHT); y += this->pixel_ratio) {
        std::vector<char> line{};

        for (int x = 0; x < capture.value().get(cv::CAP_PROP_FRAME_WIDTH); x += pixel_ratio) {
            const uchar i = frame.at<char>(y, x);

            line.emplace_back(lumToChar(i));
        }

        res.emplace_back(line);
    }

    return res;
}

void AsciiRenderer::displayFrame(const RenderedFrame &frame) {
    clr();

    for (auto line: frame) {
        std::cout << std::string(line.begin(), line.end()) << std::endl;
    }
}


[[noreturn]] void AsciiRenderer::start() {
   if (!this->capture.has_value()) {
       throw std::runtime_error("Capture is not initialized");
   }

    cv::Mat frame;
    cv::Mat grayFrame;

    while (true) {
        this->capture.value() >> frame;

        cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        const RenderedFrame r_frame = renderFrame(grayFrame);

        displayFrame(r_frame);
    }
}

std::vector<std::tuple<int, std::string>> AsciiRenderer::getPorts() {
    int curr_port = 0;
    std::vector<std::tuple<int, std::string>> ports{};

    cv::VideoCapture capture;
    cv::Mat frame;

    while (curr_port <= 10) {
        try {
            capture.open(curr_port);

            capture.read(frame);

            if (frame.empty()) {
                curr_port++;
                continue;
            }

            double w = capture.get(cv::CAP_PROP_FRAME_WIDTH);
            double h = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
            double fps = capture.get(cv::CAP_PROP_FPS);

            ports.emplace_back(curr_port, std::format("{}x{} - {} fps", w, h, fps));

            curr_port++;
        } catch (...) {
            break;
        }
    }

    return ports;
}
