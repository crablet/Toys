#include <opencv2/opencv.hpp>

void Dummy(int, void*)
{
}

int main()
{
    auto Src = cv::imread("In.jpg");

    int LowH = 0, LowS = 0, LowV = 0;
    int HighH = 180, HighS = 255, HighV = 255;

    const cv::String ResultWindowName = "Result";
    cv::namedWindow(ResultWindowName);
    cv::createTrackbar("LowH", ResultWindowName, &LowH, 180, Dummy);
    cv::createTrackbar("HighH", ResultWindowName, &HighH, 180, Dummy);
    cv::createTrackbar("LowS", ResultWindowName, &LowS, 255, Dummy);
    cv::createTrackbar("HighS", ResultWindowName, &HighS, 255, Dummy);
    cv::createTrackbar("LowV", ResultWindowName, &LowV, 255, Dummy);
    cv::createTrackbar("HighV", ResultWindowName, &HighV, 255, Dummy);

    cv::cvtColor(Src, Src, cv::COLOR_BGR2HSV);
    while (true)
    {
        cv::Mat Result;
        cv::inRange(Src, cv::Scalar(LowH, LowS, LowV), cv::Scalar(HighH, HighS, HighV), Result);
        cv::imshow(ResultWindowName, Result);

        cv::waitKey(10);
    }

    return 0;
}