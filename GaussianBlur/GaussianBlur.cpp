#include "GaussianBlur.h"

double GaussianBlur::GaussianFunction(int x) const
{
	return C * std::exp(-1.0 * x * x / (2.0 * Sigma * Sigma));
}

void GaussianBlur::GetKernal()
{
	double Sum = 0.0;

	// 获取线性权值空间Weight[]
	for (int i = 0; i < 2 * r + 1; ++i)
	{
		Weight[i] = GaussianFunction(i - r);
		Sum += Weight[i];
	}

	// 归一化
	for (int i = 0; i < 2 * r + 1; ++i)
	{
		Weight[i] /= Sum;
	}
}

// 处理边缘像素越界的问题
int GaussianBlur::DealEdges(int x, int i, int w) const
{
	int t = x + i;
	if (Q_UNLIKELY(t < 0 || t >= w))	// [unlikely] in C++20
	{
		return x - i;
	}
	else
	{
		return t;
	}
}

void GaussianBlur::Blur()
{
	for (int y = 0; y < OriginImage.height(); ++y)
	{
		for (int x = 0; x < OriginImage.width(); ++x)
		{
			double Red = 0.0, Green = 0.0, Blue = 0.0;
			for (int i = -r; i <= r; ++i)
			{
				auto Rgb = QColor(OriginImage.pixelColor(DealEdges(x, i, OriginImage.width()), y));
				Red += Weight[r + i] * Rgb.red();
				Green += Weight[r + i] * Rgb.green();
				Blue += Weight[r + i] * Rgb.blue();
			}

			FirstPassImage.setPixelColor(QPoint(x, y), QColor(Red, Green, Blue));
		}
	}

	for (int y = 0; y < FirstPassImage.height(); ++y)
	{
		for (int x = 0; x < FirstPassImage.width(); ++x)
		{
			double Red = 0.0, Green = 0.0, Blue = 0.0;
			for (int i = -r; i <= r; ++i)
			{
				auto Rgb = QColor(FirstPassImage.pixelColor(x, DealEdges(y, i, FirstPassImage.height())));
				Red += Weight[r + i] * Rgb.red();
				Green += Weight[r + i] * Rgb.green();
				Blue += Weight[r + i] * Rgb.blue();
			}

			SecondPassImage.setPixelColor(QPoint(x, y), QColor(Red, Green, Blue));
		}
	}
}

GaussianBlur::operator QPixmap()
{
	return QPixmap::fromImage(SecondPassImage);
}
