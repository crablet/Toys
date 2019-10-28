#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <unordered_map>
#include <unordered_set>
#include <QChart>
#include <QChartView>
#include <QPieSlice>
#include <QPieSeries>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTime>
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QStackedWidget>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

class AnalysisWindow : public QWidget
{
	Q_OBJECT
public:
	explicit AnalysisWindow(QWidget *parent = nullptr);

signals:

public slots:
	void UpdatePieChart(const std::unordered_map<std::string, int>&);
	void UpdateLineChart(const std::unordered_map<std::string, int>&);
	void InitializeAnalysisChart(const std::unordered_set<std::string>&);

private:
	QVBoxLayout *Layout, *PieChartLayout, *LineChartLayout;

	QPieSeries *PieSeries;

	QDateTimeAxis *AxisX;
	QValueAxis *AxisY;

	QChart *PieChart, *LineChart;
	QChartView *PieChartView, *LineChartView;

	QStackedWidget *ChartStack;
	QWidget *PieChartWidget, *LineChartWidget;

	QRadioButton *ChoosePieChart, *ChooseLineChart;

	QDateTime BeginTime;

private:
	void InitializeUi();
	void InitializeConnect();
};

#endif // ANALYSISWINDOW_H