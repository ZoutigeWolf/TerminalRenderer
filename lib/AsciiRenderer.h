#ifndef ASCIIRENDERER_H
#define ASCIIRENDERER_H


using RenderedFrame = std::vector<std::vector<char>>;

class AsciiRenderer {
private:
    int port = 0;
    int pixel_ratio = 1;
    std::string chars;
    std::optional<cv::VideoCapture> capture;

    void init();
    [[nodiscard]] char lumToChar(uchar lum) const;
    [[nodiscard]] RenderedFrame renderFrame(cv::Mat frame) const;
    static void displayFrame(const RenderedFrame& frame);

public:
    explicit AsciiRenderer(int port, int pixel_ratio);
    [[noreturn]] void start();
    static std::vector<std::tuple<int, std::string>> getPorts();
};


#endif // ASCIIRENDERER_H
