#include "topbarwidget.h"

TopBarWidget::TopBarWidget(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(155);

	Icon = new QLabel;
	Icon->setPixmap(QPixmap::fromImage(QImage(":/NetFlowIcon.jpg")));
	Icon->setScaledContents(true);

	StartWindowBtn = new QPushButton("Start");
	connect(StartWindowBtn, &QPushButton::clicked, [this]()
	{
		emit ShowStartWindow();
	});

	AnalysisWindowBtn = new QPushButton("Analysis");
	connect(AnalysisWindowBtn, &QPushButton::clicked, [this]()
	{
		emit ShowAnalysisWindow();
	});

	CaptureRecordWindowBtn = new QPushButton("Capture Record");
	connect(CaptureRecordWindowBtn, &QPushButton::clicked, [this]()
	{
		emit ShowCaptureRecordWindow();
	});

	Layout = new QHBoxLayout(this);
	Layout->addWidget(Icon);
	Layout->addWidget(StartWindowBtn);
	Layout->addWidget(AnalysisWindowBtn);
	Layout->addWidget(CaptureRecordWindowBtn);
	Layout->setMargin(0);
	
	setLayout(Layout);
}
