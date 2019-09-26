#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <vector>
#include <cmath>

#include <QPixmap>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QtGlobal>

class GaussianBlur
{
public:
	GaussianBlur() = delete;
	GaussianBlur(const QPixmap &Src, int r = 6, double Sigma = 4.0)
		: OriginImage(Src.toImage()),
		  FirstPassImage(Src.size(), QImage::Format_RGB32), SecondPassImage(Src.size(), QImage::Format_RGB32),
		  r(r), Weight(2 * r + 1),
		  Sigma(Sigma), C(1 / (Sigma * std::sqrt(2 * std::acos(-1.0))))
	{
		GetKernal();
		Blur();
	}

private:
	QImage OriginImage, FirstPassImage, SecondPassImage;

	int r;	// 高斯模糊半径
	std::vector<double> Weight;	// 权重空间
	double Sigma, C;	// 高斯函数中的两个参数

public:
	operator QPixmap();

private:
	double GaussianFunction(int x) const;	// 一维高斯函数
	void GetKernal();	// 获取线性权值空间
	int DealEdges(int x, int i, int w) const;
	void Blur();
};

#endif // GAUSSIANBLUR_H