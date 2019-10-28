#include "analysiswindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent)
	: QWidget(parent)
{
	InitializeUi();
	InitializeConnect();
}

void AnalysisWindow::UpdatePieChart(const std::unordered_map<std::string, int> &UrlCount)
{
	auto PieSlices = PieSeries->slices();
	for (const auto &r : UrlCount)
	{
		const auto UrlName = QString::fromStdString(r.first);
		for (const auto &Slice : PieSlices)
		{
			if (Slice->label() == UrlName)	// find the corresponding part of the pie chart and update its value
			{
				Slice->setValue(r.second);
			}
		}
	}
}

void AnalysisWindow::UpdateLineChart(const std::unordered_map<std::string, int> &CountIn30Secs)
{
	for (const auto &[StdUrl, Count] : CountIn30Secs)
	{
		auto Url = QString::fromStdString(StdUrl);
		for (const auto &LineSeries : LineChart->series())
		{
			if (LineSeries->name() == Url)
			{
				auto Now = QDateTime(QDate::currentDate(), QTime::currentTime()).toMSecsSinceEpoch();
				static_cast<QLineSeries*>(LineSeries)->append(Now, Count);

				break;
			}
		}
	}
}

void AnalysisWindow::InitializeAnalysisChart(const std::unordered_set<std::string> &UrlSet)
{
	BeginTime = QDateTime(QDate::currentDate(), QTime::currentTime());

	// PieChart begin

	PieSeries = new QPieSeries;
	for (const auto &Url : UrlSet)
	{
		auto *Slice = new QPieSlice(QString::fromStdString(Url), 0);
		PieSeries->append(Slice);
		connect(Slice, &QPieSlice::hovered, Slice, [=](bool Hovering)
		{
			if (Hovering)
			{
				Slice->setExploded(true);
				Slice->setLabelVisible(true);
			}
			else
			{
				Slice->setExploded(false);
				Slice->setLabelVisible(false);
			}
		});
	}

	PieChart = new QChart;
	PieChart->addSeries(PieSeries);
	PieChart->setAnimationOptions(QChart::AllAnimations);
	PieChart->legend()->setAlignment(Qt::AlignLeft);
	PieChart->setMargins(QMargins(0, 0, 0, 0));

	PieChartView->setChart(PieChart);
	PieChartView->setRenderHint(QPainter::Antialiasing);
	PieChartView->show();

	// PieChart end
	
	// -----------------------------//

	// LineChart begin

	auto BeginTime = QDateTime(QDate::currentDate(), QTime::currentTime());
	auto EndTime = QDateTime(QDate::currentDate(), QTime::currentTime().addSecs(360));
	AxisX = new QDateTimeAxis;
	AxisX->setRange(BeginTime, EndTime);
	AxisX->setFormat("hh:mm:ss");
	AxisX->setTickCount(7);
	AxisX->setTitleText("Time");

	AxisY = new QValueAxis;
	AxisY->setRange(0, 15);
	AxisY->setTitleText("Count");

	LineChart = new QChart;
	LineChart->addAxis(AxisX, Qt::AlignBottom);
	LineChart->addAxis(AxisY, Qt::AlignLeft);
	LineChart->setMargins(QMargins(0, 0, 0, 0));
	LineChart->setAnimationOptions(QChart::AllAnimations);

	for (const auto &Url : UrlSet)
	{
		auto *UrlSeries = new QLineSeries;
		UrlSeries->setName(QString::fromStdString(Url));
		UrlSeries->append(BeginTime.toMSecsSinceEpoch(), 0);
		LineChart->addSeries(UrlSeries);
		UrlSeries->attachAxis(AxisX);
		UrlSeries->attachAxis(AxisY);
	}

	LineChartView->setChart(LineChart);
	LineChartView->setRenderHint(QPainter::Antialiasing);
	LineChartView->show();

	// LineChart end
}

void AnalysisWindow::InitializeUi()
{
	PieChartView = new QChartView;
	PieChartLayout = new QVBoxLayout(this);
	PieChartLayout->addWidget(PieChartView);

	PieChartWidget = new QWidget;
	PieChartWidget->setLayout(PieChartLayout);

	LineChartView = new QChartView;
	LineChartLayout = new QVBoxLayout(this);
	LineChartLayout->addWidget(LineChartView);

	LineChartWidget = new QWidget;
	LineChartWidget->setLayout(LineChartLayout);

	ChartStack = new QStackedWidget(this);
	ChartStack->addWidget(PieChartWidget);
	ChartStack->addWidget(LineChartWidget);
	ChartStack->setCurrentWidget(PieChartWidget);	// pie chart is the default chart

	Layout = new QVBoxLayout(this);
	Layout->setMargin(0);
	Layout->addWidget(ChartStack);
	setLayout(Layout);

	ChoosePieChart = new QRadioButton("Visits", this);
	ChoosePieChart->move(ChartStack->x() + 9, ChartStack->y());
	ChoosePieChart->setChecked(true);	// pie chart is the default chart

	ChooseLineChart = new QRadioButton("Timeline", this);
	ChooseLineChart->move(ChoosePieChart->x() + ChoosePieChart->width(), ChoosePieChart->y());
}

void AnalysisWindow::InitializeConnect()
{
	connect(ChoosePieChart, &QRadioButton::clicked, [this]()
	{
		ChartStack->setCurrentWidget(PieChartWidget);
	});
	connect(ChooseLineChart, &QRadioButton::clicked, [this]()
	{
		ChartStack->setCurrentWidget(LineChartWidget);
	});
}
