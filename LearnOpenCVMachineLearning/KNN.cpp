// 参考资料：（建议先阅读此处）
// https://blog.csdn.net/chaipp0607/article/details/77966888
// https://stackoverflow.com/questions/28035484/opencv-3-knn-implementation
#include <iostream>
#include <string>
#include <opencv2/ml.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


void Init()
{
    std::cout << "Init..." << std::endl;

    // 我们使用的训练样本是OpenCV自带的一张图，在\opencv\sources\samples\data目录下
    // 我把这张图拷贝到我的桌面上了，大家可以自行修改路径
    auto Img = cv::imread(R"(C:\Users\Crablet\Desktop\digits.png)");
    decltype(Img) Gray;
    cv::cvtColor(Img, Gray, CV_BGR2GRAY);

    constexpr auto b = 20;
    const auto m = Gray.rows / b, n = Gray.cols / b;
    auto FileName = 0, FileNum = 0;
    for (int i = 0; i < m; ++i)
    {
        if (i % 5 == 0 && i != 0)
        {
            ++FileName;
            FileNum = 0;
        }

        const auto OffsetRow = i * b;
        for (int j = 0; j < n; ++j)
        {
            const auto OffsetCol = j * b;
            const auto Address
                = R"(C:\Users\Crablet\Desktop\Out\)"
                + std::to_string(FileName)
                + std::to_string(FileNum++)
                + R"(.jpg)";
            decltype(Gray) Tmp;
            Gray(cv::Range(OffsetRow, OffsetRow + b), cv::Range(OffsetCol, OffsetCol + b))
                .copyTo(Tmp);
            cv::imwrite(Address, Tmp);
        }
    }

    std::cout << "Init done.\n" << std::endl;
}

void TrainAndPredict(int k)
{
    std::cout << "Training..." << std::endl;

    cv::Mat TrainData, TrainLabel;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 400; ++j)
        {
            const auto Address
                = R"(C:\Users\Crablet\Desktop\Out\)"
                + std::to_string(i)
                + std::to_string(j)
                + R"(.jpg)";
            const auto Src = cv::imread(Address).reshape(1, 1);
            TrainData.push_back(Src);
            TrainLabel.push_back(i);
        }
    }
    TrainData.convertTo(TrainData, CV_32F);

    // 这是新版OpenCV的接口，网上很多资料都旧了，所以我就写一篇文章介绍一下新版接口的用法
    // 建议先阅读“参考资料”中的内容
    auto KNN = cv::ml::KNearest::create();
    KNN->setDefaultK(k);
    KNN->setIsClassifier(true);
    KNN->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
    KNN->train(TrainData, cv::ml::ROW_SAMPLE, TrainLabel);

    std::cout << "Predicting..." << std::endl;

    auto TestNum = 0, TrueNum = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 400; j < 500; ++j)
        {
            ++TestNum;

            const auto Address
                = R"(C:\Users\Crablet\Desktop\Out\)"
                + std::to_string(i)
                + std::to_string(j)
                + R"(.jpg)";
            auto TestData = cv::imread(Address).reshape(1, 1);
            TestData.convertTo(TestData, CV_32F);

            // 这个Dummy只是为了占个位，我们并不需要它的内容，因为我们只想读取KNN->findNearest的返回值而已
            // 注意：“auto Response = KNN->findNearest(TestData, KNN->getDefaultK(), cv::Mat());”这样写是不行的
            // 所以我们才需要这个Dummy
            cv::Mat Dummy;
            auto Response = KNN->findNearest(TestData, KNN->getDefaultK(), Dummy);
            if (static_cast<int>(Response) == i)
            {
                ++TrueNum;
            }
        }
    }

    std::cout << "K: " << k << std::endl;
    std::cout << "TrueNum: " << TrueNum << std::endl;
    std::cout << "TestNum: " << TestNum << std::endl;
    std::cout << "Result: " << 1.0 * TrueNum / TestNum << std::endl;
    std::cout << std::endl;
}

int main()
{
    Init();

    for (int i = 1; i <= 10; ++i)
    {
        TrainAndPredict(i);
    }

    return 0;
}