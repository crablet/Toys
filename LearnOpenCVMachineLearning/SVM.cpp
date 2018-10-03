// �ο����ϣ����������Ķ��˴���
// http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/ml/introduction_to_svm/introduction_to_svm.html#introductiontosvms
// https://docs.opencv.org/3.4/d1/d73/tutorial_introduction_to_svm.html
// http://blog.sina.com.cn/s/blog_662c7859010105za.html
// https://blog.csdn.net/xingkongfenqi/article/details/49794567
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

int main()
{
    // ��ѵ�����ݴ��ϱ�ǩ����Ӧ1���-1��
    int Labels[4] = { 1, -1, -1, -1 };
    cv::Mat LabelsMat(4, 1, CV_32SC1, Labels);  // CV_32SC1: 32λ�з��ŵ�ͨ������

    // ����ѵ�����ݵ����꣬ע��Ҫ��ǰ���Labels��Ӧ����
    float TrainingData[4][2] = { {501., 10.}, {255., 10.}, {501., 255.}, {10., 501.} };
    cv::Mat TrainingDataMat(4, 2, CV_32F, TrainingData);

    // ��ʼ��֧��������
    auto SVM = cv::ml::SVM::create();
    SVM->setType(cv::ml::SVM::C_SVC);
    SVM->setKernel(cv::ml::SVM::LINEAR);
    SVM->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
    SVM->train(TrainingDataMat, cv::ml::ROW_SAMPLE, LabelsMat);

    // ��ʼ������
    constexpr auto Width = 512, Height = 512;
    cv::Mat Image = cv::Mat::zeros(Height, Width, CV_8UC3);

    const cv::Vec3b Green(0, 255, 0), Blue(255, 0, 0);
    for (int i = 0; i < Image.rows; ++i)    // ���������ϵ�ÿ����
    {
        for (int j = 0; j < Image.cols; ++j)
        {
            cv::Mat SampleMat = (cv::Mat_<float>(1, 2) << j, i);
            auto Response = static_cast<int>(SVM->predict(SampleMat));  // ͨ��֧��������Ԥ��õ�����

            // ����ȡ�õ�����������ɫ
            if (Response == 1)
            {
                Image.at<cv::Vec3b>(i, j) = Green;
            }
            else if (Response == -1)
            {
                Image.at<cv::Vec3b>(i, j) = Blue;
            }
        }
    }

    // �ڻ����ϻ���ѵ����������ʾ�ĵ�
    auto Thinckness = -1;
    cv::circle(Image, cv::Point(501, 10), 5, cv::Scalar(0, 0, 0), Thinckness);
    cv::circle(Image, cv::Point(255, 10), 5, cv::Scalar(255, 255, 255), Thinckness);
    cv::circle(Image, cv::Point(501, 255), 5, cv::Scalar(255, 255, 255), Thinckness);
    cv::circle(Image, cv::Point(10, 501), 5, cv::Scalar(255, 255, 255), Thinckness);

    Thinckness = 2;
    auto SV = SVM->getUncompressedSupportVectors(); // ���֧������
    for (int i = 0; i < SV.rows; ++i)
    {
        auto v = SV.ptr<float>(i);  // ��֧���������ϻ�Ȧ
        cv::circle(Image, cv::Point(static_cast<int>(v[0]), static_cast<int>(v[1])),
            6, cv::Scalar(128, 128, 128), Thinckness);
    }

    cv::imwrite("result.png", Image);
    cv::imshow("Result", Image);

    cv::waitKey();

    return 0;
}