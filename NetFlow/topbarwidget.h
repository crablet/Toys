#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QPalette>

class TopBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

signals:
	void ShowStartWindow();
	void ShowAnalysisWindow();
	void ShowCaptureRecordWindow();

public slots:

private:
	QHBoxLayout *Layout;
	QLabel *Icon;
	QPushButton *StartWindowBtn, *AnalysisWindowBtn, *CaptureRecordWindowBtn;
};

#endif // TOPBARWIDGET_H